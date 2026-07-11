/* Reconstructed FUN_00081820 @ 0x81820.
 * Complete 50-byte tail-dispatch wrapper; 0x81852 starts the next function. */
#include <stdint.h>
extern short* FUN_0005f518(int,int);
extern unsigned FUN_000564cc(int,int,int,unsigned);

unsigned FUN_00081820(int param_1, short param_2, int param_3, int param_4, unsigned param_5){
  short *psVar4 = FUN_0005f518(param_3 + 0xc, 4);
  short sVar1 = *(short*)(param_3 + 0x10);
  psVar4[1] = param_2;
  *psVar4 = (short)(sVar1 - 4);
  return FUN_000564cc(param_1, param_3, param_4, param_5);
}
