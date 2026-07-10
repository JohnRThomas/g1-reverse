/* Reconstructed FUN_00054d18 @ 0x54d18  (parity: 300/300 trials, PROVEN) */

extern int FUN_000530b4(void);
extern int FUN_00054ce8(void*);
extern int FUN_00080d3a(void);
extern int FUN_00080dda(void*);
extern int FUN_00080fa4(int,unsigned);
extern int FUN_00080fb4(unsigned);
extern int FUN_00080fc4(int,int);
int FUN_00054d18(int param_1,int param_2,unsigned param_3){
  int iVar1,iVar2;
  int iStack_18,iStack_14; unsigned uStack_10;
  iStack_18=param_1; iStack_14=param_2; uStack_10=param_3;
  if(param_2==0 || (iVar1=FUN_00080fa4(param_2,0xf2b3a), iVar1!=0)){
    do{
      iVar1=FUN_00080dda(&iStack_18);
      if(iVar1!=0) return iVar1;
      iVar1=FUN_00054ce8(&iStack_18);
    } while(iVar1 >= 0);
    iVar2=FUN_00080fc4(param_1*7+0x20002000, (int)&iStack_18);
    iVar1=param_2;
    if(param_2==0) goto LAB;
  } else {
    iVar1=0x20002000 + param_1*7;
    iVar2=param_2;
  }
  FUN_00080fc4(iVar1,iVar2);
  LAB:
  iVar1=FUN_00080fb4(0x200020d4);
  if((iVar1<<0x1d) < 0){ FUN_000530b4(); FUN_00080d3a(); }
  return 0;
}

