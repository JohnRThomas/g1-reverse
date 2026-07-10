/* Reconstructed FUN_000848b0 @ 0x848b0  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void *a, int b, int c);
extern void FUN_00084840(int a, void *b);
void FUN_000848b0(int param_1)
{
  unsigned char local_1c[20];
  memset_bytes(local_1c, 0, 0x14);
  local_1c[0] = 5;
  FUN_00084840(param_1, local_1c);
}

