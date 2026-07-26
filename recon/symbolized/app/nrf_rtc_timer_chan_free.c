#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00063898 @ 0x00063898
 * public-name: nrf_rtc_timer_chan_free
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf_rtc_timer_chan_free                  <= FUN_00063898 @ 0x00063898
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6659                             @ 0x000f6659
 *   rodata_f66a6                             @ 0x000f66a6   [INLINED -- G6 literal batch]
 *   nrf_rtc_timer_free_channels              @ 0x2000b2d4
 */
/* Reconstructed FUN_00063898 @ 0x63898  (parity: 300/300 trials, PROVEN) */

extern unsigned long long assert_post_action(unsigned int, unsigned int);

void nrf_rtc_timer_chan_free(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    if (param_1 != 1) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"chan > 0 && chan < (1 + 1)") /*=0xf66a6*/, ((unsigned long)&rodata_f6659) /*=0xf6659*/, 0x257UL);
        assert_post_action(((unsigned long)&rodata_f6659) /*=0xf6659*/, 0x257UL);
    }
    (void)__atomic_fetch_or((unsigned int *)((unsigned long)&nrf_rtc_timer_free_channels) /*=0x2000b2d4*/, 2,
                            __ATOMIC_ACQ_REL);
}
