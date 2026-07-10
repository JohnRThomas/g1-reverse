/* Reconstructed FUN_00083e0e @ 0x83e0e  (parity: 300/300 trials, PROVEN) */

extern int FUN_000723b8(unsigned,unsigned,int,int,int,unsigned);
extern int FUN_00072558(unsigned);
extern int FUN_00083dba(int,unsigned,unsigned,void*);
extern int FUN_00083dc8(int,unsigned,unsigned);
int FUN_00083e0e(int param_1, unsigned param_2, unsigned param_3){
  int iVar1; unsigned uVar2; unsigned char local;
  uVar2=*(unsigned*)(param_1+0x10);
  FUN_000723b8(uVar2,param_2,-1,-1,param_1,param_2);
  iVar1=FUN_00083dba(param_1,param_2,param_3,&local);
  if(iVar1==0){ iVar1=FUN_00083dc8(param_1,param_2,param_3); }
  FUN_00072558(uVar2);
  return iVar1;
}

