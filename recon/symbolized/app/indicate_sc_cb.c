#include "g1_app_symbols.h"
/* named: indicate_sc_cb */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20006ab4  g_gatt_discovery_flags       
//   0x20007554  g_log_use_alt_sink           
//   0x2000ff70  g_ble_indicate_sc_retry_count 
*/
/* Reconstructed indicate_sc_cb @ 0x18a38  (parity: 300/300 trials, PROVEN) */

extern int gatt_discover(unsigned int, int);
extern void debug_print(void);
extern int FUN_00056a68(unsigned int, int);
extern int DEBUG_PRINT(int, ...);

void indicate_sc_cb(unsigned int *param_1, unsigned int param_2, int param_3)
{
  unsigned char bVar1;

  if (param_3 != 0) return;
  bVar1 = *(volatile unsigned char*)((uintptr_t)&g_ble_indicate_sc_retry_count) /*=0x2000ff70*/;
  bVar1 = bVar1 + 1;
  *(volatile unsigned char*)((uintptr_t)&g_ble_indicate_sc_retry_count) /*=0x2000ff70*/ = bVar1;
  if (bVar1 < 5) {
    *(volatile unsigned int*)((uintptr_t)&g_gatt_discovery_flags) /*=0x20006ab4*/ |= 4;
    gatt_discover(*param_1, 1);
    return;
  }
  *(volatile unsigned char*)((uintptr_t)&g_ble_indicate_sc_retry_count) /*=0x2000ff70*/ = 0;
  if (*(int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 0) {
    if (*(int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
      DEBUG_PRINT("%s(): disconnect because can not discover ancs.\n" /*=0x9a8f9*/, "indicate_sc_cb" /*=0x9b1da*/);
    } else {
      debug_print();
    }
  }
  FUN_00056a68(*param_1, 0x13);
}

