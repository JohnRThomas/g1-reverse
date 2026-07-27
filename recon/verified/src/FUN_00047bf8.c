/* Reconstructed FUN_00047bf8 @ 0x47bf8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>

extern void FUN_00086c78(void*, int, int);
extern int FUN_000720d0(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned long, ...);

int FUN_00047bf8(unsigned char param_1, unsigned char param_2)
{
  unsigned char message[24];
  FUN_00086c78(message + 1, 0, 23);
  message[0] = 2;
  message[2] = 2;
  message[3] = 0;
  message[4] = param_1;
  message[5] = param_2;

  int iVar1 = FUN_000720d0(0x2000392c, message, 0, 0);
  if (iVar1 != 0) {
    DEBUG_PRINT(0xef058, 0xef71d);
    iVar1 = -1;
  }
  return iVar1;
}
