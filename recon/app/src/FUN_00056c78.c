/* Reconstructed FUN_00056c78 @ 0x56c78  (parity: 300/300 trials, PROVEN) */

extern int FUN_00080f14(int);
extern void FUN_0007e2ec(int,int);
extern int FUN_0007e2fa(int,...);
int FUN_00056c78(int param_1,int param_2){
  int iVar2=FUN_00080f14(param_2);
  if(iVar2==0) return 0;
  unsigned uVar1,uVar5; int iVar3,iVar4;
  for(iVar4=*(int*)0x2000ad1c; uVar1=0x88058, uVar5=0x87fec, iVar4!=0; iVar4=*(int*)(iVar4+0x20)){
    if(*(void**)(iVar4+8)!=0){
      iVar3=(*(int(**)(int,int))(iVar4+8))(param_1,param_2);
      if(iVar3==0) return 0;
      iVar3=FUN_00080f14(param_2);
      if(iVar3==0) return 0;
    }
  }
  while(1){
    if(uVar1<uVar5){ FUN_0007e2fa(0x99cbd,0xf3a8d,0xf3a5d,0x676); FUN_0007e2fa(0xf0d20); FUN_0007e2ec(0xf3a5d,0x676); }
    if(uVar1<=uVar5) break;
    if(*(void**)(uVar5+8)!=0){
      iVar4=(*(int(**)(int,int))(uVar5+8))(param_1,param_2);
      if(iVar4==0) return 0;
      iVar4=FUN_00080f14(param_2);
      if(iVar4==0) return 0;
    }
    uVar5=uVar5+0x24;
  }
  return iVar2;
}

