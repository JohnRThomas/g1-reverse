/* Reconstructed FUN_00074f68 @ 0x74f68  (parity: 80/80 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00072040(unsigned int);
extern void FUN_00072078(unsigned int);
extern unsigned int FUN_00074b68(void);
extern int FUN_0007205c(unsigned int);
extern void FUN_0007e2fa(unsigned int,...);
extern void FUN_0007e2ec(unsigned int,...);
unsigned long long FUN_00074f68(void){
  unsigned int uVar6=0;
  int iVar2=FUN_00072040(0x2000b498);
  if(iVar2==0){
    FUN_0007e2fa(0x00099cbd,0x000f0920,0x000f08c7,0x72);
    FUN_0007e2fa(0x000f0935,0x2000b498);
    FUN_0007e2ec(0x000f08c7,0x72);
  }
  FUN_00072078(0x2000b498);
  unsigned int uVar3=FUN_00074b68();
  unsigned int uVar4=*(volatile unsigned int*)0x200069e0UL;
  unsigned int uVar5=*(volatile unsigned int*)0x200069e4UL;
  int iVar2b=FUN_0007205c(0x2000b498);
  if(iVar2b==0){
    FUN_0007e2fa(0x00099cbd,0x000f08f4,0x000f08c7,0xf0);
    FUN_0007e2fa(0x000f090b,0x2000b498);
    FUN_0007e2ec(0x000f08c7,0xf0);
  }
  (void)uVar6;
  unsigned int r0res=uVar3+uVar4;
  unsigned int r1res=uVar5 + (unsigned int)((int)uVar3>>31) + (unsigned int)(((unsigned long long)uVar3+uVar4)>>32);
  return ((unsigned long long)r1res<<32)|r0res;
}

