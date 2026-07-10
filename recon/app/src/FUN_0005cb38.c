/* Reconstructed FUN_0005cb38 @ 0x5cb38  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern long long FUN_00081820(unsigned,int,unsigned,unsigned,int);
extern void FUN_0005f24c(unsigned);
extern void FUN_00083074(unsigned,unsigned,void*);
extern void FUN_0007350c(int,int,unsigned,int);

void FUN_0005cb38(int param_1, unsigned param_2, unsigned param_3){
  long long uVar1 = FUN_00081820(*(volatile unsigned*)(param_1+0xf0), 6, param_2, param_3, 0);
  if((int)uVar1 != 0){
    if((int)uVar1 == -0x69){
      unsigned local_18, local_14;
      local_14 = 0x000f4557;
      local_18 = 2;
      FUN_00083074(0x00088180, 0x1040, &local_18);
      (void)local_14;
    }
    FUN_0005f24c(param_2);
    return;
  }
  FUN_0007350c(param_1+0x208, (int)((unsigned long long)uVar1 >> 0x20), 0xf0000, 0);
}

