#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00067794 @ 0x00067794
 * public-name: nrfx_twim_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf_gpio_pin_reconfigure                 <= FUN_00067548 @ 0x00067548
 *   twim_configure                           <= FUN_000675c0 @ 0x000675c0
 *   nrfx_twim_init                           <= FUN_00067794 @ 0x00067794
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6c00                             @ 0x000f6c00   [INLINED -- G6 literal batch]
 *   rodata_f6fef                             @ 0x000f6fef
 *   rodata_f702b                             @ 0x000f702b
 *   g_nrfx_twim_cb                           @ 0x2000b3cc
 */
/* Reconstructed FUN_00067794 @ 0x67794  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_log.h"
extern void assert_post_action(uint32_t,uint32_t);
extern void nrf_gpio_pin_reconfigure(int,int,int,uint32_t,...);
extern void twim_configure(int,int*);

uint32_t nrfx_twim_init(int param_1, int *param_2, uint32_t param_3, uint32_t param_4){
    if (param_2 == 0){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"p_config") /*=0xf6c00*/, ((unsigned long)&rodata_f6fef) /*=0xf6fef*/, 0x102);
        assert_post_action(((unsigned long)&rodata_f6fef) /*=0xf6fef*/, 0x102);
    }
    uint8_t bVar1 = *(volatile uint8_t*)(param_1+4);
    uint32_t iVar3 = (uint32_t)bVar1 * 0x28;
    volatile uint8_t *iVar6 = (volatile uint8_t*)(((unsigned long)&g_nrfx_twim_cb) /*=0x2000b3cc*/ + iVar3);
    uint32_t uVar4 = 0x0bad0005;
    if (*(volatile uint8_t*)(iVar6+0x22) == 0){
        *(volatile uint32_t*)(iVar6+8) = 0;
        *(volatile uint32_t*)(iVar6+0) = param_3;
        *(volatile uint32_t*)(iVar6+4) = param_4;
        *(volatile uint8_t*)(iVar6+0x25) = 0;
        *(volatile uint8_t*)(iVar6+0x24) = 0;
        int8_t cVar2 = *(volatile int8_t*)((int)param_2+0xe);
        *(volatile uint8_t*)(iVar6+0x27) = (uint8_t)cVar2;
        if ((uint32_t)param_2[2] < 0xff00000){
            uVar4 = 6;
        } else {
            int bVar7;
            if (param_2[0] == 0x22){
                bVar7 = (param_2[1] == 0x23);
            } else {
                if (param_2[0] != 0x23) return 0x0bad0004;
                bVar7 = (param_2[1] == 0x22);
            }
            if (!bVar7) return 0x0bad0004;
            uVar4 = 0xb;
        }
        if (cVar2 == 0){
            if (param_2[0] == param_2[1]){
                printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f702b) /*=0xf702b*/, ((unsigned long)&rodata_f6fef) /*=0xf6fef*/, 0xf3);
                assert_post_action(((unsigned long)&rodata_f6fef) /*=0xf6fef*/, 0xf3);
            }
            nrf_gpio_pin_reconfigure(param_2[0], 0, 3, uVar4, param_4);
            nrf_gpio_pin_reconfigure(param_2[1], 0, 3, uVar4);
        }
        volatile uint8_t *iVar5b = (volatile uint8_t*)(((unsigned long)&g_nrfx_twim_cb) /*=0x2000b3cc*/ + iVar3);
        *(volatile uint8_t*)(iVar5b+0x26) = *(volatile uint8_t*)((int)param_2+0xd);
        twim_configure(param_1, param_2);
        uVar4 = 0x0bad0000;
        *(volatile uint8_t*)(iVar5b+0x22) = 1;
    }
    return uVar4;
}
