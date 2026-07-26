#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_k_thread__param_0168                   [param_0168; library]
 * Raw function identity: 0x00073cdc.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00073cdc @ 0x00073cdc
 * public-name: dlist_unlink_node
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dlist_unlink_node                        <= FUN_00073cdc @ 0x00073cdc
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f82f4                             @ 0x000f82f4
 *   rodata_f84d6                             @ 0x000f84d6
 */
/* Reconstructed FUN_00073cdc @ 0x73cdc  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int a,unsigned int b,unsigned int c,unsigned int d);
extern unsigned long long assert_post_action(unsigned int a,unsigned int b);

void dlist_unlink_node(unsigned int param_1, int *param_2, unsigned int param_3, unsigned int param_4)
{
    int *base;
    if ((unsigned int)param_2 == 0x20006720UL) {
        unsigned long long r;
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f84d6) /*=0xf84d6*/, ((unsigned long)&rodata_f82f4) /*=0xf82f4*/, 0x484);
        r = assert_post_action(((unsigned long)&rodata_f82f4) /*=0xf82f4*/, 0x484);
        base = (int*)(unsigned int)(r >> 32);
    } else {
        base = param_2;
    }
    {
        int iVar2 = *(volatile int*)base;
        int *piVar1 = *(volatile int**)((char*)base + 4);
        *(volatile int*)piVar1 = iVar2;
        *(volatile int**)((unsigned int)iVar2 + 4) = piVar1;
        *(volatile int*)base = 0;
        *(volatile int*)((char*)base + 4) = 0;
    }
}
