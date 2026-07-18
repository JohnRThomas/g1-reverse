#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005505c @ 0x0005505c
 * public-name: bt_id_add
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_id_add_part_0                         <= FUN_00054ea8 @ 0x00054ea8
 *   bt_id_add                                <= FUN_0005505c @ 0x0005505c
 * address symbols (name @ address):
 *   g_ble_dev_state                          @ 0x20002000
 */
/* Reconstructed FUN_0005505c @ 0x5505c  true code extent: 0x34 bytes */
extern void bt_id_add_part_0(unsigned char *identity);
void bt_id_add(unsigned char *param_1){
  if (param_1 == 0) return;
  volatile unsigned char *g = (volatile unsigned char*)((unsigned long)&g_ble_dev_state) /*=0x20002000*/;
  unsigned char b120 = g[0x120];
  unsigned char b121 = g[0x121];
  if (b120 == 0 || b120 < b121) {
    g[0x121] = (unsigned char)(b121 + 1);
    *(volatile unsigned char*)(param_1 + 8) = *(volatile unsigned char*)(param_1 + 8) | 4;
    return;
  }
  bt_id_add_part_0(param_1);
}
