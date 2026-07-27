#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
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
/* Reconstructed FUN_00052bf8 @ 0x52bf8  (parity: 300/300 trials, PROVEN) */

extern int assert_post_action(int, int);

void entropy_get_entropy_isr_call(unsigned int param_1, unsigned int param_2)
{
    volatile unsigned int *pp = (volatile unsigned int*)(((unsigned long)&entropy_dev) /*=0x87b90*/ + 8);
    unsigned int A = *pp;
    unsigned int r4 = *(volatile unsigned int*)A;
    unsigned int arg1, arg2;
    if (r4 == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"api->get_entropy != ((void *)0)") /*=0xf2a79*/, ((unsigned long)"WEST_TOPDIR/zephyr/include/zephyr/drivers/entropy.h") /*=0xf2a45*/, 0x4d);
        printk(((unsigned long)"\tCallback pointer should not be NULL\n") /*=0xf2a99*/, 0, 0, 0);
        assert_post_action(((unsigned long)"WEST_TOPDIR/zephyr/include/zephyr/drivers/entropy.h") /*=0xf2a45*/, 0x4d);
        arg1 = 0x4d;
        arg2 = ((unsigned long)"WEST_TOPDIR/zephyr/include/zephyr/drivers/entropy.h") /*=0xf2a45*/;
    } else {
        arg1 = param_1;
        arg2 = param_2;
    }
    {
        void (*fp)(unsigned int, unsigned int, unsigned int) = (void (*)(unsigned int,unsigned int,unsigned int))r4;
        fp(((unsigned long)&entropy_dev) /*=0x87b90*/, arg1, arg2);
    }
}
