/* Reconstructed FUN_00053cd4 @ 0x53cd4  (parity: 300/300 trials, PROVEN) */

extern int FUN_000836de(int,int,int,int);
extern void FUN_0005f4d4(int,int);
extern int FUN_0005ee18(int);
extern int FUN_0005f5d0(int,int);
extern void FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(unsigned long, ...);
int FUN_00053cd4(short param_1,int param_2){
  int iVar2=FUN_000836de(0x20003b4c,param_2,-1,-1);
  if(iVar2==0){ FUN_0007e2fa(0x99cbd,0xf45be,0xf2e84,0x10a); FUN_0007e2ec(0xf2e84,0x10a); }
  FUN_0005f4d4(iVar2+0xc,1);
  *(volatile char*)(iVar2+0x18)=0;
  int iVar3=FUN_0005ee18(iVar2);
  *(volatile short*)(iVar3*0xc + 0x2000abf4 + 2)=param_1;
  iVar3=FUN_0005ee18(iVar2);
  *(volatile int*)(iVar3*0xc + 0x2000abf4 + 8)=0;
  iVar3=FUN_0005ee18(iVar2);
  *(volatile int*)(iVar3*0xc + 0x2000abf4 + 4)=0;
  int puVar4=FUN_0005f5d0(iVar2+0xc,3);
  *(volatile short*)puVar4=param_1;
  *(volatile char*)(puVar4+2)=(char)param_2;
  return iVar2;
}

