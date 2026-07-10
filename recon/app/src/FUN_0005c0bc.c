/* Reconstructed FUN_0005c0bc @ 0x5c0bc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int  FUN_00080d3e(void*, ...);
extern void FUN_00082a42(int,int,void*);
extern int  FUN_00082d2e(int,int,int*);
extern void FUN_00086c78(void*,int,int);

void FUN_0005c0bc(unsigned int param_1,int param_2,unsigned char *param_3,
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
    if (uVar2 != 2) { FUN_00082a42(0x00088128,0x1840,(void*)0); goto LAB_0f2; }
    uVar2 = 0x12; local_50 = 2;
  }
  uVar5 = (unsigned int)(param_4 - 1) & 0xffff;
  if (uVar2 > uVar5) goto LAB_0f2;
  bVar1 = 0;
  uVar5 = uVar5 / uVar2;
  off = 1;
  local_60 = 0;
  for (;;) {
    if (uVar5 == 0) { FUN_00082d2e(local_5c, local_60, param_5); return; }
    local_64 = *(volatile unsigned short*)(param_3 + off);
    local_60 = local_64;
    if (bVar1) { goto LAB_1ec; }
    /* local_50==0 / ==2 copies are stack-only, omitted */
    if ((pp5[0] != 0) && (iVar3 = FUN_00080d3e((void*)&local_50), iVar3 != 0)) goto LAB_1ec;
    if ((char)pp5[4] == 4) {
      iVar3 = FUN_00080d3e((void*)&local_50);
      if (iVar3 != 0) {
        iVar3 = FUN_00080d3e((void*)&local_50);
        if (iVar3 != 0) {
          iVar3 = FUN_00080d3e((void*)&local_50);
          if (iVar3 != 0) {
            iVar3 = FUN_00080d3e((void*)&local_50);
            if (iVar3 != 0) goto LAB_1f8;
            bVar1 = 1; goto LAB_1f0;
          }
        }
      }
      goto LAB_1ec;
    }
LAB_1f8:
    FUN_00086c78((void*)0,0,0x10);
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

