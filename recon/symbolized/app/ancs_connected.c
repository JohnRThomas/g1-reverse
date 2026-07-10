#include "g1_app_symbols.h"
/* named: ancs_connected */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20006ab8  g_ancs_active_conn           
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed ancs_connected @ 0x1861c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern int get_device_info(void);
extern void format_bt_addr_str(unsigned, void*);
extern void debug_print(unsigned,unsigned);
extern int is_battery_critical(void);
extern void FUN_00056a68(int,int);
extern unsigned k_uptime_get_32(void);
extern int FUN_00081526(void);
extern void bt_conn_le_param_update(int,unsigned);
extern int memcmp(int,unsigned,int);
void ancs_connected(int param_1, int param_2)
{
  unsigned char bVar1, bVar2;
  int *piVar3; unsigned uVar4; int iVar5; unsigned uVar6;
  unsigned char auStack_38[32];
  uVar4 = FUN_00081526();
  format_bt_addr_str(uVar4, auStack_38);
  bVar1 = *(unsigned char*)(param_1+2);
  bVar2 = *(unsigned char*)(param_1+3);
  iVar5 = get_device_info();
  uVar6 = (unsigned)*(unsigned char*)(iVar5+0x1071);
  DEBUG_PRINT("%s -- type: 0x%x, role:0x%x force_bind %d" /*=0x9a5ae*/, auStack_38, (unsigned)bVar1, (unsigned)bVar2, uVar6);
  if (param_2 == 0) {
    iVar5 = is_battery_critical();
    if ((iVar5 == 0) && (iVar5 = get_device_info(), *(char*)(iVar5+0x1071) == 0)) {
      iVar5 = get_device_info();
      iVar5 = memcmp(iVar5+0x1069, uVar4, 7);
      if (iVar5 != 0) {
        if (0 < *(int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
          if (*(int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
            DEBUG_PRINT("%s(): disconnect because invalid mac %s -- type: 0x%x, role:0x%x \n\n" /*=0x9a5f4*/, "ancs_connected" /*=0x9b1b9*/, auStack_38,
                        (unsigned)*(unsigned char*)(param_1+2), (unsigned)*(unsigned char*)(param_1+3));
          else
            debug_print("%s(): disconnect because invalid mac %s -- type: 0x%x, role:0x%x \n\n" /*=0x9a5f4*/, "ancs_connected" /*=0x9b1b9*/);
        }
        FUN_00056a68(param_1, 5);
        return;
      }
    }
    bt_conn_le_param_update(param_1, ((uintptr_t)&g_ancs_conn_param) /*=0x20002f60*/);
    iVar5 = get_device_info();
    uVar4 = k_uptime_get_32();
    *(volatile unsigned*)(iVar5+0xae4) = uVar4;
    iVar5 = get_device_info();
    uVar4 = k_uptime_get_32();
    piVar3 = (int*)((uintptr_t)&g_ancs_active_conn) /*=0x20006ab8*/;
    *(volatile unsigned*)(iVar5+0xae8) = uVar4;
    iVar5 = *piVar3;
    *(volatile unsigned char*)(iVar5+0x365) = 1;
    *(volatile unsigned char*)(iVar5+0x367) = 1;
    *(volatile int*)((uintptr_t)&g_ancs_conn) /*=0x20007518*/ = param_1;
  }
  else if (0 < *(int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
    if (*(int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
      DEBUG_PRINT("%s(): failed (err 0x%02x)\n\n" /*=0x9a5d8*/, "ancs_connected" /*=0x9b1b9*/, param_2, 0, uVar6);
    else
      debug_print("%s(): failed (err 0x%02x)\n\n" /*=0x9a5d8*/, "ancs_connected" /*=0x9b1b9*/);
  }
  return;
}

