/* readable reconstruction; identity: FUN_00052bf8 @ 0x00052bf8
 * public-name: entropy_get_entropy_isr_call
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   entropy_get_entropy_isr_call             <= FUN_00052bf8 @ 0x00052bf8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   entropy_dev                              @ 0x00087b90
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f2a45                             @ 0x000f2a45   [INLINED -- G6 literal batch]
 *   rodata_f2a79                             @ 0x000f2a79   [INLINED -- G6 literal batch]
 *   rodata_f2a99                             @ 0x000f2a99   [INLINED -- G6 literal batch]
 */
#include "../headers/g1_log.h"
/* Reconstructed FUN_00052bf8 @ 0x52bf8  (parity: 300/300 trials, PROVEN) */

extern unsigned int assert_post_action(unsigned int a, unsigned int b);

void entropy_get_entropy_isr_call(unsigned int param_1, unsigned int param_2)
{
    volatile unsigned int *pp = (volatile unsigned int*)(0x00087b90UL + 8);
    unsigned int A = *pp;
    unsigned int r4 = *(volatile unsigned int*)A;
    unsigned int arg1, arg2;
    if (r4 == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f2a79UL, 0x000f2a45UL, 0x4d);
        printk(0x000f2a99UL, 0, 0, 0);
        assert_post_action(0x000f2a45UL, 0x4d);
        arg1 = 0x4d;
        arg2 = 0x000f2a45UL;
    } else {
        arg1 = param_1;
        arg2 = param_2;
    }
    {
        void (*fp)(unsigned int, unsigned int, unsigned int) = (void (*)(unsigned int,unsigned int,unsigned int))r4;
        fp(0x00087b90UL, arg1, arg2);
    }
}
