/* Reconstructed FUN_0007f088 @ 0x7f088  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c04(int,int,unsigned);
extern int FUN_0004e1ac(int*);
int FUN_0007f088(int *param_1,int param_2,unsigned param_3,int param_4){
  int iVar1;
  if(param_1==0) return -0xe;
  if((unsigned)param_1[6] < (unsigned)(param_1[4]+param_1[2]+(int)param_3)) return -0xc;
  unsigned uVar2=0, uVar3, uVar4;
  while(1){
    iVar1=*(volatile int*)((int)param_1+8);
    uVar4=param_3-uVar2;
    uVar3=param_1[1]-iVar1;
    if(uVar4<uVar3) break;
    FUN_00086c04(iVar1+*param_1, param_2+uVar2, uVar3);
    *(volatile int*)((int)param_1+8)=param_1[1];
    iVar1=FUN_0004e1ac(param_1);
    if(iVar1!=0) return iVar1;
    uVar2=uVar2+uVar3;
  }
  if(uVar2<param_3){
    FUN_00086c04(iVar1+*param_1, param_2+uVar2, uVar4);
    *(volatile int*)((int)param_1+8)=*(volatile int*)((int)param_1+8)+uVar4;
  }
  if(param_4==0){ iVar1=0; }
  else{
    iVar1=*(volatile int*)((int)param_1+8);
    if(iVar1!=0){ iVar1=FUN_0004e1ac(param_1); return iVar1; }
  }
  return iVar1;
}

