#include "g1_app_symbols.h"
/* named: gatt_parse_find_info_rsp */
/* Reconstructed gatt_parse_find_info_rsp @ 0x5c0bc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int  bt_uuid_cmp(void*, ...);
extern void FUN_00082a42(int,int,void*);
extern int  gatt_discover_next(int,int,int*);
extern void memset_bytes(void*,int,int);

void gatt_parse_find_info_rsp(unsigned int param_1,int param_2,unsigned char *param_3,
                  int param_4,int *param_5){
  int local_5c = (int)param_1;
  volatile unsigned char *pp3 = (volatile unsigned char*)param_3;
  volatile int *pp5 = (volatile int*)param_5;
  unsigned int uVar2, uVar5, local_60, local_64;
  int iVar3, bVar1;
  char local_50 = 0;
  unsigned int off;

  if (param_2 != 0) goto LAB_0f2;
  uVar2 = pp3[0];
  if (uVar2 == 1) { uVar2 = 4; local_50 = 0; }
  else {
    if (uVar2 != 2) { FUN_00082a42(((uintptr_t)&tbl_880d8) /*=0x88128*/,0x1840,(void*)0); goto LAB_0f2; }
    uVar2 = 0x12; local_50 = 2;
  }
  uVar5 = (unsigned int)(param_4 - 1) & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
  if (uVar2 > uVar5) goto LAB_0f2;
  bVar1 = 0;
  uVar5 = uVar5 / uVar2;
  off = 1;
  local_60 = 0;
  for (;;) {
    if (uVar5 == 0) { gatt_discover_next(local_5c, local_60, param_5); return; }
    local_64 = *(volatile unsigned short*)(param_3 + off);
    local_60 = local_64;
    if (bVar1) { goto LAB_1ec; }
    /* local_50==0 / ==2 copies are stack-only, omitted */
    if ((pp5[0] != 0) && (iVar3 = bt_uuid_cmp((void*)&local_50), iVar3 != 0)) goto LAB_1ec;
    if ((char)pp5[4] == 4) {
      iVar3 = bt_uuid_cmp((void*)&local_50);
      if (iVar3 != 0) {
        iVar3 = bt_uuid_cmp((void*)&local_50);
        if (iVar3 != 0) {
          iVar3 = bt_uuid_cmp((void*)&local_50);
          if (iVar3 != 0) {
            iVar3 = bt_uuid_cmp((void*)&local_50);
            if (iVar3 != 0) goto LAB_1f8;
            bVar1 = 1; goto LAB_1f0;
          }
        }
      }
      goto LAB_1ec;
    }
LAB_1f8:
    memset_bytes((void*)0,0,0x10);
    iVar3 = ((int(*)(int,void*,int*))(pp5[1]))(local_5c,(void*)0,param_5);
    if (iVar3 == 0) return;
    goto LAB_1f0;
LAB_1ec:
    bVar1 = 0;
LAB_1f0:
    uVar5 = uVar5 - 1;
    off = off + uVar2;
  }
LAB_0f2:
  ((int(*)(int,int,int*))(pp5[1]))(local_5c,0,param_5);
  return;
}

