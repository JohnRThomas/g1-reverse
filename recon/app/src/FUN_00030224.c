/* Reconstructed FUN_00030224 @ 0x30224  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00030178(int,...);
int FUN_00030224(void){
  volatile uint32_t *puVar1 = (volatile uint32_t*)0x20007bc4UL;
  volatile uint32_t *puVar2 = (volatile uint32_t*)0x0008a0a8UL;
  int iVar3 = 0;
  do {
    uint32_t v0 = puVar2[0];
    uint32_t v1 = puVar2[1];
    if(v0 == 0x4414){
      *puVar1 = v1;
    } else {
      FUN_00030178(v0 & 0xffff, v1);
    }
    iVar3 += 2;
    puVar2 += 2;
  } while(iVar3 != 0x58);
  iVar3 = FUN_00030178(0x4408, 1);
  if(iVar3 != 0){
    return -1;
  }
  *(volatile uint32_t*)0x20007bc8UL = 1;
  iVar3 = FUN_00030178(0x4414, (int)*puVar1);
  return (iVar3 != 0) ? -1 : 0;
}
