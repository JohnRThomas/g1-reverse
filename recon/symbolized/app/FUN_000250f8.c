#include "g1_app_symbols.h"
/* named: FUN_000250f8 */
/* Reconstructed FUN_000250f8 @ 0x250f8  (parity: 300/300 trials, PROVEN) */
extern int st25dv_mailbox_write_with_retry(int,int);
extern int FUN_00025090(void*,void*);
extern int FUN_000250c4(void*,void*);
extern int FUN_0007c3da(void*,void*);
extern int opt_record_decode(void*,void*);
extern int FUN_0007c77e(void*,void*);
extern int opt_list_append_node(void*,void*);

int FUN_000250f8(char *param_1, char *param_2, char *param_3){
  unsigned int uVar1,uVar2,uVar3,t; int iVar4,iVar5;
  int buf1[16], buf2[16]; int local_168=0, local_164=0;
  (void)param_1;
  uVar1 = (unsigned int)FUN_00025090(buf1, buf1);
  uVar2 = (unsigned int)FUN_0007c3da(buf1, buf1);
  uVar1 = (uVar1 | uVar2) & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
  if (*param_2 == 0) {
    iVar5 = 1;
  } else {
    iVar5 = 2;
    uVar2 = (unsigned int)FUN_000250c4(buf2, buf2);
    uVar3 = (unsigned int)FUN_0007c3da(buf2, buf2);
    uVar1 = ((uVar2 | uVar3) & ((uintptr_t)&tbl_ffc8) /*=0xffff*/) | uVar1;
  }
  if (*param_3 != 0) {
    uVar1 = (unsigned int)opt_record_decode(buf1, buf1);
    iVar5 = iVar5 + 1;
  }
  iVar4 = 0;
  *(volatile unsigned char*)((uintptr_t)&g_ndef_build_status_flag) /*=0x20018c6a*/ = 0;
  do {
    uVar2 = (unsigned int)opt_list_append_node(buf1, buf1);
    iVar4 = iVar4 + 1;
    uVar1 = (uVar2 | uVar1) & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
  } while (iVar4 != iVar5);
  uVar2 = (unsigned int)FUN_0007c77e(buf1, &local_168);
  uVar3 = (unsigned int)st25dv_mailbox_write_with_retry(local_168, local_164);
  t = (uVar1 | uVar2) & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
  t = (uVar3 | t) & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
  if (t != 0) t = 1;
  return -(int)t;
}

