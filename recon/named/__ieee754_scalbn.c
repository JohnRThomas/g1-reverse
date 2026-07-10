/* named: __ieee754_scalbn */
/* Reconstructed __ieee754_scalbn @ 0x13e60  (parity: 300/300 trials, PROVEN) */
extern unsigned long long __muldf3(void);
extern unsigned long long __aeabi_dadd(void);
double __ieee754_scalbn(double d0in, int param_1){
  union { double d; unsigned long long u; } v; v.d = d0in;
  unsigned lo = (unsigned)v.u, hi = (unsigned)(v.u >> 32);
  unsigned exp = (hi >> 20) & 0x7ff;
  if (exp == 0){
    if (((hi & 0x7fffffff) | lo) == 0) return v.d;
    v.u = __muldf3();
    lo = (unsigned)v.u; hi = (unsigned)(v.u >> 32);
    if (param_1 < (int)0xffff3cb0){ v.u = __muldf3(); return v.d; }
    exp = ((hi >> 20) & 0x7ff) - 0x36;
  } else if (exp == 0x7ff){
    v.u = __aeabi_dadd();
    return v.d;
  }
  {
    int newexp = (int)exp + param_1;
    if (newexp > 0 && newexp <= 0x7fe){
      hi = (hi & 0x800fffff) | ((unsigned)newexp << 20);
      v.u = ((unsigned long long)hi << 32) | lo;
      return v.d;
    }
    v.u = __muldf3();
    return v.d;
  }
}

