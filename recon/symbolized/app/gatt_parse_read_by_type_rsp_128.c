#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005c004 @ 0x0005c004
 * public-name: gatt_parse_read_by_type_rsp_128
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_parse_read_by_type_rsp_128          <= FUN_0005c004 @ 0x0005c004
 *   bt_uuid_cmp                              <= FUN_00080d3e @ 0x00080d3e
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 *   gatt_discover_next                       <= FUN_00082d2e @ 0x00082d2e
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f4ca8                             @ 0x000f4ca8
 */
/* Reconstructed FUN_0005c004 @ 0x5c004  (parity: 200/200 trials, PROVEN) */

#include <stdint.h>
typedef int (*codep)(int,void*,int*);
extern int bt_uuid_cmp(void);
extern void log_msg_create_3arg(int,int,void*);
extern void gatt_discover_next(int,short,int*);
extern void memset_bytes(void*,int,int);
void gatt_parse_read_by_type_rsp_128(int param_1,int param_2,unsigned *param_3,int param_4,int *param_5){
  int iVar1; int iVar2; unsigned *puVar3; unsigned *puVar5; unsigned *puVar4;
  unsigned local_60; unsigned local_5c; int iStack_58;
  unsigned char local_4c[2]; unsigned short local_4a; unsigned char *local_48;
  unsigned short local_44; unsigned short local_42; unsigned char local_40;
  unsigned auStack_3f[4]; unsigned char *local_2c; unsigned char auStack_28[8];
  unsigned char **local_20; unsigned short local_1c;
  if (param_4 == 0x10) {
    local_44 = *(unsigned short *)((int)param_5 + 10);
    local_48 = &local_40;
    local_42 = (unsigned short)param_5[3];
    iVar1 = param_5[2];
    local_40 = 2;
    puVar3 = param_3; puVar5 = auStack_3f;
    do { puVar4 = puVar3 + 1; *puVar5 = *puVar3; puVar3 = puVar4; puVar5 = puVar5 + 1; } while (puVar4 != param_3 + 4);
    if ((*param_5 == 0) || (iVar2 = bt_uuid_cmp(), iVar2 == 0)) {
      local_4c[0] = 0; local_4a = 0x2802;
      memset_bytes(auStack_28,0,0x10);
      local_2c = local_4c; local_20 = &local_48; local_1c = (short)iVar1;
      iVar1 = ((codep)param_5[1])(param_1,&local_2c,param_5);
      if (iVar1 == 0) { return; }
    }
    gatt_discover_next(param_1,(short)param_5[2],param_5);
  } else {
    local_5c = ((unsigned long)&rodata_f4ca8) /*=0xf4ca8*/; local_60 = 3; iStack_58 = param_4;
    log_msg_create_3arg(((unsigned long)&rodata_88128) /*=0x88128*/,0x1840,&local_60);
    ((codep)param_5[1])(param_1,0,param_5);
  }
  return;
}
