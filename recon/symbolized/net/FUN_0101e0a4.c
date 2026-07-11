/* Reconstructed internal net function FUN_0101e0a4 @ 0x0101e0a4, 104 bytes. */
#include <stdint.h>
extern void FUN_01008d00(unsigned,unsigned); extern void *FUN_01009d18(uint16_t,unsigned);
extern void FUN_0101df84(void *,void *);
unsigned FUN_0101e0a4(uint8_t *c,uint8_t *e,uint8_t v){
 if(!c) FUN_01008d00(0x1a,0xb1); if(c[0xc6]!=0x2a)return 0xc;
 if(!v)c[0xc6]=0x2b; else {c[0x14a]=v;c[0x14b]=0x1f;c[0xc6]=0x30;if(e){void*t=FUN_01009d18(*(uint16_t*)(e+0x17e),7);if(!t)FUN_01008d00(0x1a,0xd3);FUN_0101df84(t,e);}}
 if((int8_t)c[0x104]<0)FUN_01008d00(0x1a,0xd8);return 0;
}
