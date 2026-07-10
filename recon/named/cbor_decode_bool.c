/* named: cbor_decode_bool */
/* Reconstructed cbor_decode_bool @ 0x86006  (parity: 300/300 trials, PROVEN) */

extern int cbor_decode_simple_value(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern void cbor_decode_undo_and_fail(unsigned int, unsigned int);

int cbor_decode_bool(unsigned int param_1, unsigned char *param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  unsigned char *uStack_14 = param_2;
  unsigned int uStack_10 = param_3;
  iVar1 = cbor_decode_simple_value(param_1, (unsigned int)((unsigned char *)&uStack_14 + 3), param_3, param_4, param_1);
  if (iVar1 != 0) {
    unsigned char byte3 = ((unsigned char *)&uStack_14)[3];
    unsigned char bVar2 = byte3 - 0x14;
    if (bVar2 < 2) {
      *param_2 = bVar2 & 1;
      return iVar1;
    }
    cbor_decode_undo_and_fail(param_1, 10);
  }
  return 0;
}

