/* Reconstructed FUN_0006058c @ 0x6058c  (parity: 300/300 trials, PROVEN) */

extern void FUN_0005010c(int,int,int,unsigned,unsigned);
extern int FUN_00065190(unsigned);
extern void FUN_000651d8(void);
extern int FUN_0007e212(int,unsigned);
int FUN_0006058c(int param_1,unsigned param_2,unsigned param_3,unsigned param_4){
  unsigned uVar1; int iVar2,iVar3,iVar4;
  FUN_0005010c(5,1,0,param_4,param_4);
  iVar2=FUN_00065190(0x60635);
  if(iVar2==0x0bad0000){
    *(volatile unsigned*)0x5000555cUL=0x9ba5;
    FUN_000651d8();
    uVar1=0x8b5fc; iVar2=0;
    do{
      iVar4=*(int*)(param_1+0x10);
      iVar3=FUN_0007e212(iVar4+iVar2*0x20,uVar1);
      if(iVar3<0) return iVar3;
      iVar3=iVar2*0xc; iVar2=iVar2+1;
      *(unsigned*)(iVar3+iVar4+0x88)=1;
    } while(iVar2!=4);
    iVar2=0;
  } else { iVar2=-5; }
  return iVar2;
}

