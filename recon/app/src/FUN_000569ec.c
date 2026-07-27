/* Reconstructed FUN_000569ec @ 0x569ec  (parity: 300/300 trials, PROVEN) */

extern int FUN_0005f4d4(int,int);
extern void FUN_0007e2ec(unsigned,unsigned);
extern void FUN_0007e2fa(unsigned long, ...);
extern int FUN_000813ca(unsigned,unsigned,void*);
extern int FUN_000836de(int,unsigned,unsigned,unsigned);
extern int FUN_00086406(void);
int FUN_000569ec(int param_1,int param_2,unsigned param_3,unsigned param_4){
  int iVar1; unsigned local_20, local_1c;
  iVar1 = FUN_00086406();
  if(iVar1!=0){
    FUN_0007e2fa(0x99cbd,0xf3d75,0xf3a5d,0x55f);
    FUN_0007e2ec(0xf3a5d,0x55f);
  }
  if(param_1==0) param_1=0x20003a7c;
  iVar1=FUN_000836de(param_1,0x20003a7c,param_3,param_4);
  if(iVar1==0){
    local_1c=0xf3d84; local_20=2;
    FUN_000813ca(0x88108,0x1080,&local_20);
  } else {
    FUN_0005f4d4(iVar1+0xc, param_2+5);
  }
  return iVar1;
}

