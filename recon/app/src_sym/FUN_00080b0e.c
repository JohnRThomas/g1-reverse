/* Reconstructed FUN_00080b0e @ 0x80b0e  (parity: 300/300 trials, PROVEN) */

typedef void (*fp_t)(int);
extern void FUN_0005f24c(int);
void FUN_00080b0e(int param_1,int param_2)
{
  if (param_1 != 0) {
    fp_t f = *(volatile fp_t *)(param_2 + 0x38);
    if (f != (fp_t)0) {
      f(param_1 + 0x18);
    }
    FUN_0005f24c(param_1);
  }
}

