#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_net_buf_simple__param_0285             [param_0285; library]
 * Raw function identity: 0x0005f518.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0005f518 @ 0x0005f518
 * public-name: net_buf_simple_push
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_simple_push                      <= FUN_0005f518 @ 0x0005f518
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f543a                             @ 0x000f543a
 *   rodata_f5484                             @ 0x000f5484
 */
/* Reconstructed FUN_0005f518 @ 0x5f518  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned long long assert_post_action(unsigned int, unsigned int);

void net_buf_simple_push(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int r0 = (unsigned int)*param_1;
    char *r3 = (char*)param_1;
    unsigned int r1 = param_2;
    if ((unsigned int)(r0 - param_1[2]) < param_2) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f5484) /*=0xf5484*/, ((unsigned long)&rodata_f543a) /*=0xf543a*/, 0x12dUL);
        unsigned long long rv = assert_post_action(((unsigned long)&rodata_f543a) /*=0xf543a*/, 0x12dUL);
        r0 = (unsigned int)rv;
        r1 = (unsigned int)(rv >> 32);
        r3 = (char*)0x12dUL;
    }
    unsigned short r2 = *(volatile unsigned short*)(r3 + 4);
    *(volatile unsigned int*)r3 = r0 - r1;
    *(volatile short*)(r3 + 4) = (short)r1 + (short)r2;
}
