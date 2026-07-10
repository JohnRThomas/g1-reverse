#include "g1_app_symbols.h"
/* named: att_timeout */
/* Reconstructed att_timeout @ 0x59920  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint8_t* FUN_00081526(uint32_t);
extern void snprintk(void*, int, uint32_t, ...);
extern void strcpy(void*, uint32_t);
extern void FUN_00081ddc(uint32_t, int, void*);
extern void FUN_00059834(int);

void att_timeout(int param_1){
  uint8_t *puVar1;
  uint32_t uVar2;
  volatile uint32_t local_58, local_54;
  volatile uint8_t *local_50, *local_4c;
  uint8_t auStack_44[12];
  uint8_t auStack_38[32];
  puVar1 = FUN_00081526(**(uint32_t**)(param_1 - 0x160));
  switch(puVar1[0]){
    case 0: uVar2 = "public" /*=0x9a1c8*/; break;
    case 1: uVar2 = "random" /*=0x9a1cf*/; break;
    case 2: uVar2 = "public-id" /*=0x9a1d6*/; break;
    case 3: uVar2 = "random-id" /*=0x9a1e0*/; break;
    default:
      snprintk(auStack_44, 10, "0x%02x" /*=0xf5071*/);
      goto LAB;
  }
  strcpy(auStack_44, uVar2);
LAB:
  local_50 = (volatile uint8_t*)(uint32_t)puVar1[1];
  local_54 = puVar1[2];
  local_58 = puVar1[3];
  local_4c = auStack_44;
  snprintk(auStack_38, 0x1e, "%02X:%02X:%02X:%02X:%02X:%02X (%s)" /*=0x9a1ea*/, puVar1[6], puVar1[5], puVar1[4]);
  local_54 = "ATT Timeout for device %s" /*=0xf4697*/;
  local_4c = (volatile uint8_t*)(((uintptr_t)local_4c & 0xffff0000) | 0x200);
  local_58 = 0x1000003;
  local_50 = auStack_38;
  FUN_00081ddc(((uintptr_t)&tbl_880d8) /*=0x88100*/, 0x1c40, (void*)&local_58);
  FUN_00059834(param_1 - 0x158);
}

