#include <iostream>
#include <iomanip>
#include <sstream>
#include <bitset>
//#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */
#include <cmath>
#include <fstream>

#include "call_ihsenv2.h"
#include "softposit.h"
#include "internals.h"
#include "primitives.h"
#include "platform.h"

using namespace std;

typedef union {
    uint32_t st;
    float f;
} IEEE754Union;

typedef union {
    uint32_t st;
    posit32_t p;
} PositUnion;





float fault_inj_float(float fi, int i) { //float to corrupt with ER error rate (probability)

    IEEE754Union u;

    u.f=fi;// put the float i the corruption system NIAHAHA
    std::bitset<32> temp(u.st);
    //cout << "before injection in bit " << i << ":  "<< temp <<" f= "<< fi << endl;
     //std::cout<< "injection fault in bit n°"<<i <<std::endl;
     temp.flip(i);
     u.st=(uint32_t)temp.to_ulong();
     fi = u.f;
     //cout << "After injection in bit " << i << ":  " << temp <<" f*= " << fi << endl;
  
    return fi;
}

posit32_t fault_inj_posit(posit32_t pp, int i) { //posit to corrupt with ER error rate (probability)

    PositUnion u;

    u.p=pp;// put the float i the corruption system NIAHAHA
    std::bitset<32> temp(u.st);
     

      //cout<< "injection fault in bit n°"<<i <<std::endl;
     temp.flip(i);
     u.st=(uint32_t)temp.to_ulong();
      //u.p = ui32_to_p32 ((uint32_t)temp.to_ulong());
 
    
    pp = u.p;
     //cout<<"after fault injection , maybe :/ " << fi << endl;
     
    return pp;
}

int Exhaustive(){

	//ofstream posit_file, float_file;

	uint32_t raw;
	raw =0; //4294967294
	float f,fe,e_f;
	posit32_t p,pe, e_p;
	IEEE754Union uF;
	PositUnion uP;
  
    float EF;
    EF=0.0;
    posit32_t EP;
    EP=convertFloatToP32(0.0);

    //posit_file.open ("posit.txt");
    //float_file.open ("float.txt");

    while (raw < 4294967294){//0x 00000000 till 0xFFFFFFFF

    	uF.st=raw;
    	f= uF.f;
    	uP.st=raw;
    	p= uP.p;
   		e_f=0;
   		e_p=convertFloatToP32(0.0);
   		

    	for (int i = 0; i < 32; ++i)
    	{

        fe=fault_inj_float(f,i);
			  e_f += abs(f-fe);
			//cout << "raw= " << raw<< "  __ correct= " << f <<"  corrupted bit i= "<<i <<"__ F*= " << fe << " Err= "<< f+fe << "\n";
    		pe =fault_inj_posit(p,i);
    		e_p = p32_add( e_p, p32_sub(p,pe));

    		/* code */
    	}

    	e_f = e_f/32; // mean error distance
    	e_p = p32_div(e_p,convertFloatToP32(32.0)); // mean error distance
        //cout << "E_f= "<< e_f <<"  ***  EF= "<< EF << endl;
        //cout << "E_p= "<< convertP32ToDouble(e_p) <<"  ***  EP= "<< convertP32ToDouble(EP) << endl;

      if ( ( (abs(e_f - EF)/abs(e_f)) > 0.01) || ( convertP32ToDouble(p32_div(p32_sub(e_p,EP),e_p)) > 0.01 ) || ( convertP32ToDouble(p32_div(p32_sub(e_p,EP),e_p)) < -0.01 )  )//(( raw == 0) || (abs(e_f - EF) > 0.01) || ( convertP32ToDouble(p32_sub(e_p,EP)) > 0.01 ) || ( convertP32ToDouble(p32_sub(e_p,EP)) < -0.01 )  ) //( not p32_eq(e_p ,EP) || )
            { 
            //float_file <<" inside the if "<<endl;
            //cout << "EF - e_f= " << EF - e_f << endl;
            //cout << "debugging... EF - e_f= " << EF - e_f << " EP - e_p ="  << convertP32ToDouble(p32_sub(EP,e_p)) << endl;
            //float_file << raw << "  " << e_f << endl;
            //posit_file << raw << "  " << convertP32ToDouble(e_p) << endl;
            cout<< raw << " " << e_f << " " << convertP32ToDouble(e_p) << endl;
            EF= e_f;//track what to show ; the error trend
            EP= e_p;//track what to show ; the error trend if there is a change in the error     
            }
      //else continue;
    
      ++raw;
      }
		
        


//posit_file.close();
//float_file.close();
return 0;
}

