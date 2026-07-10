/* Reconstructed FUN_00074d74 @ 0x74d74  (parity: 300/300 trials, PROVEN) */

extern int FUN_00072040(int);
extern int FUN_0007205c(int);
extern void FUN_00072078(int);
extern void FUN_00074bbc(int);
extern void FUN_0007e2ec(int,int);
extern int FUN_0007e2fa(int,...);
int FUN_00074d74(int *param_1,int param_2,int param_3,int param_4){
  int uVar4;
  int r=FUN_00072040(0x2000b498);
  if(r==0){ FUN_0007e2fa(0x99cbd,0xf0920,0xf08c7,0x72,param_4); FUN_0007e2fa(0xf0935,0x2000b498); FUN_0007e2ec(0xf08c7,0x72); }
  FUN_00072078(0x2000b498);
  if(*param_1==0) uVar4=0xffffffea; else { FUN_00074bbc((int)param_1); uVar4=0; }
  r=FUN_0007205c(0x2000b498);
  if(r!=0) return uVar4;
  FUN_0007e2fa(0x99cbd,0xf08f4,0xf08c7,0xf0,param_4); FUN_0007e2fa(0xf090b,0x2000b498); FUN_0007e2ec(0xf08c7,0xf0);
  return 0;
}

