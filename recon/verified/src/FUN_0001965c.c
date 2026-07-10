/* Reconstructed FUN_0001965c @ 0x1965c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, void*);
extern int FUN_00018d94(void*);
extern void FUN_00019c70(void);
extern void FUN_00021460(uint32_t, void*, void*);
extern void FUN_0003384c(void*);
extern int FUN_00034bd4(void*);
extern void FUN_0004a3d0(uint32_t, void*);
extern int FUN_0007ca80(void*);
extern int FUN_0007d224(void);
extern void FUN_00086c78(void*, int, int);
extern void FUN_0008705a(void*, uint32_t, int);

void FUN_0001965c(uint32_t param_1){
  uint32_t *puVar1;
  int iVar2;
  uint8_t uVar3;
  uint32_t local_1c8;
  int local_1c4[2];
  uint32_t local_1bc;
  char local_1b4[384];
  uint8_t auStack_34[32];
  volatile uint32_t local_14;
  local_1c8 = 0x4b;
  FUN_00086c78(local_1c4, 0, 0x1b4);
  iVar2 = FUN_00018d94(local_1c4);
  if (iVar2 == 0 && (1 < local_14 || local_1b4[0] != 0)){
    local_1c4[0] = FUN_0007d224();
    puVar1 = (uint32_t*)0x20006aac;
    if (local_1c4[0] == 0) local_1c4[0] = 1;
    local_1bc = *(volatile uint32_t*)0x20006aac;
    FUN_0004a3d0(0x9ad7c, local_1c4);
    if (local_14 < 2 && (iVar2 = FUN_00034bd4(local_1b4), iVar2 != 2)){
      if (iVar2 != 3){
        if (iVar2 != 1) return;
        if (*(volatile int*)0x20007554 == 0){
          DEBUG_PRINT(0x9ad86, local_1b4);
        } else {
          FUN_00019c70();
        }
        FUN_0003384c(local_1c4);
        return;
      }
      uVar3 = 4;
    } else {
      uVar3 = 2;
    }
    *((uint8_t*)&local_1c8 + 1) = uVar3;
    if (*((char*)puVar1 + 6) == 2){
      FUN_0008705a(local_1b4, 0x9adaa, 0x20);
    }
    FUN_0007ca80(auStack_34);
    FUN_00021460(param_1, &local_1c8, local_1c4);
  }
}

