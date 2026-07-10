#include "g1_app_symbols.h"
/* named: dtoa_get_bias_const */
/* Reconstructed dtoa_get_bias_const @ 0x13e50  (parity: 200/200 trials, PROVEN) */

static double bits64(unsigned long long u){ double d; __builtin_memcpy(&d,&u,8); return d; }
double dtoa_get_bias_const(void){ return bits64(0x7ff8000000000000ULL); }

