#include "g1_net_symbols.h"
/* Reconstructed internal net function FUN_0101e0a4 @ 0x0101e0a4.
 * Exact owned extent [0x0101e0a4,0x0101e10c), 104 bytes; 0x0101e10c
 * begins a separate function.  There is no trailing literal pool. */
#include <stdint.h>
extern void FUN_01008d00(unsigned reason,unsigned line);
extern void *FUN_01009d18(uint16_t handle,unsigned type);
extern void FUN_0101df84(void *target,void *entry);
unsigned FUN_0101e0a4(uint8_t *context,uint8_t *entry,uint8_t value)
{
    if(context==0) FUN_01008d00(0x1a,0xb1);
    if(context[0xc6]!=0x2a) return 0x0c;
    if(value==0) context[0xc6]=0x2b;
    else {
        context[0x14a]=value; context[0x14b]=0x1f; context[0xc6]=0x30;
        if(entry!=0){
            void *target=FUN_01009d18(*(uint16_t *)(entry+0x17e),7);
            if(target==0) FUN_01008d00(0x1a,0xd3);
            FUN_0101df84(target,entry);
        }
    }
    if((int8_t)context[0x104]<0) FUN_01008d00(0x1a,0xd8);
    return 0;
}
