/* Reconstructed FUN_0004c2d4 @ 0x4c2d4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_0004c278(uint32_t,uint32_t,uint32_t,int);
extern void FUN_0004d944(uint32_t,int,void*,...);
extern int FUN_0006385c(void);
extern void FUN_00064f30(uint32_t);
extern int FUN_0006540c(void*);
extern void FUN_00065418(uint32_t);

typedef int (*rtc_setup_callback_t)(void *, uint32_t, uintptr_t, uint32_t);
typedef int (*rtc_enable_callback_t)(void *, uint32_t, uint32_t);

struct rtc_sync_driver_api {
  uint32_t reserved_0;
  rtc_setup_callback_t setup;
  uint32_t reserved_8;
  uint32_t reserved_c;
  rtc_enable_callback_t enable;
};

struct rtc_sync_error_record {
  uint32_t argument_count;
  const void *format;
  int error;
};

int FUN_0004c2d4(void){
  uint8_t *puVar1;
  int iVar2;
  volatile uint32_t local_1c;
  iVar2 = FUN_0006540c((void*)&local_1c);
  if (iVar2 == 0x0bad0000){
    iVar2 = FUN_0006385c();
    puVar1 = (uint8_t*)0x87bd8UL;
    if (iVar2 < 0){
      FUN_00065418(local_1c & 0xff);
    } else {
      const struct rtc_sync_driver_api *api =
          *(const struct rtc_sync_driver_api **)(0x87bd8UL + 8);
      *(volatile uint8_t*)((volatile char*)&local_1c+1) = (uint8_t)iVar2;
      *(volatile uint16_t*)((volatile char*)&local_1c+2) = 0x807;
      if (api->setup != 0){
        iVar2 = api->setup((void *)0x87bd8, 8, 0x4c419, local_1c);
        if (iVar2 < 0) goto LAB;
        if (api->enable != 0){
          iVar2 = api->enable(puVar1, 8, 1);
          if (iVar2 >= 0){
            FUN_00064f30(1u << (local_1c & 0xff));
            FUN_0004c278(local_1c & 0xff, (local_1c>>8)&0xff, (local_1c>>24)&0xff, 1);
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
  {
    struct rtc_sync_error_record diagnostic = {
      3, (const void *)0xf0a68, iVar2
    };
    FUN_0004d944(0x88288, 0x1840, (void *)&diagnostic, 0);
  }
  return iVar2;
}
