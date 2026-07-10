#include "g1_app_symbols.h"
/* named: cjson_create_object */
/* globals referenced:
//   0x20002bac  g_cjson_hooks                
*/
/* Reconstructed cjson_create_object @ 0x64ca4  (parity: 300/300 trials, PROVEN) */

extern unsigned int alloc_zeroed_node(unsigned int a);

void cjson_create_object(void)
{
    unsigned int v = *(volatile unsigned int*)((uintptr_t)&g_cjson_hooks) /*=0x20002bac*/;
    unsigned int r = alloc_zeroed_node(v);
    if (r != 0) {
        *(volatile unsigned int*)(r + 0xc) = 0x40;
    }
}

