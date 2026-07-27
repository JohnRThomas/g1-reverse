/* Reconstructed FUN_000719f4 @ 0x719f4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0008669c(void*);
extern int FUN_00072040(int);
extern void FUN_00072078(int);
extern int FUN_0007205c(int);
extern long long FUN_0004b2b0(int,unsigned,unsigned);
extern void FUN_000866e4(void*,int,int,int);
extern void FUN_00073f6c(int,unsigned,int,int,int,int);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(unsigned,unsigned);

static inline unsigned gp(void){unsigned r;__asm volatile("mrs %0, basepri":"=r"(r));return r;}
static inline void spm(unsigned v){__asm volatile("msr basepri_max, %0"::"r"(v):"memory");}
static inline void sp(unsigned v){__asm volatile("msr basepri, %0"::"r"(v):"memory");}
static inline void ib(void){__asm volatile("isb sy":::"memory");}
static inline unsigned gi(void){unsigned r;__asm volatile("mrs %0, ipsr":"=r"(r));return r;}

int FUN_000719f4(int param_1, unsigned param_2, unsigned param_3, unsigned param_4, int param_5, int param_6){
  int local_30, iStack_2c;
  FUN_0008669c(&local_30);
  int iVar4 = local_30;
  int iVar2 = iStack_2c;
  int iVar7 = param_1 + 0x14;
  unsigned uVar8, uVar5;
  long long uVar9 = 0;
  uVar8 = gp(); spm(0x20); ib();
  int iVar3 = FUN_00072040(iVar7);
  if(iVar3 == 0){
    FUN_0007e2fa(0x00099cbd,0x000f0920,0x000f08c7,0x72);
    FUN_0007e2fa(0x000f0935,iVar7);
    uVar5 = 0x72; uVar8 = 0x000f08c7;
    goto EC;
  }
  FUN_00072078(iVar7);
  unsigned uVar6 = gi();
  if(uVar6 == 0 || (param_5 == 0 && param_6 == 0)){
    while(1){
      uVar9 = FUN_0004b2b0(param_1, param_2, param_3);
      if((int)uVar9 != 0 || (param_5 == 0 && param_6 == 0)) break;
      FUN_000866e4(&local_30, (int)((unsigned long long)uVar9 >> 0x20), iVar4, iVar2);
      param_6 = iStack_2c;
      param_5 = local_30;
      FUN_00073f6c(iVar7, uVar8, param_1 + 0xc, iStack_2c, local_30, iStack_2c);
      uVar8 = gp(); spm(0x20); ib();
      iVar3 = FUN_00072040(iVar7);
      if(iVar3 == 0){
        FUN_0007e2fa(0x00099cbd,0x000f0920,0x000f08c7,0x72);
        FUN_0007e2fa(0x000f0935,iVar7);
        uVar5 = 0x72; uVar8 = 0x000f08c7;
        goto EC;
      }
      FUN_00072078(iVar7);
    }
    int iVar4b = FUN_0007205c(iVar7);
    if(iVar4b != 0){
      sp(uVar8); ib();
      return (int)uVar9;
    }
    FUN_0007e2fa(0x00099cbd,0x000f08f4,0x000f08c7,0xf0);
    FUN_0007e2fa(0x000f090b,iVar7);
    uVar5 = 0xf0; uVar8 = 0x000f08c7;
  } else {
    FUN_0007e2fa(0x00099cbd,0x000f7df6,0x000f7dbe,0x4a);
    FUN_0007e2fa(0x000f53ff);
    uVar5 = 0x4a; uVar8 = 0x000f7dbe;
  }
EC:
  FUN_0007e2ec(uVar8, uVar5);
  return 0;
}

