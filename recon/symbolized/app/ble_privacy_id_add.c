#include "g1_app_symbols.h"
/* named: ble_privacy_id_add */
/* globals referenced:
//   0x20002000  g_ble_dev_state              
*/
/* Reconstructed ble_privacy_id_add @ 0x5505c  (parity: 300/300 trials, PROVEN) */
extern void TAIL_54ea8(void);
void ble_privacy_id_add(unsigned char *param_1){
  if (param_1 == 0) return;
  volatile unsigned char *g = (volatile unsigned char*)((uintptr_t)&g_ble_dev_state) /*=0x20002000*/;
  unsigned char b120 = g[0x120];
  unsigned char b121 = g[0x121];
  if (b120 == 0 || b120 < b121) {
    g[0x121] = (unsigned char)(b121 + 1);
    *(volatile unsigned char*)(param_1 + 8) = *(volatile unsigned char*)(param_1 + 8) | 4;
    return;
  }
  TAIL_54ea8();
}

