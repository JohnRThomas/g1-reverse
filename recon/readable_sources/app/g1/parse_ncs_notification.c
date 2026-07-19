#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_param_0101_false_union__param_0101     [param_0101; G1-original]
 * Raw function identity: 0x00034980.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00034980 @ 0x00034980
 * public-name: parse_ncs_notification
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strcmp                                   <= FUN_0000eefe @ 0x0000eefe
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   log_notification_fields_debug            <= FUN_0004a3d0 @ 0x0004a3d0
 *   cjson_delete                             <= FUN_00064b1c @ 0x00064b1c
 *   get_timestamp                            <= FUN_0007d224 @ 0x0007d224
 *   cbor_decode_start_default                <= FUN_0008500c @ 0x0008500c
 *   sllist_find_by_name_ci                   <= FUN_0008503c @ 0x0008503c
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 *   strncpy_zero_pad                         <= FUN_0008705a @ 0x0008705a
 * address symbols (name @ address):
 *   rodata_9b257                             @ 0x0009b257
 *   rodata_9d759                             @ 0x0009d759
 *   rodata_9d76c                             @ 0x0009d76c
 *   rodata_9d775                             @ 0x0009d775
 *   rodata_9d790                             @ 0x0009d790
 *   rodata_9d79d                             @ 0x0009d79d
 *   rodata_a81b7                             @ 0x000a81b7
 *   rodata_a838d                             @ 0x000a838d
 *   rodata_a83aa                             @ 0x000a83aa
 *   rodata_a83ca                             @ 0x000a83ca
 *   rodata_a83d1                             @ 0x000a83d1
 *   rodata_a83d8                             @ 0x000a83d8
 *   rodata_a83e9                             @ 0x000a83e9
 *   rodata_f3fde                             @ 0x000f3fde
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed parse_ncs_notification @ 0x34980  (parity: 300/300 trials, PROVEN) */
extern void log_message(int,...);
extern void debug_print(void);
extern int  strcmp(int,int);
extern int  log_notification_fields_debug(int,int*);
extern int  cjson_delete(int);
extern int  get_timestamp(void);
extern int  cbor_decode_start_default(void);
extern int  sllist_find_by_name_ci(int,int);
extern void memset_bytes(int*,int,int);
extern void strncpy_zero_pad(int,int,int);
#define VI(a) (*(volatile int*)(a))

void parse_ncs_notification(int param_1, int *param_2){
  volatile int *lvl=(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
  volatile int *g8=(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
  int iVar1,iVar2,iVar3,iVar4,iVar5,iVar6,iVar7,iVar8,iVar9;
  (void)param_1;
  iVar1 = cbor_decode_start_default();
  if (iVar1 == 0) {
    if (0 < *lvl) {
      if (*g8 != 0) { debug_print(); return; }
      log_message(((unsigned long)&rodata_a838d) /*=0xa838d*/,((unsigned long)&rodata_a83e9) /*=0xa83e9*/); return;
    }
    return;
  }
  iVar2 = sllist_find_by_name_ci(iVar1, ((unsigned long)&rodata_9d79d) /*=0x9d79d*/);
  if (iVar2 == 0) {
    if (0 < *lvl) { if (*g8==0) log_message(((unsigned long)&rodata_a83aa) /*=0xa83aa*/,((unsigned long)&rodata_a83e9) /*=0xa83e9*/); else debug_print(); }
    cjson_delete(iVar1);
    return;
  }
  iVar3 = sllist_find_by_name_ci(iVar2, ((unsigned long)&rodata_9d759) /*=0x9d759*/);
  iVar4 = sllist_find_by_name_ci(iVar2, ((unsigned long)&rodata_9b257) /*=0x9b257*/);
  iVar5 = sllist_find_by_name_ci(iVar2, ((unsigned long)&rodata_9d76c) /*=0x9d76c*/);
  iVar6 = sllist_find_by_name_ci(iVar2, ((unsigned long)&rodata_9d775) /*=0x9d775*/);
  iVar7 = sllist_find_by_name_ci(iVar2, ((unsigned long)&rodata_f3fde) /*=0xf3fde*/);
  iVar8 = sllist_find_by_name_ci(iVar2, ((unsigned long)&rodata_9d790) /*=0x9d790*/);
  iVar9 = sllist_find_by_name_ci(iVar2, ((unsigned long)&rodata_a83ca) /*=0xa83ca*/);
  iVar2 = sllist_find_by_name_ci(iVar2, ((unsigned long)&rodata_a83d1) /*=0xa83d1*/);
  memset_bytes(param_2,0,0x1b4);
  if (iVar3 != 0) {
    strncpy_zero_pad((int)(param_2+4), VI(iVar3+0x10), 0x1f);
    if (strcmp(VI(iVar3+0x10), ((unsigned long)&rodata_a81b7) /*=0xa81b7*/) == 0)
      *(volatile int*)(param_2+1) = get_timestamp();
  }
  if (iVar4 != 0) strncpy_zero_pad((int)(param_2+0x14), VI(iVar4+0x10), 0x1f);
  if (iVar6 != 0) strncpy_zero_pad((int)(param_2+0x24), VI(iVar6+0x10), 0xff);
  if (iVar5 != 0) strncpy_zero_pad((int)(param_2+0x1c), VI(iVar5+0x10), 0x1f);
  if (iVar7 != 0) strncpy_zero_pad((int)(param_2+100), VI(iVar7+0x10), 0x20);
  if (iVar8 != 0) strncpy_zero_pad((int)(param_2+0xc), VI(iVar8+0x10), 0x1f);
  if (iVar9 != 0) *(volatile int*)(param_2+2) = VI(iVar9+0x14);
  if (iVar2 != 0) *(volatile int*)(param_2+0x6c) = VI(iVar2+0x14);
  *(volatile int*)param_2 = get_timestamp();
  cjson_delete(iVar1);
  log_notification_fields_debug(((unsigned long)&rodata_a83d8) /*=0xa83d8*/, param_2);
}
