/* Reconstructed FUN_00073a78 @ 0x73a78  (parity: 300/300 trials, PROVEN) */

extern int FUN_00072040(int);
extern int FUN_0007205c(int);
extern void FUN_00072078(int);
extern void FUN_00073840(int);
extern void FUN_000739f0(int,int);
extern void FUN_0007e2ec(int,int);
extern int FUN_0007e2fa(int,...);
void FUN_00073a78(int param_1,int param_2,int param_3,int param_4){
  int r=FUN_00072040(0x2000b490);
  if(r==0){ FUN_0007e2fa(0x99cbd,0xf0920,0xf08c7,0x72,param_4); FUN_0007e2fa(0xf0935,0x2000b490); FUN_0007e2ec(0xf08c7,0x72); }
  FUN_00072078(0x2000b490);
  unsigned char b=*(volatile unsigned char*)(param_1+0xd);
  if((int)((unsigned)b<<0x1d) < 0){
    *(volatile unsigned char*)(param_1+0xd) = b & 0xfb;
    FUN_00073840(param_1);
    FUN_000739f0(0x2000b490, 0);
    return;
  }
  r=FUN_0007205c(0x2000b490);
  if(r!=0) return;
  FUN_0007e2fa(0x99cbd,0xf08f4,0xf08c7,0xf0,param_4); FUN_0007e2fa(0xf090b,0x2000b490); FUN_0007e2ec(0xf08c7,0xf0);
}

