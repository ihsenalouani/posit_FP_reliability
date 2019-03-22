#include <iostream>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <cmath>
#include <fstream>
#include "call_ihsenv2.h"
#include "softposit.h"

using namespace std;

int main(int argc, char *argv[]) {

    float f,fi;
    double pf;
    int a;
    posit32_t p,pp;


   // if (argc < 2 || 0 == sscanf(argv[1], "%f", &f)) {
   //     std::cerr << "Please supply a float as the first argument." << std::endl;
   //     return EXIT_FAILURE;
   // }
   // int width = 40;
   // width = (strlen(argv[1]) > width) ? (int) strlen(argv[1]) + 1 : width;
    
    //convert f to posit
    
    //p=convertFloatToP32(f);
    

    //for (int i=0;i<20;i++){
        

/*      if (do_i_inject(1))
        {   
          int i= rand() % 32; //location of fault injection within the float
          fi=fault_inj_float(f,i);
          pp= fault_inj_posit(p,i);
        }
*/


    
a=Exhaustive();
if (a!= 0){
  cout<<" an error occurred ";
}
else {
  return 0;
}



}
