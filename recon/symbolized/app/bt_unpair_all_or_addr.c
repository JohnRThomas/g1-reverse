#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005420c @ 0x0005420c
 * public-name: bt_unpair_all_or_addr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   unpair                                   <= FUN_00053380 @ 0x00053380
 *   bt_unpair_all_or_addr                    <= FUN_0005420c @ 0x0005420c
 *   bt_foreach_bond                          <= FUN_0005e6d4 @ 0x0005e6d4
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 * address symbols (name @ address):
 *   rodata_80e81                             @ 0x00080e81
 *   rodata_f2b3a                             @ 0x000f2b3a
 */
/* Reconstructed FUN_0005420c @ 0x5420c  (parity: 300/300 trials, PROVEN) */

extern int memcmp(int a,int b,int c,int d);
extern void bt_foreach_bond(int a,int b,void *c);
extern void unpair(int a,int b);
int bt_unpair_all_or_addr(int param_1,int param_2,int param_3,int param_4)
{
  int iVar1;
  int uVar2;
  char flag = (char)param_1;
  if (param_1 == 0) {
    if (param_2 == 0 || (iVar1 = memcmp(param_2, ((unsigned long)&rodata_f2b3a) /*=0xf2b3a*/, 7, param_4), iVar1 == 0)) {
      bt_foreach_bond(0, ((unsigned long)&rodata_80e81) /*=0x80e81*/, (void*)&flag);
    } else {
      unpair(0, param_2);
    }
    uVar2 = 0;
  } else {
    uVar2 = 0xffffffea;
  }
  return uVar2;
}
