/* Reconstructed FUN_0003f380 @ 0x3f380  (parity: 300/300 trials, PROVEN) */

extern int FUN_00023ee0(void);
extern int FUN_0007d3ee(void);
extern int FUN_0007d446(void);
extern void FUN_00043e90(int,...);
void FUN_0003f380(void){
  int iVar1=FUN_00023ee0();
  int iVar2,iVar3,iVar4,uVar5;
  if(iVar1==6){
    iVar1=FUN_0007d3ee(); iVar2=FUN_0007d446(); iVar3=FUN_0007d3ee(); iVar4=FUN_0007d446();
    iVar1+=0xa4; uVar5=0xaa091;
  } else {
    iVar1=FUN_0007d3ee(); iVar2=FUN_0007d446(); iVar3=FUN_0007d3ee(); iVar4=FUN_0007d446();
    iVar1+=0x92; uVar5=0xaa070;
  }
  FUN_00043e90(0,uVar5,0,iVar1,iVar2+0x37,iVar3+0x23f,iVar4+0x6d,2,0,0,0,0);
}

