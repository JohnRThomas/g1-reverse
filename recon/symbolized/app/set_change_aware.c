#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00082bb8 @ 0x00082bb8
 * public-name: set_change_aware
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_delayed_store_enqueue               <= FUN_00059d24 @ 0x00059d24
 *   set_change_aware_no_store                <= FUN_00082b98 @ 0x00082b98
 *   set_change_aware                         <= FUN_00082bb8 @ 0x00082bb8
 */
/* Reconstructed FUN_00082bb8 @ 0x82bb8  (parity: 300/300 trials, PROVEN) */

extern int set_change_aware_no_store(void);
extern void gatt_delayed_store_enqueue(unsigned char,unsigned char*,unsigned int);
void set_change_aware(unsigned char *param_1)
{
  int iVar1 = set_change_aware_no_store();
  if (iVar1 != 0) {
    gatt_delayed_store_enqueue(*(volatile unsigned char *)param_1, param_1 + 1, 1);
  }
}
