#include "g1_app_symbols.h"
/* named: cbor_decode_check_major_type */
/* Reconstructed cbor_decode_check_major_type @ 0x85da2  (parity: 300/300 trials, PROVEN) */

extern int cbor_decode_precheck(void);
extern void FUN_00085d70(int *a, int b, int c, unsigned char d, int e);
int cbor_decode_check_major_type(int **param_1, unsigned int param_2, int param_3, int param_4)
{
  int iVar1;
  iVar1 = cbor_decode_precheck();
  if (iVar1 != 0) {
    unsigned char *p = (unsigned char *)*param_1;
    if (param_2 == (unsigned int)(*(volatile unsigned char *)p >> 5)) {
      return iVar1;
    }
    FUN_00085d70((int *)param_1, 10, param_3, *(volatile unsigned char *)p, param_4);
  }
  return 0;
}

