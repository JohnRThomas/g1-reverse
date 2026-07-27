#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_bt_conn__param_0034                    [param_0034; library]
 * Raw function identity: 0x0001861c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0001861c @ 0x0001861c
 * public-name: ancs_connected
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   format_bt_addr_str                       <= FUN_00018334 @ 0x00018334
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   bt_conn_disconnect_by_state              <= FUN_00056a68 @ 0x00056a68
 *   k_uptime_get_32                          <= FUN_0007c0c8 @ 0x0007c0c8
 *   bt_conn_get_field_0x90                   <= FUN_00081526 @ 0x00081526
 *   bt_conn_le_param_update                  <= FUN_0008157a @ 0x0008157a
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 * address symbols (name @ address):
 *   rodata_9a5ae                             @ 0x0009a5ae   [INLINED -- G6 literal batch]
 *   rodata_9a5d8                             @ 0x0009a5d8   [INLINED -- G6 literal batch]
 *   rodata_9a5f4                             @ 0x0009a5f4   [INLINED -- G6 literal batch]
 *   rodata_9b1b9                             @ 0x0009b1b9   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_ancs_conn_param                        @ 0x20002f60
 *   g_ancs_active_conn                       @ 0x20006ab8
 *   g_ancs_conn                              @ 0x20007518
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed ancs_connected @ 0x1861c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
extern int get_device_info(void);
extern void format_bt_addr_str(unsigned, void*);
extern int is_battery_critical(void);
extern void bt_conn_disconnect_by_state(int,int);
extern unsigned int k_uptime_get_32(void);
extern int bt_conn_get_field_0x90(int);
extern void bt_conn_le_param_update(int,unsigned);
extern int memcmp(int,unsigned,int);
void ancs_connected(int param_1, int param_2)
{
  unsigned char bVar1, bVar2;
  int *piVar3; unsigned uVar4; int iVar5; unsigned uVar6;
  unsigned char auStack_38[32];
  uVar4 = bt_conn_get_field_0x90(param_1);
  format_bt_addr_str(uVar4, auStack_38);
  bVar1 = *(unsigned char*)(param_1+2);
  bVar2 = *(unsigned char*)(param_1+3);
  iVar5 = get_device_info();
  uVar6 = (unsigned)*(unsigned char*)(iVar5+0x1071);
  log_message(((unsigned long)"%s -- type: 0x%x, role:0x%x force_bind %d") /*=0x9a5ae*/, auStack_38, (unsigned)bVar1, (unsigned)bVar2, uVar6);
  if (param_2 == 0) {
    iVar5 = is_battery_critical();
    if ((iVar5 == 0) && (iVar5 = get_device_info(), *(char*)(iVar5+0x1071) == 0)) {
      iVar5 = get_device_info();
      iVar5 = memcmp(iVar5+0x1069, uVar4, 7);
      if (iVar5 != 0) {
        if (0 < *(int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
          if (*(int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
            log_message(((unsigned long)"%s(): disconnect because invalid mac %s -- type: 0x%x, role:0x%x \n\n") /*=0x9a5f4*/, ((unsigned long)"ancs_connected") /*=0x9b1b9*/, auStack_38,
                        (unsigned)*(unsigned char*)(param_1+2), (unsigned)*(unsigned char*)(param_1+3));
          else
            debug_print(((unsigned long)"%s(): disconnect because invalid mac %s -- type: 0x%x, role:0x%x \n\n") /*=0x9a5f4*/, ((unsigned long)"ancs_connected") /*=0x9b1b9*/, auStack_38,
                         (unsigned)*(unsigned char*)(param_1+2),
                         (unsigned)*(unsigned char*)(param_1+3));
        }
        bt_conn_disconnect_by_state(param_1, 5);
        return;
      }
    }
    bt_conn_le_param_update(param_1, ((unsigned long)&g_ancs_conn_param) /*=0x20002f60*/);
    iVar5 = get_device_info();
    uVar4 = k_uptime_get_32();
    *(volatile unsigned*)(iVar5+0xae4) = uVar4;
    iVar5 = get_device_info();
    uVar4 = k_uptime_get_32();
    piVar3 = (int*)((unsigned long)&g_ancs_active_conn) /*=0x20006ab8*/;
    *(volatile unsigned*)(iVar5+0xae8) = uVar4;
    iVar5 = *piVar3;
    *(volatile unsigned char*)(iVar5+0x365) = 1;
    *(volatile unsigned char*)(iVar5+0x367) = 1;
    *(volatile int*)((unsigned long)&g_ancs_conn) /*=0x20007518*/ = param_1;
  }
  else if (0 < *(int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
    if (*(int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
      log_message(((unsigned long)"%s(): failed (err 0x%02x)\n\n") /*=0x9a5d8*/, ((unsigned long)"ancs_connected") /*=0x9b1b9*/, param_2, 0, uVar6);
    else
      debug_print(((unsigned long)"%s(): failed (err 0x%02x)\n\n") /*=0x9a5d8*/, ((unsigned long)"ancs_connected") /*=0x9b1b9*/, param_2,
                   *(volatile unsigned*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/, uVar6);
  }
  return;
}
