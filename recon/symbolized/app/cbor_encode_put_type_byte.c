#include "g1_app_symbols.h"
/* named: cbor_encode_put_type_byte */
/* Reconstructed cbor_encode_put_type_byte @ 0x861d4  (parity: 300/300 trials, PROVEN) */

extern long long cbor_encode_check_ok(unsigned int);
extern void cbor_encode_set_error(unsigned int *, unsigned int);

int cbor_encode_put_type_byte(unsigned int *param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned int uVar1;
  unsigned char *pbVar2;
  long long uVar3;
  uVar3 = cbor_encode_check_ok(param_1[5]);
  if ((int)uVar3 != 0) {
    pbVar2 = (unsigned char *)param_1[0];
    if (pbVar2 < (unsigned char *)param_1[3]) {
      if (param_3 < 0x20) {
        param_1[0] = (unsigned int)(pbVar2 + 1);
        *pbVar2 = (unsigned char)param_3 | (unsigned char)((int)(uVar3 >> 32) << 5);
        return (int)uVar3;
      }
      uVar1 = 0xe;
    } else {
      uVar1 = 8;
    }
    cbor_encode_set_error(param_1, uVar1);
  }
  return 0;
}

