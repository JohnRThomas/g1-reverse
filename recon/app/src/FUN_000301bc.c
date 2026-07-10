/* Reconstructed FUN_000301bc @ 0x301bc  (parity: 300/300 trials, PROVEN) */

extern int FUN_0003016c(int);
extern int FUN_00030178(unsigned,unsigned,...);
int FUN_000301bc(unsigned p1,unsigned p2,unsigned p3,unsigned p4){
  int iVar1;
  iVar1 = FUN_00030178(0xff20, 0x3c00f091, p3, p4, p4);
  if(iVar1 >= 0 && (iVar1=FUN_00030178(0x4700,0x110), iVar1>=0)){
    FUN_0003016c(1);
    iVar1 = FUN_00030178(0x4444,0);
    if(iVar1 != 0) return iVar1;
    FUN_0003016c(0x14);
    iVar1 = FUN_00030178(0xff18,0x3c);
    if(iVar1 >= 0){
      FUN_0003016c(0x19);
      iVar1 = FUN_00030178(0x4700,0x102);
      return iVar1 >> 0x1f;
    }
  }
  return -1;
}

