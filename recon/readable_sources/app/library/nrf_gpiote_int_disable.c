#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00065e4c @ 0x00065e4c
 * public-name: nrf_gpiote_int_disable
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf_gpiote_int_disable                   <= FUN_00065e4c @ 0x00065e4c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6bc5                             @ 0x000f6bc5
 *   rodata_f6c09                             @ 0x000f6c09   [INLINED -- G6 literal batch]
 *   g_nrfx_gpiote_init_flag                  @ 0x2000b328
 *   REG_5002a308                             @ 0x5002a308
 */
/* Reconstructed FUN_00065e4c @ 0x65e4c  (parity: 300/300 trials, PROVEN) */

extern unsigned int assert_post_action(unsigned int a, unsigned int b);
extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void nrf_gpiote_int_disable(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int r0 = param_1;
    if (*(volatile unsigned char*)((unsigned long)&g_nrfx_gpiote_init_flag) /*=0x2000b328*/ != 1) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"m_cb.state == NRFX_DRV_STATE_INITIALIZED") /*=0xf6c09*/, ((unsigned long)&rodata_f6bc5) /*=0xf6bc5*/, 0x72, param_4);
        r0 = assert_post_action(((unsigned long)&rodata_f6bc5) /*=0xf6bc5*/, 0x72);
    }
    *(volatile int*)REG_5002a308 /*=0x5002a308*/ = 1 << (r0 & 0xff);
}
