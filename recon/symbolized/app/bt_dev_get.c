#include "g1_app_symbols.h"
/* named: bt_dev_get */
/* globals referenced:
//   0x2000216c  g_bt_dev.name                [g_bt_dev (base 0x20002000) + 0x16c: device/BLE local-name storage buffer, max 29 bytes]
*/
/* Reconstructed bt_dev_get @ 0x54ce0  (parity: 300/300 trials, PROVEN) */

unsigned int bt_dev_get(void){
  return ((uintptr_t)&g_bt_dev_name) /*=0x2000216c*/;
}

