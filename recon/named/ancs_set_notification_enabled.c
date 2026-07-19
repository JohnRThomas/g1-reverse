/* readable reconstruction; identity: FUN_00019ac0 @ 0x00019ac0
 * public-name: ancs_set_notification_enabled
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   ancs_discover_start                      <= FUN_000182c8 @ 0x000182c8
 *   ancs_cancel_timers                       <= FUN_00018ab0 @ 0x00018ab0
 *   ancs_set_notification_enabled            <= FUN_00019ac0 @ 0x00019ac0
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   g_ancs_conn                              @ 0x20007518
 */
/* Reconstructed FUN_00019ac0 @ 0x19ac0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int get_device_info(void);
extern void ancs_discover_start(uint32_t);
extern void ancs_cancel_timers(void);
extern void k_sem_give(int);
int ancs_set_notification_enabled(int param_1){
  int iVar1;
  ancs_cancel_timers();
  if(param_1==0){
    iVar1=get_device_info();
    if(*(volatile uint8_t*)(iVar1+0x1070)!=1) return 0;
    iVar1=get_device_info();
    *(volatile uint8_t*)(iVar1+0x1070)=0;
  } else {
    uint32_t active = *(volatile uint32_t*)0x20007518UL;
    if(active==0) return 0;
    ancs_discover_start(active);
    iVar1=get_device_info();
    if(*(volatile uint8_t*)(iVar1+0x1070)!=0) return 0;
    iVar1=get_device_info();
    *(volatile uint8_t*)(iVar1+0x1070)=1;
  }
  iVar1=get_device_info();
  *(volatile uint32_t*)(iVar1+0x104c)=0;
  iVar1=get_device_info();
  k_sem_give(iVar1+0x80);
  return 0;
}
