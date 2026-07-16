/* Reconstructed FUN_0005a6b0 @ 0x5a6b0  (parity: 300/300 trials, PROVEN) */

extern int FUN_000531d8(unsigned,unsigned,int,int);
extern int FUN_000566a4(int);
extern int FUN_00056e74(int,void*);
extern int FUN_00082572(void);
extern int FUN_000826b2(void*,unsigned);
extern int FUN_000826f6(unsigned,unsigned,...);
extern int FUN_00082bb8(void*,int);
void FUN_0005a6b0(unsigned p1,unsigned p2,unsigned p3,unsigned p4){
  unsigned uVar1; int iVar2; unsigned char* puVar3; int iVar4;
  FUN_000826f6(0x20006448, 0xfffffff7, p3, p4, p4);
  FUN_000531d8(0x200063a0, 0, 0x148, 0);
  uVar1 = 0xf2b3a;
  iVar4=0;
  puVar3=(unsigned char*)0x2000aed4;
  do{
    iVar2=FUN_000826b2(puVar3+1, uVar1);
    if(iVar2==0 && (int)((unsigned)(unsigned char)puVar3[8]<<0x1f) < 0){
      iVar2=FUN_00056e74(0, puVar3+1);
      if(iVar2!=0){ FUN_00082572(); FUN_000566a4(iVar2); }
      FUN_000826f6((unsigned)(puVar3+0xc), 0xfffffffd);
      FUN_00082bb8(puVar3, 0);
    }
    iVar4=iVar4+1;
    puVar3=puVar3+0x10;
  } while(iVar4!=3);
  return;
}
