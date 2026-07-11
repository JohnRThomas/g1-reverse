/* Reconstructed internal net function FUN_0100eec8 @ 0x0100eec8, 60 bytes. */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern void FUN_0100ebb8(void);extern void FUN_0102583c(unsigned);
void FUN_0100eec8(uint8_t*i,uint32_t v){if(i[8]){FUN_0100ebb8();return;}*(uint32_t*)(i+4)=v;i[8]=3;uint32_t p=__get_PRIMASK();__disable_irq();volatile uint8_t*q=(volatile uint8_t*)0x21000ec8u;uint8_t**l=(uint8_t**)(q+8);*(uint8_t**)i=(uint8_t*)(q+8);uint8_t*h=*(uint8_t**)(q+8);if(!h||h[8]!=1)l=*(uint8_t***)(q+4);*l=i;*(uint8_t***)(q+4)=(uint8_t**)i;if(!p)__enable_irq();FUN_0102583c(q[0]);}
