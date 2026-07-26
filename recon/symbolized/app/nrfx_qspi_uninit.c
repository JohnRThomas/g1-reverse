#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00066b24 @ 0x00066b24
 * public-name: nrfx_qspi_uninit
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_irq_disable                         <= FUN_000500c8 @ 0x000500c8
 *   qspi_deactivate                          <= FUN_00066478 @ 0x00066478
 *   nrfx_qspi_uninit                         <= FUN_00066b24 @ 0x00066b24
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   nrf_gpio_cfg_default                     <= FUN_000851fa @ 0x000851fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6d5e                             @ 0x000f6d5e
 *   rodata_f6d9a                             @ 0x000f6d9a
 *   g_qspi_cb                                @ 0x2000b348
 *   NRF_QSPI_BASE                            @ 0x5002b000
 */
/* Reconstructed FUN_00066b24 @ 0x66b24  (parity: 300/300 trials, PROVEN) */

extern void arch_irq_disable(int a);
extern void qspi_deactivate(void);
extern void nrf_gpio_cfg_default(unsigned a);
extern void assert_post_action(unsigned a,unsigned b);
void nrfx_qspi_uninit(void){
    volatile unsigned char *g = (volatile unsigned char*)((unsigned long)&g_qspi_cb) /*=0x2000b348*/;
    if (g[0x30] == 0){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f6d9a) /*=0xf6d9a*/,((unsigned long)&rodata_f6d5e) /*=0xf6d5e*/,0x2b1,0);
        assert_post_action(((unsigned long)&rodata_f6d5e) /*=0xf6d5e*/,0x2b1);
    }
    arch_irq_disable(0x2b);
    qspi_deactivate();
    if (g[0x3a] == 0){
        volatile unsigned *b = (volatile unsigned*)NRF_QSPI_BASE /*=0x5002b000*/;
        unsigned v524 = b[0x524/4];
        unsigned v528 = b[0x528/4];
        unsigned v530 = b[0x530/4];
        unsigned v534 = b[0x534/4];
        unsigned v538 = b[0x538/4];
        unsigned v53c = b[0x53c/4];
        nrf_gpio_cfg_default(v524 & 0xff);
        nrf_gpio_cfg_default(v528 & 0xff);
        nrf_gpio_cfg_default(v530 & 0xff);
        unsigned r5 = v538 & 0xff;
        nrf_gpio_cfg_default(v534 & 0xff);
        unsigned r4 = v53c & 0xff;
        if (r5 != 0xff) nrf_gpio_cfg_default(r5);
        if (r4 != 0xff) nrf_gpio_cfg_default(r4);
    }
    g[0x30] = 0;
}
