/* Reconstructed FUN_000730e8 @ 0x730e8  (parity: 300/300 trials, PROVEN) */
extern void FUN_0007e2fa(int,...);
extern void FUN_0007e2ec(int,...);
extern void FUN_00071eac(int,int,unsigned,int,int,int,int,unsigned,int);
extern void FUN_00086412(int);
extern void FUN_0008641c(int);
void FUN_000730e8(int param_1,int param_2,unsigned param_3,unsigned param_4,int *param_5){
  unsigned uVar1;
  if(param_1==0){
    FUN_0007e2fa(0x00099cbd,0x000f586b,0x000f820f,0x2c8); uVar1=0x2c8;
    FUN_0007e2ec(0x000f820f,uVar1); return;
  } else if(param_2==0){
    FUN_0007e2fa(0x00099cbd,0x000f82a5,0x000f820f,0x2c9); uVar1=0x2c9;
    FUN_0007e2ec(0x000f820f,uVar1); return;
  } else {
    if((*(volatile unsigned*)(param_1+0xf0)&1)!=0){
      FUN_0007e2fa(0x00099cbd,0x000f82ab,0x000f820f,0x2ca);
      FUN_0007e2ec(0x000f820f,0x2ca);
    }
    *(volatile unsigned*)(param_1+0xd8)=0;
    *(volatile unsigned*)(param_1+0xdc)=0;
    *(volatile int*)(param_1+0xe0)=param_1+0xe0;
    *(volatile int*)(param_1+0xe4)=param_1+0xe0;
    *(volatile int*)(param_1+0xe8)=param_1+0xe8;
    *(volatile int*)(param_1+0xec)=param_1+0xe8;
    if(param_5==0) uVar1=1;
    else { uVar1=0x101; if((char)param_5[1]==0) uVar1=1; }
    *(volatile unsigned*)(param_1+0xf0)=uVar1;
    FUN_00071eac(param_1,param_2,param_3,0x00072ab1,param_1,0,0,param_4,0);
    if(param_5!=0 && *param_5!=0) FUN_00086412(param_1);
    FUN_0008641c(param_1); return;
  }
}
