#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00082fd2 @ 0x00082fd2
 * public-name: bt_gatt_pairing_complete
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_store_cf                         <= FUN_0005a8bc @ 0x0005a8bc
 *   bt_gatt_store_ccc                        <= FUN_0005c80c @ 0x0005c80c
 *   bt_gatt_pairing_complete                 <= FUN_00082fd2 @ 0x00082fd2
 */
/* Reconstructed FUN_00082fd2 @ 0x82fd2  (parity: 300/300 trials, PROVEN) */

extern int bt_gatt_store_ccc(unsigned int, unsigned int);
extern void bt_gatt_store_cf(unsigned char,int,unsigned int,unsigned int);
void bt_gatt_pairing_complete(int param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  if (param_2 != 0) {
    bt_gatt_store_ccc(*(volatile unsigned char *)(param_1 + 8), param_1 + 0x90);
    bt_gatt_store_cf(*(volatile unsigned char *)(param_1 + 8), param_1 + 0x90, param_3, param_4);
    return;
  }
  return;
}
