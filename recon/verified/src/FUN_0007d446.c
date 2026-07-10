/* Reconstructed FUN_0007d446 @ 0x7d446  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000167a8(void);
uint16_t FUN_0007d446(void){
  int b;
  b=FUN_000167a8();
  if(*(volatile uint16_t*)(b+0x1072)==0) goto L492;
 L456:
  b=FUN_000167a8();
  if(*(volatile uint16_t*)(b+0x1074)>0x40) goto L4a2;
 L466:
  b=FUN_000167a8();
  if(*(volatile uint16_t*)(b+0x1074)>3) goto L484;
  b=FUN_000167a8();
  *(volatile uint16_t*)(b+0x1074)=4;
 L484:
  b=FUN_000167a8();
  return *(volatile uint16_t*)(b+0x1074);
 L492:
  b=FUN_000167a8();
  if(*(volatile uint16_t*)(b+0x1074)!=0) goto L456;
 L4a2:
  b=FUN_000167a8();
  *(volatile uint16_t*)(b+0x1074)=0x20;
  goto L466;
}

