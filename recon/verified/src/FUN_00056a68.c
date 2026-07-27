/* Reconstructed FUN_00056a68 @ 0x56a68  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(unsigned int,...);
extern int FUN_00080ed8(unsigned int);
extern void FUN_00056704(void*,unsigned int);
int FUN_00056a68(unsigned short* param_1, unsigned char param_2){
  int iVar1; unsigned int uVar2;
  switch(*(unsigned char*)((int)param_1+0xd)){
  case 2:
    *(unsigned char*)((int)param_1+0xc)=param_2;
    uVar2=0;
    break;
  case 6:
    if(*(char*)((int)param_1+2)==1) return 0;
    FUN_0007e2fa(0x00099cbd,0x000f7a30,0x000f3a5d,0x5d9);
    FUN_0007e2fa(0x000f3dad,*(unsigned char*)((int)param_1+2));
    FUN_0007e2ec(0x000f3a5d,0x5d9);
    /* fallthrough */
  case 7:
    iVar1=FUN_00080ed8(*param_1);
    if(iVar1!=0) return iVar1;
    if(*(char*)((int)param_1+0xd)!=7) return 0;
    uVar2=8;
    break;
  case 8:
    return 0;
  default:
    return -128;
  }
  FUN_00056704(param_1,uVar2);
  return 0;
}
