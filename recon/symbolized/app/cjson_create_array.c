#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00064c8c @ 0x00064c8c
 * public-name: cjson_create_array
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_create_array                       <= FUN_00064c8c @ 0x00064c8c
 *   alloc_zeroed_node                        <= FUN_00084fd4 @ 0x00084fd4
 * address symbols (name @ address):
 *   g_cjson_hooks                            @ 0x20002bac
 */
/* Reconstructed FUN_00064c8c @ 0x64c8c  (parity: 300/300 trials, PROVEN) */

extern unsigned int alloc_zeroed_node(unsigned int a);

void cjson_create_array(void)
{
    unsigned int v = *(volatile unsigned int*)((unsigned long)&g_cjson_hooks) /*=0x20002bac*/;
    unsigned int r = alloc_zeroed_node(v);
    if (r != 0) {
        *(volatile unsigned int*)(r + 0xc) = 0x20;
    }
}
