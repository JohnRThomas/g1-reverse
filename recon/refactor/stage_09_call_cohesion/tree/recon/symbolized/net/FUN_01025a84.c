#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01025a84 @ 0x01025a84
 * public-name: FUN_01025a84
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01025a84 @ 0x1025a84  (CFG-directed candidate) */
#include <stdint.h>
void FUN_01025a84(void *destination, uint32_t value_arg, uint32_t length) {
    volatile uint8_t *byte = (volatile uint8_t *)destination;
    uint8_t value=(uint8_t)value_arg;
    while ((((uintptr_t)byte)&3u)!=0u && length!=0u) {
        *byte++=value; --length;
    }
    uint32_t word=(uint32_t)value * 0x01010101u;
    volatile uint32_t *wide=(volatile uint32_t *)(uintptr_t)byte;
    while(length>=8u) {
        wide[0]=word; wide[1]=word; wide+=2; length-=8u;
    }
    if(length>=4u) { *wide++=word; length-=4u; }
    byte=(volatile uint8_t *)(uintptr_t)wide;
    if(length!=0u) { *byte++=value; --length; }
    if(length!=0u) { *byte++=value; --length; }
    if(length!=0u) { *byte=value; }
}
