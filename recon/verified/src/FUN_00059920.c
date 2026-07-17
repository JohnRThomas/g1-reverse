/* Reconstructed FUN_00059920 @ 0x59920  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint8_t* FUN_00081526(uint32_t);
extern void FUN_0007ddbe(void*, int, uint32_t, ...);
extern void FUN_00086fee(void*, uint32_t);
extern void FUN_00081ddc(uint32_t, int, void*);
extern void FUN_00059834(int);

void FUN_00059920(int param_1){
  uint8_t *puVar1;
  uint32_t uVar2;
  struct {
    uint32_t type;
    uint32_t format;
    uint8_t *text;
    uintptr_t style;
  } record;
  uint8_t auStack_44[12];
  uint8_t auStack_38[32];
  puVar1 = FUN_00081526(**(uint32_t**)(param_1 - 0x160));
  switch(puVar1[0]){
    case 0: uVar2 = 0x9a1c8; break;
    case 1: uVar2 = 0x9a1cf; break;
    case 2: uVar2 = 0x9a1d6; break;
    case 3: uVar2 = 0x9a1e0; break;
    default:
      FUN_0007ddbe(auStack_44, 10, 0xf5071);
      goto LAB;
  }
  FUN_00086fee(auStack_44, uVar2);
LAB:
  FUN_0007ddbe(auStack_38, 0x1e, 0x9a1ea, puVar1[6], puVar1[5], puVar1[4]);
  record.type = 0x1000003;
  record.format = 0xf4697;
  record.text = auStack_38;
  record.style = ((uintptr_t)auStack_44 & 0xffff0000) | 0x200;
  FUN_00081ddc(0x88100, 0x1c40, &record);
  FUN_00059834(param_1 - 0x158);
}
