/* named: att_send_with_retry */
/* Reconstructed att_send_with_retry @ 0x818dc  (parity: 300/300 trials, PROVEN) */

extern int net_buf_unref(void);
extern int FUN_00073418(int,int,int,int);
extern unsigned long long FUN_00081852(int,void*,unsigned);
extern int thunk_FUN_000727ac(int,int,int,int,int);
void att_send_with_retry(int param_1,int param_2,unsigned param_3){
  int iVar1; unsigned long long uVar2; int iVar3;
  int local_1c; unsigned uStack_18;
  iVar3=param_1; local_1c=param_2; uStack_18=param_3;
  do {
    iVar1 = *(int*)(param_1-4);
    if(iVar1==0){
      iVar1 = thunk_FUN_000727ac(param_1-0x20, param_2, 0, 0, iVar3);
      if(iVar1==0) return;
    } else {
      *(int*)(param_1-4)=0;
    }
    local_1c=iVar1;
    uVar2 = FUN_00081852(param_1-0x50, &local_1c, **(unsigned short**)(iVar1+0x18));
    param_2 = (int)(uVar2 >> 0x20);
  } while((int)uVar2 >= 0);
  if((int)uVar2 == -0xb){
    *(int*)(param_1-4)=local_1c;
    FUN_00073418(param_1,param_2,0x8000,0);
    return;
  }
  net_buf_unref();
  return;
}

