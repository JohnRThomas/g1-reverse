#include "g1_app_symbols.h"
/* named: FUN_00063bcc */
/* Reconstructed FUN_00063bcc @ 0x63bcc  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_0004f564(unsigned int a);
void FUN_00063bcc(void) {
  unsigned int r = FUN_0004f564(0xc);
  if (r != 0) {
    *(unsigned int*)(r + 4) = ((uintptr_t)&rodata_fa9cc) /*=0xfa9cc*/;
  }
}

