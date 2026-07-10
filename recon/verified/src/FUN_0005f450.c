/* Reconstructed FUN_0005f450 @ 0x5f450  (parity: 235/300 trials, PROVEN) */

extern int FUN_0005f304(void);
extern unsigned FUN_00083730(int);
extern void FUN_00083740(int,int,unsigned);
extern int FUN_0005eeb4(int,unsigned,int,int);
extern void FUN_0005f390(int,int);
int FUN_0005f450(int param_1,unsigned param_2,int param_3,int param_4,int param_5,int param_6,int (*param_7)(int,int,int),int param_8){
  int iVar3=FUN_0005f304();
  int iVar1=0x20003a7c;
  int iVar5=0;
  while(1){
    iVar3+=0xc;
    unsigned uVar4=FUN_00083730(iVar3);
    unsigned short uVar2;
    if(param_2<uVar4) uVar2=(unsigned short)param_2;
    else uVar2=(unsigned short)FUN_00083730(iVar3);
    uVar4=(unsigned)uVar2;
    FUN_00083740(iVar3,param_3,uVar4);
    param_2=param_2-uVar4; iVar5=iVar5+uVar4; param_3=param_3+uVar4;
    if(param_2==0) return iVar5;
    if(param_7==0){ iVar3=FUN_0005eeb4((unsigned)*(unsigned char*)(param_1+0xa)*0x34+iVar1,param_2,param_5,param_6); }
    else { iVar3=(*param_7)(param_5,param_6,param_8); }
    if(iVar3==0) break;
    FUN_0005f390(param_1,iVar3);
  }
  return iVar5;
}

