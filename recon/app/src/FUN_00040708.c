/* Reconstructed FUN_00040708 @ 0x40708  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000167a8(void);
void FUN_00040708(void){
  char cVar1=*(volatile signed char*)0x200034f5UL;
  int iVar3;
  iVar3=FUN_000167a8();
  if(((int)cVar1!=(unsigned int)*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2)) ||
     (((iVar3=FUN_000167a8(),*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2)!=5)&&
       (iVar3=FUN_000167a8(),*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2)!=0x13))&&
      (iVar3=FUN_000167a8(),*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2)!=0x14)&&
      (iVar3=FUN_000167a8(),*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2)!=0x15))){
    *(volatile unsigned char*)0x2001cdd2UL=0;
    *(volatile unsigned char*)0x2001cdd1UL=0;
  }
  *(volatile unsigned char*)0x2001cdd3UL=1;
  iVar3=FUN_000167a8();
  *(volatile char*)0x200034f5UL=*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2);
}

