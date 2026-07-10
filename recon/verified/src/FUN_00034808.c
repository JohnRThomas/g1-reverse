/* Reconstructed FUN_00034808 @ 0x34808  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00033cdc(void);
extern int FUN_0003444c(void);
extern int FUN_000347cc(void);

int FUN_00034808(void)
{
  int iVar2 = FUN_00033cdc();
  volatile char *pcVar1 = (volatile char*)0x2001a229UL;
  if (iVar2 != 0) {
    if (*pcVar1 == 5) {
      iVar2 = FUN_0003444c();
      if (iVar2 == 1) return 1;
    }
    if (*pcVar1 == 3) {
      iVar2 = FUN_000347cc();
      return iVar2 == 1;
    }
  }
  return 0;
}

