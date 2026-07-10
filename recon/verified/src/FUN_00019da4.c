/* Reconstructed FUN_00019da4 @ 0x19da4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int FUN_00019c70(int,...);
extern int FUN_00086c04(int,...);
unsigned int FUN_00019da4(int param_1, unsigned char *param_2, unsigned int param_3)
{
  volatile int *E = (volatile int*)0x20007554UL;
  volatile unsigned char *P = (volatile unsigned char*)0x2001031fUL;
  volatile unsigned short *H6f2 = (volatile unsigned short*)0x2000d6f2UL;
  volatile unsigned short *H6f0 = (volatile unsigned short*)0x2000d6f0UL;
  if (param_2 == 0) {
    if (*E == 0) DEBUG_PRINT(0x9b371,0x9e0b2,0xe4);
    else FUN_00019c70(0x9b371,0x9e0b2,0xe4);
    return 0xca;
  }
  if (param_1 == 0) {
    if (*E == 0) DEBUG_PRINT(0x9b38f,0x9e0b2,0xe9);
    else FUN_00019c70(0);
    return 0xca;
  }
  if (param_3 < 4) {
    if (*E != 0) { FUN_00019c70(0x9b3b5,0x9e0b2,0xef,param_3); return 0xca; }
    DEBUG_PRINT(0x9b3b5,0x9e0b2,0xef,param_3);
    return 0xca;
  }
  {
    unsigned char bVar3 = param_2[3];
    unsigned char b0 = param_2[0];
    unsigned char bVar1 = param_2[1];
    unsigned char bVar2 = param_2[2];
    if (bVar3 == 0) {
      *P = b0;
      *H6f2 = (unsigned short)bVar3;
      *H6f0 = (unsigned short)bVar1;
    }
    unsigned int pb = *P;
    if (pb != b0) {
      if (*E != 0) FUN_00019c70(0x9b3e0,0x9e0b2,0x109,b0);
      else DEBUG_PRINT(0x9b3e0,0x9e0b2,0x109,b0,pb);
      return 0xca;
    }
    unsigned int h0 = *H6f0;
    if (bVar1 != h0) {
      if (*E != 0) FUN_00019c70(0x9b413,0x9e0b2,0x10f,bVar1);
      else DEBUG_PRINT(0x9b413,0x9e0b2,0x10f,bVar1,h0);
      return 0xca;
    }
    {
      unsigned short uVar4 = *H6f2;
      FUN_00086c04(param_1 + uVar4, (int)(param_2 + 4), param_3 - 4, bVar1);
      *H6f2 = (unsigned short)(param_3 + (uVar4 - 4));
      if ((int)bVar3 != (int)bVar2 - 1) return 0xcb;
      if (*E == 0) DEBUG_PRINT(0x9b44a, param_1);
      else FUN_00019c70(0);
      return 0xc9;
    }
  }
}

