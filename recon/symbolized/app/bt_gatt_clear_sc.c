#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005a044 @ 0x0005a044
 * public-name: bt_gatt_clear_sc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   find_sc_cfg_59bcc                        <= FUN_00059bcc @ 0x00059bcc
 *   bt_gatt_clear_sc                         <= FUN_0005a044 @ 0x0005a044
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f47a4                             @ 0x000f47a4
 */
/* Reconstructed FUN_0005a044 @ 0x5a044  (parity: 300/300 trials, PROVEN) */

extern void* find_sc_cfg_59bcc(void);
extern int FUN_00053024(unsigned char, void*);
extern void FUN_00082a42(unsigned int, unsigned int, void*);
extern void FUN_00082928(void*);

unsigned int bt_gatt_clear_sc(void){
  unsigned char *puVar1 = (unsigned char*)find_sc_cfg_59bcc();
  if (puVar1 != (unsigned char*)0) {
    int iVar2 = FUN_00053024(*puVar1, puVar1+1);
    if (iVar2 != 0) {
      struct { unsigned int a; unsigned int b; int c; } local;
      local.a = 3;
      local.b = ((unsigned long)&rodata_f47a4) /*=0xf47a4*/;
      local.c = iVar2;
      FUN_00082a42(((unsigned long)&rodata_88128) /*=0x88128*/, 0x1840, &local);
    }
    FUN_00082928(puVar1);
  }
  return 0;
}
