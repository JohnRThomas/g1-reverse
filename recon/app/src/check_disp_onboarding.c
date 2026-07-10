/* Reconstructed check_disp_onboarding @ 0x26a08  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(int,int);
extern int FUN_000167a8(void);
extern void FUN_00019c70(void);
extern void FUN_00040708(void);
extern int FUN_00042c8c(void*,int);
extern int FUN_0007c132(void);
extern unsigned long long FUN_0007cb2c(void);
extern void FUN_0007d39e(void);
extern void update_persist_task_status(int,int,int);
#define VB(a) (*(volatile unsigned char*)(a))
#define VI(a) (*(volatile int*)(a))

void check_disp_onboarding(int param_1, unsigned int param_2, unsigned int param_3){
  volatile char *pg70 = (volatile char*)0x20018d93UL;
  volatile unsigned char *pg74 = (volatile unsigned char*)0x2001cdceUL;
  volatile int *pg78 = (volatile int*)0x2000230cUL;
  volatile int *pg7c = (volatile int*)0x20007554UL;
  int iVar3, iVar5; unsigned long long uVar6;
  (void)param_2;(void)param_3;
  if ((param_1 != 0) || (*pg70 == 0) ||
      (FUN_0007c132() != 0 && (iVar3=FUN_000167a8(), VB(VI(iVar3+0x1014)+2) == 0))) {
    if (VB(FUN_000167a8()) != 1) return;
    FUN_0007d39e();
    return;
  }
  if (*pg70 == 0) return;
  iVar3 = FUN_000167a8();
  if (VI(VI(iVar3+0x1054)) != 0) return;
  iVar3 = FUN_000167a8();
  if (VB(iVar3+0xd5) != 0) return;
  if (VB(FUN_000167a8()) != 1) return;
  if (FUN_0007c132() != 0) { iVar3=FUN_000167a8(); if (VB(VI(iVar3+0x1014)+1)==0) return; }
  if (FUN_0007c132() == 0) { iVar3=FUN_000167a8(); VB(VI(iVar3+0x1014)+2)=0; }
  iVar3=FUN_000167a8(); VB(VI(iVar3+0x1014)+3)=0;
  iVar3=FUN_000167a8(); *pg74 = VB(VI(iVar3+0x1014)+3);
  iVar3=FUN_000167a8(); (void)VB(VI(iVar3+0x1014)+2); (void)(*pg74);
  if (FUN_00042c8c((void*)0,3) != 0) return;
  if (0 < *pg78) {
    if (*pg7c == 0) DEBUG_PRINT(0x0009fcc1,0x000a1aea);
    else FUN_00019c70();
  }
  FUN_00040708();
  iVar3=FUN_000167a8(); VB(VI(iVar3+0x1014))=1;
  update_persist_task_status(FUN_000167a8(),0xe,2);
  iVar3=FUN_000167a8(); iVar5=FUN_000167a8(); VB(VI(iVar5+0x1014)+0x20)=VB(iVar3+0xed5);
  iVar3=FUN_000167a8(); VB(iVar3+0xed5)=0x2a;
  uVar6=FUN_0007cb2c();
  iVar3=FUN_000167a8(); { int b=VI(iVar3+0x1014); VI(b+8)=(int)(uVar6>>32); VI(b+4)=(int)uVar6; }
  iVar3=FUN_000167a8(); iVar5=VI(iVar3+0x1014);
  iVar3=FUN_000167a8(); VB(iVar3+0xcd)=VB(iVar5+3);
}

