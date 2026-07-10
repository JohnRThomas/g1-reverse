#include "g1_app_symbols.h"
/* named: Bfree */
/* Reconstructed Bfree @ 0x78654  (parity: 300/300 trials, PROVEN) */

extern unsigned int *malloc(int size);
extern unsigned int *libc_fatal_error_and_abort(int a,int b,int c,int d);

void Bfree(int param_1, unsigned int *param_2)
{
  unsigned int *puVar1;
  int iVar2;

  if (*(volatile int *)(param_1 + 0x24) == 0) {
    puVar1 = malloc(0x10);
    *(volatile unsigned int *)(param_1 + 0x24) = (unsigned int)puVar1;
    if (puVar1 == 0) {
      puVar1 = libc_fatal_error_and_abort("/__w/_temp/workspace/build/.build/HOST-x86_64-w64-mingw32/arm-zephyr-eabi/src/newlib-nano/newlib/libc/stdlib/mprec.c" /*=0xf8cd5*/, 0x8a, 0, "REENT malloc succeeded" /*=0xf8bb7*/);
    }
    puVar1[1] = 0;
    puVar1[2] = 0;
    *puVar1 = 0;
    puVar1[3] = 0;
  }
  if (param_2 != 0) {
    iVar2 = *(int *)(*(int *)(param_1 + 0x24) + 0xc);
    *param_2 = *(unsigned int *)(iVar2 + param_2[1] * 4);
    *(unsigned int **)(iVar2 + param_2[1] * 4) = param_2;
  }
}

