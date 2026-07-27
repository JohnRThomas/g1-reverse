#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_ancs_notif_ctx__param_0157             [param_0157; G1-original]
 * Raw function identity: 0x0004f040.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0004f040 @ 0x0004f040
 * public-name: ancs_subscribe_notification_source
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   ancs_subscribe_notification_source       <= FUN_0004f040 @ 0x0004f040
 *   gatt_subscribe_add                       <= FUN_0005c3c4 @ 0x0005c3c4
 *   atomic_clear_bit                         <= FUN_0007f5d8 @ 0x0007f5d8
 *   atomic_test_and_set_bit                  <= FUN_0007f612 @ 0x0007f612
 * address symbols (name @ address):
 *   ADDR_FUN_0007f634_THUMB                  @ 0x0007f635
 *   rodata_880e8                             @ 0x000880e8
 *   rodata_f159e                             @ 0x000f159e
 */
/* Reconstructed FUN_0004f040 @ 0x4f040  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int atomic_test_and_set_bit(void*, int);
extern int gatt_subscribe_add(int, int *);
extern void atomic_clear_bit(volatile int *, int);
extern void z_log_msg_runtime_create(unsigned int, unsigned int, unsigned int, unsigned int);

int ancs_subscribe_notification_source(volatile uint32_t *param_1, int param_2){
  int iVar1;
  volatile uint32_t local_28, local_24, iStack_20;
  if (param_1 == 0 || param_2 == 0){
    iVar1 = -0x16;
  } else {
    iVar1 = atomic_test_and_set_bit((void*)(param_1 + 1), 0);
    if (iVar1 == 0){
      param_1[0x20a] = ADDR_FUN_0007f634_THUMB /*=0x7f635*/;
      *(volatile uint16_t*)(param_1 + 0x20e) = 1;
      *(volatile uint16_t*)(param_1 + 0x20d) = *(volatile uint16_t*)((char*)param_1 + 10);
      *(volatile uint16_t*)((char*)param_1 + 0x836) = *(volatile uint16_t*)(param_1 + 3);
      param_1[0x20f] |= 1;
      param_1[0x211] = param_2;
      iVar1 = gatt_subscribe_add(param_1[0], (void*)(param_1 + 0x20a));
      if (iVar1 != 0){
        atomic_clear_bit((void*)(param_1 + 1), 0);
        local_24 = ((unsigned long)&rodata_f159e) /*=0xf159e*/;
        local_28 = 3;
        iStack_20 = iVar1;
        z_log_msg_runtime_create(((unsigned long)&rodata_880e8) /*=0x880e8*/, 0x1840, (void*)&local_28, 0);
      }
    } else {
      iVar1 = -0x78;
    }
  }
  return iVar1;
}
