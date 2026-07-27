/* Reconstructed FUN_00063c3c @ 0x63c3c  (parity: 300/300 trials, PROVEN) */

extern int FUN_0004d944(unsigned,int,void*,int);
extern int FUN_0004f770(int);
extern int FUN_00063ba8(int);
extern int FUN_00063bcc(void);
extern int FUN_00063c14(int);
extern void FUN_0007e2ec(unsigned,unsigned);
extern void FUN_0007e2fa(unsigned long, ...);
void FUN_00063c3c(void){
  int iVar1; unsigned local_18, local_14;
  unsigned char r5 = *(volatile unsigned char*)0x2001d563UL;
  if(r5 != 0){
    FUN_0007e2fa(0x99cbd,0xf6749,0xf6716,0xab);
    FUN_0007e2ec(0xf6716,0xab);
  }
  L:
  iVar1 = FUN_00063ba8(r5);
  if(iVar1==0){
    FUN_0007e2fa(0x99cbd,0xf6769,0xf6716,0xac);
    FUN_0007e2ec(0xf6716,0xac);
    goto L;
  }
  local_14=0xf67a5; local_18=2;
  FUN_0004d944(0x88268,0x10c0,&local_18,0);
  iVar1=FUN_00063bcc();
  *(unsigned char*)(iVar1+8)=r5;
  FUN_00063c14(1);
  FUN_0004f770(iVar1);
  return;
}

