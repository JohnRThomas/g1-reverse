#include "g1_app_symbols.h"
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
  volatile int *lvl=(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
  volatile int *g8=(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
  int iVar1,iVar2,iVar3,iVar4,iVar5,iVar6,iVar7,iVar8,iVar9;
  (void)param_1;
  iVar1 = FUN_0008500c();
  if (iVar1 == 0) {
    if (0 < *lvl) {
      if (*g8 != 0) { debug_print(); return; }
      DEBUG_PRINT("%s(): error root JSON NODE!\n" /*=0xa838d*/,"parse_ncs_notification" /*=0xa83e9*/); return;
    }
    return;
  }
  iVar2 = sllist_find_by_name_ci(iVar1, "ncs_notification" /*=0x9d79d*/);
  if (iVar2 == 0) {
    if (0 < *lvl) { if (*g8==0) DEBUG_PRINT("%s(): NOT FOUND NCS JSON NODE!\n" /*=0xa83aa*/,"parse_ncs_notification" /*=0xa83e9*/); else debug_print(); }
    cjson_delete(iVar1);
    return;
  }
  iVar3 = sllist_find_by_name_ci(iVar2, "app_identifier" /*=0x9d759*/);
  iVar4 = sllist_find_by_name_ci(iVar2, "title" /*=0x9b257*/);
  iVar5 = sllist_find_by_name_ci(iVar2, "subtitle" /*=0x9d76c*/);
  iVar6 = sllist_find_by_name_ci(iVar2, "message" /*=0x9d775*/);
  iVar7 = sllist_find_by_name_ci(iVar2, "date" /*=0xf3fde*/);
  iVar8 = sllist_find_by_name_ci(iVar2, "display_name" /*=0x9d790*/);
  iVar9 = sllist_find_by_name_ci(iVar2, "msg_id" /*=0xa83ca*/);
  iVar2 = sllist_find_by_name_ci(iVar2, "action" /*=0xa83d1*/);
  memset_bytes(param_2,0,0x1b4);
  if (iVar3 != 0) {
    strncpy_zero_pad((int)(param_2+4), VI(iVar3+0x10), 0x1f);
    if (strcmp(VI(iVar3+0x10), "com.android.phone_incall" /*=0xa81b7*/) == 0)
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
  log_notification_fields_debug("#device-receiver" /*=0xa83d8*/, param_2);
}

