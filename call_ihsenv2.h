#include <bitset>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cmath>
#include <fstream>
#include "softposit.h"
#include "internals.h"
#include "primitives.h"
#include "platform.h"

int do_i_inject(float prob);
float fault_inj_float(float fi, int i);
posit32_t fault_inj_posit(posit32_t pp, int i);
int Exhaustive();
