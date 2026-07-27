#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005a044 @ 0x0005a044
 * public-name: bt_gatt_clear_sc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_sc_settings_delete                  <= FUN_00053024 @ 0x00053024
 *   find_sc_cfg_59bcc                        <= FUN_00059bcc @ 0x00059bcc
 *   bt_gatt_clear_sc                         <= FUN_0005a044 @ 0x0005a044
 *   gatt_sc_ctx_clear                        <= FUN_00082928 @ 0x00082928
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f47a4                             @ 0x000f47a4
 */
/* Reconstructed FUN_0005a044 @ 0x5a044  (parity: 300/300 trials, PROVEN) */

extern void* find_sc_cfg_59bcc(void);
extern unsigned int gatt_sc_settings_delete(unsigned char*, int);
extern void log_msg_create_3arg(unsigned int, unsigned int, void*);
extern void gatt_sc_ctx_clear(unsigned int*);

unsigned int bt_gatt_clear_sc(void){
  unsigned char *puVar1 = (unsigned char*)find_sc_cfg_59bcc();
  if (puVar1 != (unsigned char*)0) {
    int iVar2 = gatt_sc_settings_delete(*puVar1, puVar1+1);
    if (iVar2 != 0) {
      struct { unsigned int a; unsigned int b; int c; } local;
      local.a = 3;
      local.b = ((unsigned long)&rodata_f47a4) /*=0xf47a4*/;
      local.c = iVar2;
      log_msg_create_3arg(((unsigned long)&rodata_88128) /*=0x88128*/, 0x1840, &local);
    }
    gatt_sc_ctx_clear(puVar1);
  }
  return 0;
}
