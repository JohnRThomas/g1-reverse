#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_param_0101_false_union__param_0101     [param_0101; G1-original]
 * Raw function identity: 0x0005ea18.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0005ea18 @ 0x0005ea18
 * public-name: bt_keys_clear
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_settings_save_or_delete_key           <= FUN_00053184 @ 0x00053184
 *   ble_privacy_id_remove                    <= FUN_00055094 @ 0x00055094
 *   bt_keys_clear                            <= FUN_0005ea18 @ 0x0005ea18
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f5268                             @ 0x000f5268
 *   rodata_f5298                             @ 0x000f5298   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0005ea18 @ 0x5ea18  (parity: 300/300 trials, PROVEN) */

extern void printk(int a,int b,int c,int d);
extern unsigned char *assert_post_action(int a,int b);
extern void ble_privacy_id_remove(void);
extern void bt_settings_save_or_delete_key(unsigned char a, unsigned char *b);
extern void memset_bytes(void *a, int b, int c);

void bt_keys_clear(unsigned char *param_1)
{
  unsigned char *r0 = param_1;
  if (param_1 == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"keys != ((void *)0)") /*=0xf5298*/, ((unsigned long)&rodata_f5268) /*=0xf5268*/, 0x131);
    r0 = assert_post_action(((unsigned long)&rodata_f5268) /*=0xf5268*/, 0x131);
  }
  unsigned char b8 = *(volatile unsigned char*)(r0 + 8);
  if ((int)((unsigned int)b8 << 0x1d) < 0) {
    ble_privacy_id_remove();
  }
  bt_settings_save_or_delete_key(*param_1, param_1 + 1);
  memset_bytes(param_1, 0, 0x5c);
}
