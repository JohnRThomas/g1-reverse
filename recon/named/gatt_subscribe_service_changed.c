/* readable reconstruction; identity: FUN_0004f418 @ 0x0004f418
 * public-name: gatt_subscribe_service_changed
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   gatt_subscribe_service_changed           <= FUN_0004f418 @ 0x0004f418
 *   gatt_subscribe_add                       <= FUN_0005c3c4 @ 0x0005c3c4
 * address symbols (name @ address):
 *   ADDR_clock_event_notify_u16pair_THUMB    @ 0x0007f895
 *   rodata_881c0                             @ 0x000881c0
 *   rodata_f1625                             @ 0x000f1625
 */
/* Reconstructed FUN_0004f418 @ 0x4f418  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int gatt_subscribe_add(int, int *);
extern void z_log_msg_runtime_create(unsigned int, unsigned int, unsigned int, unsigned int);

int gatt_subscribe_service_changed(volatile int *param_1, int param_2, uint32_t param_3, uint32_t param_4){
  int iVar1;
  unsigned uVar2;
  volatile unsigned *puVar3;
  struct {
    uint32_t count;
    uint32_t format;
    int error;
  } log_record;
  if (param_1 == 0 || *param_1 == 0 || param_2 == 0){
    iVar1 = -0x16;
  } else {
    puVar3 = (volatile unsigned*)(param_1 + 10);
    uVar2 = __atomic_fetch_or((unsigned *)puVar3, 1u, __ATOMIC_ACQ_REL);
    iVar1 = 0x7f895;
    if ((uVar2 & 1) == 0){
      param_1[9] = param_2;
      param_1[2] = iVar1;
      *(volatile int16_t*)(param_1 + 6) = 2;
      param_1[5] = param_1[1];
      (void)__atomic_fetch_or((unsigned *)&param_1[7], 1u, __ATOMIC_ACQ_REL);
      iVar1 = gatt_subscribe_add((uint32_t)*param_1, (void*)(param_1 + 2));
      if (iVar1 != 0){
        (void)__atomic_fetch_and((unsigned *)puVar3, 0xfffffffeu,
                                 __ATOMIC_ACQ_REL);
        log_record.count = 3;
        log_record.format = 0xf1625;
        log_record.error = iVar1;
        z_log_msg_runtime_create(0x881c0, 0x1840, &log_record, 0);
      }
    } else {
      iVar1 = -0x78;
    }
  }
  return iVar1;
}
