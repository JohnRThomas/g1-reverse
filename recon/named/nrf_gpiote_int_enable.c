/* readable reconstruction; identity: FUN_00065e10 @ 0x00065e10
 * public-name: nrf_gpiote_int_enable
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf_gpiote_int_enable                    <= FUN_00065e10 @ 0x00065e10
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6bc5                             @ 0x000f6bc5
 *   rodata_f6c09                             @ 0x000f6c09
 *   g_nrfx_gpiote_init_flag                  @ 0x2000b328
 *   REG_5002a304                             @ 0x5002a304
 */
/* Reconstructed FUN_00065e10 @ 0x65e10  (parity: 300/300 trials, PROVEN) */

extern unsigned int assert_post_action(unsigned int a, unsigned int b);
extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void nrf_gpiote_int_enable(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int r0 = param_1;
    if (*(volatile unsigned char*)0x2000b328UL != 1) {
        printk(0x00099cbdUL, 0x000f6c09UL, 0x000f6bc5UL, 0x6c, param_4);
        r0 = assert_post_action(0x000f6bc5UL, 0x6c);
    }
    *(volatile int*)0x5002a304UL = 1 << (r0 & 0xff);
}
