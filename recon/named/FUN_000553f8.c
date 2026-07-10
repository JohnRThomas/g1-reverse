/* named: FUN_000553f8 */
/* globals referenced:
//   0x20002000  g_ble_dev_state              
*/
/* Reconstructed FUN_000553f8 @ 0x553f8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00054d18(int,void*);
extern int FUN_00055204(int);
extern int FUN_00055350(void*,int);
extern int FUN_00080fba(void*,void*);
int FUN_000553f8(void){
  uint8_t local30;
  uint8_t stack2f[7];
  uint8_t stack28[24];
  volatile uint8_t *g = (volatile uint8_t*)0x20002000UL;
  if(*(volatile uint8_t*)(g+7) == 0){
    int iVar1 = FUN_00055350(stack28, 1);
    *(volatile uint8_t*)(g+7) = (uint8_t)iVar1;
    if(iVar1 != 0){
      uint8_t bVar4 = 0;
      do {
        uint32_t uVar3 = bVar4;
        if((uint32_t)*(volatile uint8_t*)(g+7) <= uVar3) return 0;
        FUN_00080fba(stack2f, stack28 + uVar3*0x16);
        local30 = 1;
        iVar1 = FUN_00054d18((int)uVar3, &local30);
        bVar4++;
      } while(iVar1 == 0);
      return iVar1;
    }
  }
  return FUN_00055204(0);
}

