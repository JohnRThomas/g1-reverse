#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000669f4 @ 0x000669f4
 * public-name: nrfx_qspi_erase
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   qspi_ready_wait                          <= FUN_0006649c @ 0x0006649c
 *   qspi_activate                            <= FUN_000664f0 @ 0x000664f0
 *   nrf_qspi_cinstrdata_get                  <= FUN_000666e0 @ 0x000666e0
 *   nrf_qspi_cinstrdata_set                  <= FUN_00066720 @ 0x00066720
 *   qspi_workaround_apply                    <= FUN_000667e0 @ 0x000667e0
 *   nrfx_qspi_erase                          <= FUN_000669f4 @ 0x000669f4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6d5e                             @ 0x000f6d5e
 *   rodata_f6d9a                             @ 0x000f6d9a
 *   rodata_f6dde                             @ 0x000f6dde
 *   g_qspi_cb                                @ 0x2000b348
 *   REG_5002b100                             @ 0x5002b100
 *   REG_5002b308                             @ 0x5002b308
 *   REG_5002b634                             @ 0x5002b634
 */
/* Reconstructed FUN_000669f4 @ 0x669f4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void printk(uint32_t,...);
extern uint32_t assert_post_action(uint32_t,uint32_t);
extern uint32_t qspi_activate(void);
extern uint32_t qspi_ready_wait(void);
extern void qspi_workaround_apply(void);
extern void nrf_qspi_cinstrdata_set(uint32_t,uint32_t);
extern void nrf_qspi_cinstrdata_get(uint32_t,uint32_t);

int nrfx_qspi_erase(uint8_t *param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4){
    volatile uint8_t *sb = (volatile uint8_t*)((unsigned long)&g_qspi_cb) /*=0x2000b348*/;
    uint32_t r0v;
    r0v = *(volatile uint8_t*)(sb+0x30);
    if (r0v == 0){
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f6d9a) /*=0xf6d9a*/,((unsigned long)&rodata_f6d5e) /*=0xf6d5e*/,0x1dd,param_4);
        r0v = assert_post_action(((unsigned long)&rodata_f6d5e) /*=0xf6d5e*/,0x1dd);
    }
  A20:
    if (r0v != 1) return 0x0bad000b;
    if (*(volatile uint8_t*)(sb+0x38) == 0){
        if (qspi_activate() == 0x0bad0007) return 0x0bad0007;
    }
    *(volatile uint32_t*)REG_5002b308 /*=0x5002b308*/ = 1;
    qspi_workaround_apply();
    if (param_2 != 0) nrf_qspi_cinstrdata_set(param_1[1], param_2);
    *(volatile uint8_t*)(sb+0x39) = 0;
    *(volatile uint32_t*)REG_5002b100 /*=0x5002b100*/ = 0;
    {
        uint32_t v = ((uint32_t)param_1[2] << 0xc) | ((uint32_t)param_1[1] << 8) | (uint32_t)param_1[0]
                   | ((uint32_t)param_1[3] << 0xd) | ((uint32_t)param_1[4] << 0xe) | ((uint32_t)param_1[5] << 0xf);
        *(volatile uint32_t*)REG_5002b634 /*=0x5002b634*/ = v;
    }
    if (qspi_ready_wait() == 0x0bad0007){
        if (param_1[4] != 0) return 0x0bad0007;
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f6dde) /*=0xf6dde*/,((unsigned long)&rodata_f6d5e) /*=0xf6d5e*/,0x20a,param_4);
        r0v = assert_post_action(((unsigned long)&rodata_f6d5e) /*=0xf6d5e*/,0x20a);
        goto A20;
    } else {
        *(volatile uint32_t*)REG_5002b100 /*=0x5002b100*/ = 0;
        if (param_3 != 0) nrf_qspi_cinstrdata_get(param_1[1], param_3);
        return 0x0bad0000;
    }
}
