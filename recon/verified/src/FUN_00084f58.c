/* Reconstructed FUN_00084f58 @ 0x84f58  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c04(int,int,int);
int FUN_00084f58(int *param_1,int param_2){
  int iVar1,iVar4,iVar5; unsigned uVar2,uVar3;
  if(param_1==0) return 0;
  iVar1=*param_1;
  if(iVar1==0) return 0;
  uVar2=param_1[1];
  if(uVar2!=0 && uVar2<=(unsigned)param_1[2]) return 0;
  if(param_2<0) return 0;
  iVar4=param_1[2];
  uVar3=param_2+iVar4+1;
  if(uVar2<uVar3){
    if(param_1[4]!=0) return 0;
    if(uVar3<0x40000000){ iVar5=param_2+iVar4+2; }
    else { if((int)uVar3<0) return 0; iVar5=0x7fffffff; }
    if(((void*)param_1[8])==0){
      iVar4=((int(*)(int))param_1[6])(iVar5);
      if(iVar4==0) goto LAB;
      FUN_00086c04(iVar4,*param_1,param_1[2]+1);
      ((void(*)(int))param_1[7])(*param_1);
    } else {
      iVar4=((int(*)(int,int))param_1[8])(iVar1,iVar5);
      if(iVar4==0){
      LAB:
        ((void(*)(int))param_1[7])(*param_1);
        *param_1=iVar4; param_1[1]=iVar4; return 0;
      }
    }
    *param_1=iVar4; param_1[1]=iVar5; iVar1=param_1[2];
  }
  return iVar1+iVar4;
}

