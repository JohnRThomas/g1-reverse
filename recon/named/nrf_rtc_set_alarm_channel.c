/* readable reconstruction; identity: FUN_00063778 @ 0x00063778
 * public-name: nrf_rtc_set_alarm_channel
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   compare_set                              <= FUN_00063654 @ 0x00063654
 *   nrf_rtc_set_alarm_channel                <= FUN_00063778 @ 0x00063778
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6659                             @ 0x000f6659
 *   rodata_f66a6                             @ 0x000f66a6
 */
/* Reconstructed FUN_00063778 @ 0x63778  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int);
extern void compare_set(unsigned int, unsigned int, unsigned int,
                         unsigned int, unsigned int, unsigned int,
                         unsigned int);

void nrf_rtc_set_alarm_channel(int param_1, unsigned int param_2, unsigned int param_3,
                  unsigned int param_4, unsigned int param_5,
                  unsigned int param_6)
{
    if (param_1 != 1) {
        printk(0x99cbdUL, 0xf66a6UL, 0xf6659UL, 0x18dUL, param_1, param_2, param_3, param_4);
        assert_post_action(0xf6659UL, 0x18dUL);
    }
    compare_set((unsigned int)param_1, param_5, param_3, param_4,
                 param_5, param_6, 0);
}
