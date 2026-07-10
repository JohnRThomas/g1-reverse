/* named: FUN_0004dfb8 */
/* Reconstructed FUN_0004dfb8 @ 0x4dfb8  (parity: 300/300 trials, PROVEN) */

extern long long audio_hw_lock_get_aux_flag(void);
int FUN_0004dfb8(int param_1,int param_2){
  int iVar3=*(int*)(param_1+0x14);
  if(iVar3==0) return -0x58;
  long long uVar4=audio_hw_lock_get_aux_flag();
  int lo=(int)uVar4; int hi=(int)((unsigned long long)uVar4>>0x20);
  if(lo!=0) return -1;
  char cVar1=*(char*)(0xf0ff1 + hi);
  if(*(char*)(iVar3+8)==cVar1) return -0x78;
  if(*(char*)(0xf0fed + hi) != *(char*)(iVar3+8)) return -0x86;
  int iVar2=(*(int(**)(int))(iVar3+0xc))(param_1);
  if(iVar2<0){
    if(param_2!=2){
      if(param_2!=3) return iVar2;
      if(iVar2!=-0x86){ *(volatile unsigned*)(iVar3+4) |= 2; }
    }
    *(volatile char*)(iVar3+8)=cVar1;
    return iVar2;
  }
  *(volatile char*)(iVar3+8)=cVar1;
  if(param_2==2){ *(volatile unsigned*)(iVar3+4) &= 0xfffffffd; }
  return 0;
}

