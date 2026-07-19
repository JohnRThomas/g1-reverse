/* readable reconstruction; identity: FUN_00063898 @ 0x00063898
 * public-name: nrf_rtc_timer_chan_free
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf_rtc_timer_chan_free                  <= FUN_00063898 @ 0x00063898
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6659                             @ 0x000f6659
 *   rodata_f66a6                             @ 0x000f66a6
 *   nrf_rtc_timer_free_channels              @ 0x2000b2d4
 */
/* Reconstructed FUN_00063898 @ 0x63898  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned long long assert_post_action(unsigned int, unsigned int);

void nrf_rtc_timer_chan_free(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    if (param_1 != 1) {
        printk(0x99cbdUL, 0xf66a6UL, 0xf6659UL, 0x257UL);
        assert_post_action(0xf6659UL, 0x257UL);
    }
    (void)__atomic_fetch_or((unsigned int *)0x2000b2d4UL, 2,
                            __ATOMIC_ACQ_REL);
}
