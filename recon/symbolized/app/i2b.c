#include "g1_app_symbols.h"
/* named: i2b */
/* Reconstructed i2b @ 0x787bc  (parity: 300/300 trials, PROVEN) */

extern int Balloc(int a, int b);
extern int libc_fatal_error_and_abort(int a, int b, int c, int d);
void i2b(int param_1, int param_2)
{
  int iVar1;
  iVar1 = Balloc(param_1, 1);
  if (iVar1 == 0) {
    iVar1 = libc_fatal_error_and_abort("/__w/_temp/workspace/build/.build/HOST-x86_64-w64-mingw32/arm-zephyr-eabi/src/newlib-nano/newlib/libc/stdlib/mprec.c" /*=0xf8cd5*/, 0x140, 0, "Balloc succeeded" /*=0xf8c42*/);
  }
  *(volatile int *)(iVar1 + 0x14) = param_2;
  *(volatile int *)(iVar1 + 0x10) = 1;
}

