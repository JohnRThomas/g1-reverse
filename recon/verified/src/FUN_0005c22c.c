/* Reconstructed FUN_0005c22c @ 0x5c22c  (parity: 300/300 trials, PROVEN) */
extern void FUN_0007e2ec(int,...);
extern void FUN_0007e2fa(unsigned long, ...);
extern int FUN_000823fa(int);
extern int FUN_00082aee(int,int,int*,int,int,unsigned);
int FUN_0005c22c(int param_1, int *param_2){
  short sVar1; int iVar2; int uVar3; unsigned short uVar4; unsigned uVar5; int uVar6; int uVar7;
  if (param_1==0){
    FUN_0007e2fa(0x00099cbd,0x000f3ebd,0x000f46b8,0x13de,0,(int)param_2);
    FUN_0007e2fa(0x000f4a0a); uVar3=0x13de; FUN_0007e2ec(0x000f46b8,uVar3);
    param_2=(int*)0x13de; goto recheck;
  }
 recheck:
  if (param_2==0 || *param_2==0){
    FUN_0007e2fa(0x00099cbd,0x000f4c07,0x000f46b8,0x13df,param_1,(int)param_2);
    FUN_0007e2fa(0x000f4a0a); uVar3=0x13df; FUN_0007e2ec(0x000f46b8,uVar3);
    param_2=(int*)0x13df; goto recheck;
  }
  if ((short)param_2[1]==0){
    FUN_0007e2fa(0x00099cbd,0x000f4cce,0x000f46b8,0x13e0,param_1,(int)param_2);
    FUN_0007e2fa(0x000f4a0a); uVar3=0x13e0; FUN_0007e2ec(0x000f46b8,uVar3);
    param_2=(int*)0x13e0; goto recheck;
  }
  if (*(char*)(param_1+0xd)!=7) return 0xffffff80;
  uVar4 = *(unsigned short*)((char*)param_2+0xc);
  if (*(short*)((char*)param_2+6)==0){
    iVar2 = FUN_000823fa(param_1);
    uVar5 = (unsigned short)(uVar4+2);
    if (uVar5 <= (unsigned)(iVar2-1U)){
      uVar7=0x12; uVar3=0x00082603; uVar6=0x0008281b; goto LAB;
    }
  }
  sVar1 = FUN_000823fa(param_1);
  uVar4 = *(unsigned short*)((char*)param_2+0xc);
  if ((unsigned short)(sVar1-5U) <= *(unsigned short*)((char*)param_2+0xc)) uVar4 = sVar1-5U;
  uVar5 = (unsigned)(unsigned short)(uVar4+4);
  uVar7=0x16; uVar3=0x00082e05; uVar6=0x00082857;
 LAB:
  uVar3 = FUN_00082aee(param_1,uVar3,param_2,uVar6,uVar7,uVar5);
  return uVar3;
}
