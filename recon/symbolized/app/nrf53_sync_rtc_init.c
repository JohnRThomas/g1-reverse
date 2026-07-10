#include "g1_app_symbols.h"
/* named: nrf53_sync_rtc_init */
/* Reconstructed nrf53_sync_rtc_init @ 0x4c2d4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void nrf53_ipc_channel_configure(uint32_t,uint32_t,uint32_t,int);
extern void FUN_0004d944(uint32_t,int,void*,...);
extern int FUN_0006385c(void);
extern void nrfx_gppi_channels_enable(uint32_t);
extern int FUN_0006540c(void*);
extern void FUN_00065418(uint32_t);

int nrf53_sync_rtc_init(void){
  uint8_t *puVar1;
  int iVar2, iVar4;
  volatile uint32_t local_1c;
  volatile uint32_t local_30; volatile void* local_2c; volatile int iStack_28;
  iVar2 = FUN_0006540c((void*)&local_1c);
  if (iVar2 == 0x0bad0000){
    iVar2 = FUN_0006385c();
    puVar1 = (uint8_t*)((uintptr_t)&tbl_87b30) /*=0x87bd8*/;
    if (iVar2 < 0){
      FUN_00065418(local_1c & 0xff);
    } else {
      iVar4 = *(int*)(((uintptr_t)&tbl_87b30) /*=0x87bd8*/+8);
      *(volatile uint8_t*)((volatile char*)&local_1c+1) = (uint8_t)iVar2;
      *(volatile uint16_t*)((volatile char*)&local_1c+2) = 0x807;
      int (*pcVar3)(uint32_t,int,uint32_t,uint32_t);
      pcVar3 = *(void**)(iVar4+4);
      if (pcVar3 != 0){
        iVar2 = pcVar3(((uintptr_t)&tbl_87b30) /*=0x87bd8*/, 8, ((uintptr_t)&rodata_4c419) /*=0x4c419*/, local_1c);
        if (iVar2 < 0) goto LAB;
        pcVar3 = *(void**)(iVar4+0x10);
        if (pcVar3 != 0){
          iVar2 = pcVar3((uint32_t)(uintptr_t)puVar1, 8, 1, 0);
          if (iVar2 >= 0){
            nrfx_gppi_channels_enable(1u << (local_1c & 0xff));
            nrf53_ipc_channel_configure(local_1c & 0xff, (local_1c>>8)&0xff, (local_1c>>24)&0xff, 1);
            if (iVar2 == 0) return 0;
          }
          goto LAB;
        }
      }
      iVar2 = -0x58;
    }
  } else {
    iVar2 = -0x13;
  }
LAB:
  local_2c = (void*)"Failed synchronized RTC setup (err: %d)" /*=0xf0a68*/;
  local_30 = 3;
  iStack_28 = iVar2;
  FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88288*/, 0x1840, (void*)&local_30, 0);
  return iVar2;
}

