/* Reconstructed internal net function FUN_0100eec8 @ 0x0100eec8.
 * Reachable code is [0x0100eec8,0x0100ef04), 60 bytes.  The word at
 * [0x0100ef04,0x0100ef08) is its literal pool; 0x0100ef08 begins separate
 * code reached by other paths, not fall-through from the terminal assertion. */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern void FUN_0100ebb8(void);
extern void FUN_0102583c(unsigned event);
void FUN_0100eec8(uint8_t *item,uint32_t value)
{
    if(item[8]!=0){FUN_0100ebb8();return;}
    *(uint32_t *)(item+4)=value; item[8]=3;
    uint32_t primask=__get_PRIMASK(); __disable_irq();
    volatile uint8_t *q=(volatile uint8_t *)0x21000ec8u;
    uint8_t **link=(uint8_t **)(q+8); *(uint8_t **)item=(uint8_t *)(q+8);
    uint8_t *head=*(uint8_t **)(q+8);
    if(head==0 || head[8]!=1) link=*(uint8_t ***)(q+4);
    *link=item; *(uint8_t ***)(q+4)=(uint8_t **)item;
    if(primask==0) __enable_irq();
    FUN_0102583c(q[0]);
}
