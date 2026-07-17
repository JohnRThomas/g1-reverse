/* Reconstructed FUN_0004a2a4 @ 0x4a2a4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(int,...);
extern int FUN_0004a1b8(int,void*);
extern int FUN_0007d280(int,int,int);
extern int FUN_0007d4b2(int);
void FUN_0004a2a4(int param_1){
  uint16_t calendar[6]={0};
  FUN_0004a1b8(param_1, calendar);
  uint32_t uVar3 = calendar[0];
  uint32_t uVar1 = calendar[1];
  uint32_t uVar4 = calendar[2];
  DEBUG_PRINT(0x0009bbbf, param_1, uVar3, uVar1, uVar4,
              calendar[3], calendar[4], calendar[5]);
  int cVar2 = FUN_0007d280(uVar3, uVar1, uVar4);
  FUN_0007d4b2((int)(uint8_t)(cVar2 + 0x3b));
}
