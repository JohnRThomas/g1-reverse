/* Reconstructed FUN_000744a4 @ 0x744a4  (parity: 300/300 trials, PROVEN) */

extern int FUN_00072040(int);
extern int FUN_0007205c(int);
extern void FUN_00072078(int);
extern void FUN_00074274(int);
extern void FUN_00074d74(int);
extern void FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(unsigned long, ...);
int FUN_000744a4(int *param_1){
  int r=FUN_00072040(0x2000b490);
  if(r==0){ FUN_0007e2fa(0x99cbd,0xf0920,0xf08c7,0x72); FUN_0007e2fa(0xf0935,0x2000b490); FUN_0007e2ec(0xf08c7,0x72); }
  FUN_00072078(0x2000b490);
  int *piVar4=(int*)*param_1;
  if(param_1==piVar4) piVar4=0;
  else if(piVar4!=0){ FUN_00074274((int)piVar4); FUN_00074d74((int)piVar4+0x18); }
  r=FUN_0007205c(0x2000b490);
  if(r!=0) return (int)piVar4;
  FUN_0007e2fa(0x99cbd,0xf08f4,0xf08c7,0xf0); FUN_0007e2fa(0xf090b,0x2000b490); FUN_0007e2ec(0xf08c7,0xf0);
  return 0;
}

