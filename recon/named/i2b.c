/* named: i2b */
/* Reconstructed i2b @ 0x787bc  (parity: 300/300 trials, PROVEN) */

extern int Balloc(int a, int b);
extern int libc_fatal_error_and_abort(int a, int b, int c, int d);
void i2b(int param_1, int param_2)
{
  int iVar1;
  iVar1 = Balloc(param_1, 1);
  if (iVar1 == 0) {
    iVar1 = libc_fatal_error_and_abort(0x000f8cd5, 0x140, 0, 0x000f8c42);
  }
  *(volatile int *)(iVar1 + 0x14) = param_2;
  *(volatile int *)(iVar1 + 0x10) = 1;
}

