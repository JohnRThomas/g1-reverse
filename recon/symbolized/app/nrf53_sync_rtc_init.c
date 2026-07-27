#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004c2d4 @ 0x0004c2d4
 * public-name: nrf53_sync_rtc_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf53_ipc_channel_configure              <= FUN_0004c278 @ 0x0004c278
 *   nrf53_sync_rtc_init                      <= FUN_0004c2d4 @ 0x0004c2d4
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   rtc_timer_channel_alloc                  <= FUN_0006385c @ 0x0006385c
 *   nrfx_gppi_channels_enable                <= FUN_00064f30 @ 0x00064f30
 *   flag32_channel_alloc_wrapper             <= FUN_0006540c @ 0x0006540c
 *   dppi_channel_disable_and_free            <= FUN_00065418 @ 0x00065418
 * address symbols (name @ address):
 *   ADDR_nrf53_sync_rtc_ipc_channel_setup_THUMB @ 0x0004c419
 *   rodata_87bd8                             @ 0x00087bd8
 *   rodata_88288                             @ 0x00088288
 *   rodata_f0a68                             @ 0x000f0a68
 */
/* Reconstructed FUN_0004c2d4 @ 0x4c2d4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void nrf53_ipc_channel_configure(uint32_t,uint32_t,uint32_t,int);
extern void z_log_msg_runtime_create(unsigned int, unsigned int, unsigned int, unsigned int);
extern int rtc_timer_channel_alloc(void);
extern void nrfx_gppi_channels_enable(uint32_t);
extern int flag32_channel_alloc_wrapper(int);
extern void dppi_channel_disable_and_free(uint32_t);

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

int nrf53_sync_rtc_init(void){
  uint8_t *puVar1;
  int iVar2;
  volatile uint32_t local_1c;
  iVar2 = flag32_channel_alloc_wrapper((void*)&local_1c);
  if (iVar2 == 0x0bad0000){
    iVar2 = rtc_timer_channel_alloc();
    puVar1 = (uint8_t*)((unsigned long)&rodata_87bd8) /*=0x87bd8*/;
    if (iVar2 < 0){
      dppi_channel_disable_and_free(local_1c & 0xff);
    } else {
      const struct rtc_sync_driver_api *api =
          *(const struct rtc_sync_driver_api **)(((unsigned long)&rodata_87bd8) /*=0x87bd8*/ + 8);
      *(volatile uint8_t*)((volatile char*)&local_1c+1) = (uint8_t)iVar2;
      *(volatile uint16_t*)((volatile char*)&local_1c+2) = 0x807;
      if (api->setup != 0){
        iVar2 = api->setup((void *)((unsigned long)&rodata_87bd8) /*=0x87bd8*/, 8, ADDR_nrf53_sync_rtc_ipc_channel_setup_THUMB /*=0x4c419*/, local_1c);
        if (iVar2 < 0) goto LAB;
        if (api->enable != 0){
          iVar2 = api->enable(puVar1, 8, 1);
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
  {
    struct rtc_sync_error_record diagnostic = {
      3, (const void *)((unsigned long)&rodata_f0a68) /*=0xf0a68*/, iVar2
    };
    z_log_msg_runtime_create(((unsigned long)&rodata_88288) /*=0x88288*/, 0x1840, (void *)&diagnostic, 0);
  }
  return iVar2;
}
