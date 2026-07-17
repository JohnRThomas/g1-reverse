/* readable reconstruction; identity: FUN_0007cbfe @ 0x0007cbfe
 * public-name: set_shutdown_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   check_battery_critical                   <= FUN_0002bed0 @ 0x0002bed0
 *   update_persist_task_status_to_idle       <= FUN_0002c0e8 @ 0x0002c0e8
 *   mark_master_or_low_battery_flag          <= FUN_0002efc0 @ 0x0002efc0
 *   reset_esb_sync_state                     <= FUN_0007ce60 @ 0x0007ce60
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed set_shutdown_flag @ 0x7cbfe  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int check_battery_critical(void);
extern void update_persist_task_status_to_idle(int);
extern void mark_master_or_low_battery_flag(void);
extern void reset_esb_sync_state(int);
extern void memset_bytes(int,int,int);
extern void send_event_status(int);
void set_shutdown_flag(int param_1, int param_2)
{
  int iVar1; char *pcVar2; char cVar3;
  iVar1 = check_battery_critical();
  if (iVar1 == 0) return;
  if ((*(volatile char*)(*(int*)(param_1+0x1004)+6) != 0) ||
      (cVar3 = *(volatile char*)(*(int*)(param_1+0x1008)+6), cVar3 != 0)) {
    mark_master_or_low_battery_flag();
    memset_bytes(*(int*)(param_1+0x1008)+6, 0, 400);
    memset_bytes(*(int*)(param_1+0x1004)+6, 0, 400);
    cVar3 = 1;
  }
  if (**(char**)(param_1+0x1000) != 0) { **(volatile char**)(param_1+0x1000) = 0; cVar3 = 1; }
  if (*(char*)(*(int*)(param_1+0xffc)+1) != 0) { mark_master_or_low_battery_flag(); *(volatile char*)(*(int*)(param_1+0xffc)+1) = 0; cVar3 = 1; }
  if (**(char**)(param_1+0x1020) != 0) { mark_master_or_low_battery_flag(); **(volatile char**)(param_1+0x1020) = 0; cVar3 = 1; }
  if (*(char*)(param_1+0xd5) == 6) { cVar3 = 1; }
  else if (*(char*)(param_1+0xd5) == 4) { cVar3 = 1; }
  if (**(char**)(param_1+0x1014) != 0) { **(volatile char**)(param_1+0x1014) = 0; cVar3 = 1; }
  if (**(char**)(param_1+0x1018) != 0) { **(volatile char**)(param_1+0x1018) = 0; cVar3 = 1; }
  if (*(char*)(*(int*)(param_1+0x100c)+7) == 0) {
    pcVar2 = *(char**)(param_1+0x101c);
    if (*pcVar2 == 0) {
      if (cVar3 == 0) return;
      goto LAB;
    }
  } else {
    mark_master_or_low_battery_flag();
    reset_esb_sync_state(1);
    pcVar2 = *(char**)(param_1+0x101c);
    if (*pcVar2 == 0) goto LAB;
  }
  *(volatile char*)pcVar2 = 0;
LAB:
  if (param_2 != 0) send_event_status(0);
  update_persist_task_status_to_idle(param_1);
  memset_bytes(param_1+0xef, 0, 0x5dc);
  return;
}
