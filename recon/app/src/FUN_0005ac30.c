/* Reconstructed FUN_0005ac30 @ 0x5ac30  (parity: 300/300 trials, PROVEN) */

extern int FUN_00059c04(unsigned);
extern int FUN_0005a250(void);
extern int FUN_0005a91c(void);
extern int FUN_0005aba8(void);
extern int FUN_000735cc(int);
extern int FUN_000826e0(int,int);
extern int FUN_0008270c(int);
extern int FUN_00082932(unsigned,unsigned,unsigned,unsigned);
void FUN_0005ac30(unsigned p1,unsigned p2,unsigned p3,unsigned p4,unsigned short p5){
  int iVar1,iVar2;
  FUN_000735cc(0x200063d0 - 0x30);
  iVar1 = FUN_0008270c(0x20006448);
  if((iVar1<<0x1c) >= 0){ FUN_0005aba8(); FUN_0005a91c(); FUN_0005a250(); }
  iVar1 = FUN_00059c04(p1);
  if(iVar1!=0){
    if((int)((unsigned)*(unsigned char*)(iVar1+8)<<0x1f) < 0){
      iVar2 = FUN_0008270c(iVar1+0xc);
      if((iVar2<<0x1f) >= 0){ FUN_000826e0(iVar1+0xc, 2); }
    }
  }
  FUN_00082932(p3,p4,p5,0x20006380);
  return;
}

