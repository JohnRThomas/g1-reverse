/* named: ancs_security_changed */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20006ab4  g_gatt_discovery_flags       
//   0x20006ab8  g_ancs_active_conn           
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed ancs_security_changed @ 0x184f0  (parity: 161/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int get_device_info(int,...);
extern int ancs_discover_start(int,...);
extern int format_bt_addr_str(int,...);
extern int debug_print(int,...);
extern int is_battery_critical(int,...);
extern int sys_reboot(int,...);
extern int FUN_0007c0a8(int,...);
extern int bt_conn_set_security(int,...);
extern int bt_conn_get_security(int,...);
extern int FUN_00081526(int,...);
extern int memcmp(int,...);
void ancs_security_changed(int param_1, int param_2, int param_3)
{
  unsigned char stack38[32];
  volatile int *piVar1 = (volatile int*)0x2000230cUL;
  volatile int *piVar2 = (volatile int*)0x20006a34UL;
  volatile int *E = (volatile int*)0x20007554UL;
  int uVar3 = FUN_00081526(0);
  format_bt_addr_str(uVar3, (int)stack38);
  int iVar5 = *piVar1;
  if (param_3 == 0) {
    if (2 < iVar5) {
      if (*E == 0) DEBUG_PRINT(0x9a52b,0x9b229,(int)stack38,param_2);
      else debug_print(0x9a52b,0x9b229,(int)stack38,param_2);
    }
    unsigned int uVar4 = (unsigned int)bt_conn_get_security(param_1);
    if (1 < uVar4) {
      *(volatile int*)0x20006ab4UL = 0;
      uVar3 = FUN_00081526(param_1);
      iVar5 = is_battery_critical(0);
      if (iVar5 == 0) {
        iVar5 = get_device_info(0);
        if (*(char*)(iVar5+0x1070) == 1) {
          iVar5 = get_device_info(0);
          iVar5 = memcmp(iVar5+0x1069, uVar3, 7);
          if (iVar5 == 0) ancs_discover_start(param_1);
        }
      }
    }
    *(volatile unsigned char*)(*(volatile int*)0x20006ab8UL + 0x367) = 0;
    *piVar2 = 0;
  } else {
    if (2 < iVar5) {
      if (*E == 0) goto LAB_185da;
      debug_print(0x9a53f,0x9b229,(int)stack38,param_2,param_3);
    }
    while (1) {
      iVar5 = *piVar2;
      *piVar2 = iVar5 + 1;
      if (iVar5 + 1 < 10) break;
      if (0 < *piVar1) {
        if (*E == 0) DEBUG_PRINT(0x9a56b,0x9b229);
        else debug_print(0);
      }
      FUN_0007c0a8(500);
      sys_reboot(1);
    LAB_185da:
      DEBUG_PRINT(0x9a53f,0x9b229,(int)stack38,param_2);
    }
    bt_conn_set_security(param_1,2);
  }
}

