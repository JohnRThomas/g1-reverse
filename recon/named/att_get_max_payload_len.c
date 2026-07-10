/* named: att_get_max_payload_len */
/* Reconstructed att_get_max_payload_len @ 0x80c7c  (parity: 300/300 trials, PROVEN) */

extern unsigned int thunk_FUN_000823fa(void);
unsigned int att_get_max_payload_len(unsigned char *param_1) {
  unsigned int v = *(unsigned int*)(param_1 + 0x18);
  if (v != 0) {
    unsigned int r = thunk_FUN_000823fa();
    v = (r - 3) & 0xffff;
  }
  return v;
}

