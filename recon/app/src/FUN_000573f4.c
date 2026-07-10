/* Reconstructed FUN_000573f4 @ 0x573f4  (parity: 300/300 trials, PROVEN) */

extern int FUN_000569ec(int,int,unsigned,int);
extern void* FUN_0005f5d0(int,int);
extern int FUN_000573c8(int);
int FUN_000573f4(int param_1, unsigned char param_2, unsigned short param_3, unsigned param_4){
  unsigned uVar1 = 0x20003ab0;
  if(param_1!=6) uVar1=0;
  int iVar2 = FUN_000569ec(uVar1,4,0x10000,0);
  if(iVar2==0){ return FUN_000573c8(param_1); }
  unsigned char* puVar3 = (unsigned char*)FUN_0005f5d0(iVar2+0xc,4);
  *puVar3=(unsigned char)param_1;
  puVar3[1]=param_2;
  *(unsigned short*)(puVar3+2)=param_3;
  return iVar2;
}

