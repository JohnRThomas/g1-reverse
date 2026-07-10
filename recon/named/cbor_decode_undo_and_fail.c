/* named: cbor_decode_undo_and_fail */
/* Reconstructed cbor_decode_undo_and_fail @ 0x85dc4  (parity: 300/300 trials, PROVEN) */

extern void FUN_00085d70(void);
void cbor_decode_undo_and_fail(unsigned int *param_1) {
  param_1[0] = param_1[1];
  param_1[2] = param_1[2] + 1;
  FUN_00085d70();
}

