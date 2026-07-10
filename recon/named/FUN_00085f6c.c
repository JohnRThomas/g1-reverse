/* named: FUN_00085f6c */
/* Reconstructed FUN_00085f6c @ 0x85f6c  (parity: 300/300 trials, PROVEN) */

extern int cbor_decode_check_major_type(int param_1, int param_2);
extern void cbor_decode_extract_value(int param_1, int param_2, int param_3);

void FUN_00085f6c(int param_1, int param_2, int param_3)
{
  int iVar1;
  iVar1 = cbor_decode_check_major_type(param_1, 0);
  if (iVar1 != 0) {
    cbor_decode_extract_value(param_1, param_2, param_3);
  }
}

