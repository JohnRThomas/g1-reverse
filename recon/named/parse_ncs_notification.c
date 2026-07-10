/* named: parse_ncs_notification */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed parse_ncs_notification @ 0x34980  (parity: 300/300 trials, PROVEN) */
extern void DEBUG_PRINT(int,...);
extern void debug_print(void);
extern int  strcmp(int,int);
extern int  log_notification_fields_debug(int,int*);
extern int  cjson_delete(int);
extern int  get_timestamp(void);
extern int  FUN_0008500c(void);
extern int  sllist_find_by_name_ci(int,int);
extern void memset_bytes(int*,int,int);
extern void strncpy_zero_pad(int,int,int);
#define VI(a) (*(volatile int*)(a))

void parse_ncs_notification(int param_1, int *param_2){
  volatile int *lvl=(volatile int*)0x2000230cUL;
  volatile int *g8=(volatile int*)0x20007554UL;
  int iVar1,iVar2,iVar3,iVar4,iVar5,iVar6,iVar7,iVar8,iVar9;
  (void)param_1;
  iVar1 = FUN_0008500c();
  if (iVar1 == 0) {
    if (0 < *lvl) {
      if (*g8 != 0) { debug_print(); return; }
      DEBUG_PRINT(0x000a838d,0x000a83e9); return;
    }
    return;
  }
  iVar2 = sllist_find_by_name_ci(iVar1, 0x0009d79d);
  if (iVar2 == 0) {
    if (0 < *lvl) { if (*g8==0) DEBUG_PRINT(0x000a83aa,0x000a83e9); else debug_print(); }
    cjson_delete(iVar1);
    return;
  }
  iVar3 = sllist_find_by_name_ci(iVar2, 0x0009d759);
  iVar4 = sllist_find_by_name_ci(iVar2, 0x0009b257);
  iVar5 = sllist_find_by_name_ci(iVar2, 0x0009d76c);
  iVar6 = sllist_find_by_name_ci(iVar2, 0x0009d775);
  iVar7 = sllist_find_by_name_ci(iVar2, 0x000f3fde);
  iVar8 = sllist_find_by_name_ci(iVar2, 0x0009d790);
  iVar9 = sllist_find_by_name_ci(iVar2, 0x000a83ca);
  iVar2 = sllist_find_by_name_ci(iVar2, 0x000a83d1);
  memset_bytes(param_2,0,0x1b4);
  if (iVar3 != 0) {
    strncpy_zero_pad((int)(param_2+4), VI(iVar3+0x10), 0x1f);
    if (strcmp(VI(iVar3+0x10), 0x000a81b7) == 0)
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
  log_notification_fields_debug(0x000a83d8, param_2);
}

