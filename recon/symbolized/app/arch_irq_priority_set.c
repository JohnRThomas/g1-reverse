#include "g1_app_symbols.h"
#include "../../headers/g1_nrf_regs.h"
/* readable reconstruction; identity: FUN_0005010c @ 0x0005010c
 * public-name: arch_irq_priority_set
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_irq_priority_set                    <= FUN_0005010c @ 0x0005010c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f1ba8                             @ 0x000f1ba8
 *   rodata_f1bde                             @ 0x000f1bde   [INLINED -- G6 literal batch]
 *   rodata_f1bf9                             @ 0x000f1bf9   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0005010c @ 0x5010c  (parity: 300/300 trials, PROVEN) */

extern int printk(int a, int b, int c, int d, int e);
extern int assert_post_action(int a, int b);

void arch_irq_priority_set(int param_1, unsigned int param_2, int param_3, int param_4)
{
    int r0 = param_1;
    int r2 = param_3;
    int r3 = (int)(param_2 + 1U);
    signed char cVar1;
    int bVar5;

    if ((unsigned int)r3 > 7) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"prio <= ((1UL << (3)) - 1)") /*=0xf1bde*/, ((unsigned long)&rodata_f1ba8) /*=0xf1ba8*/, 0x5c, param_4);
        r3 = 7;
        r2 = param_1;
        printk(((unsigned long)"\tinvalid priority %d for %d irq! values must be less than %lu\n\n") /*=0xf1bf9*/, (int)param_2, r2, r3, 0);
        r0 = assert_post_action(((unsigned long)&rodata_f1ba8) /*=0xf1ba8*/, 0x5c);
    }
    r0 = (int)(signed char)r0;
    bVar5 = (r0 >= 0);
    if (bVar5) {
        r0 = r0 + (int)0xe0000000;
    } else {
        r2 = (int)G1_SCB_CCR;
    }
    r3 = r3 << 5;
    r3 = (unsigned char)r3;
    if (bVar5) {
        r0 = r0 + 0xe100;
        cVar1 = (signed char)r3;
        *(char *)(r0 + 0x300) = cVar1;
    } else {
        r0 = r0 & 0xf;
        cVar1 = (signed char)r3;
        *(char *)(r2 + r0) = cVar1;
    }
}
