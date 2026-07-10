#include "g1_app_symbols.h"
/* named: nrfx_qspi_erase */
/* globals referenced:
//   0x2000b348  g_qspi_cb                    
*/
/* Reconstructed nrfx_qspi_erase @ 0x669f4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void printk(uint32_t,...);
extern uint32_t assert_post_action(uint32_t,uint32_t);
extern uint32_t qspi_activate(void);
extern uint32_t qspi_ready_wait(void);
extern void qspi_workaround_apply(void);
extern void nrf_qspi_cinstrdata_set(uint32_t,uint32_t);
extern void nrf_qspi_cinstrdata_get(uint32_t,uint32_t);

int nrfx_qspi_erase(uint8_t *param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4){
    volatile uint8_t *sb = (volatile uint8_t*)((uintptr_t)&g_qspi_cb) /*=0x2000b348*/;
    uint32_t r0v;
    r0v = *(volatile uint8_t*)(sb+0x30);
    if (r0v == 0){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"m_cb.state != NRFX_QSPI_STATE_UNINITIALIZED" /*=0xf6d9a*/,"WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_qspi.c" /*=0xf6d5e*/,0x1dd,param_4);
        r0v = assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_qspi.c" /*=0xf6d5e*/,0x1dd);
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
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"p_config->wipwait" /*=0xf6dde*/,"WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_qspi.c" /*=0xf6d5e*/,0x20a,param_4);
        r0v = assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_qspi.c" /*=0xf6d5e*/,0x20a);
        goto A20;
    } else {
        *(volatile uint32_t*)REG_5002b100 /*=0x5002b100*/ = 0;
        if (param_3 != 0) nrf_qspi_cinstrdata_get(param_1[1], param_3);
        return 0x0bad0000;
    }
}

