#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00066050 @ 0x00066050
 * public-name: pdm_configure_pins
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_irq_enable                          <= FUN_000500ac @ 0x000500ac
 *   nrf_gpio_pin_port_decode_65ff4           <= FUN_00065ff4 @ 0x00065ff4
 *   pdm_configure_pins                       <= FUN_00066050 @ 0x00066050
 * address symbols (name @ address):
 *   NRF_PDM_BASE                             @ 0x50026000
 *   REG_50026100                             @ 0x50026100
 *   REG_50026104                             @ 0x50026104
 */
/* Reconstructed FUN_00066050 @ 0x66050  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int arch_irq_enable(int,uint32_t,uint32_t,uint32_t,void*);
extern int nrf_gpio_pin_port_decode_65ff4(uint32_t*);
void pdm_configure_pins(uint8_t* param_1, uint32_t param_2){
    volatile uint32_t *const pdm_events_started =
        (volatile uint32_t *)REG_50026100 /*=0x50026100*/; /* PDM EVENTS_STARTED; raw: 0x50026000 + 0x100 */
    volatile uint32_t *const pdm_events_stopped =
        (volatile uint32_t *)REG_50026104 /*=0x50026104*/; /* PDM EVENTS_STOPPED; raw: 0x50026000 + 0x104 */
    (void)param_2;
    uint32_t local_1c; int iVar8;
    if(param_1[0x15]==0){
        local_1c = *(volatile uint32_t *)(param_1+4);
        iVar8 = nrf_gpio_pin_port_decode_65ff4(&local_1c);
        *(volatile uint32_t *)(iVar8+0xc) = 1u << (local_1c & 0xff);
        local_1c = *(volatile uint32_t *)(param_1+4);
        iVar8 = nrf_gpio_pin_port_decode_65ff4(&local_1c);
        iVar8 = iVar8 + local_1c*4;
        *(volatile uint32_t *)(iVar8+0x200) = (*(volatile uint32_t *)(iVar8+0x200) & 0xfffcf0f0u) | 3;
        local_1c = *(volatile uint32_t *)(param_1+8);
        iVar8 = nrf_gpio_pin_port_decode_65ff4(&local_1c);
        iVar8 = iVar8 + local_1c*4;
        *(volatile uint32_t *)(iVar8+0x200) = *(volatile uint32_t *)(iVar8+0x200) & 0xfffcf0f0u;
    }
    if(param_1[0x16]==0){
        uint32_t v4 = *(volatile uint32_t *)(param_1+4);
        uint32_t v8 = *(volatile uint32_t *)(param_1+8);
        *(volatile uint32_t *)(NRF_PDM_BASE /*=0x50026000*/+0x540) = v4;
        *(volatile uint32_t *)(NRF_PDM_BASE /*=0x50026000*/+0x544) = v8;
    }
    uint8_t bVar1=param_1[1], bVar2=param_1[0];
    uint32_t uVar11=*(volatile uint32_t *)(param_1+0xc);
    uint8_t bVar3=param_1[0x10], bVar4=param_1[0x11];
    uint8_t bVar6=param_1[0x14];
    uint8_t b13=param_1[0x13];
    uint8_t bVar5=param_1[0x16];
    uint32_t uVar10=*(volatile uint32_t *)(param_1+4);
    uint32_t uVar9=*(volatile uint32_t *)(param_1+8);
    *(volatile uint32_t *)(NRF_PDM_BASE /*=0x50026000*/+0x520) = b13;
    *(volatile uint32_t *)(NRF_PDM_BASE /*=0x50026000*/+0x54c) = bVar6;
    *(volatile uint32_t *)(NRF_PDM_BASE /*=0x50026000*/+0x504) = uVar11;
    *(volatile uint32_t *)(NRF_PDM_BASE /*=0x50026000*/+0x508) = ((uint32_t)(bVar1&1)<<1) | (bVar2&1);
    *(volatile uint32_t *)(NRF_PDM_BASE /*=0x50026000*/+0x518) = bVar3;
    *(volatile uint32_t *)(NRF_PDM_BASE /*=0x50026000*/+0x51c) = bVar4;
    if(bVar5==0){
        *(volatile uint32_t *)(NRF_PDM_BASE /*=0x50026000*/+0x540) = uVar10;
        *(volatile uint32_t *)(NRF_PDM_BASE /*=0x50026000*/+0x544) = uVar9;
    }
    /* Preserve the peripheral's exact write/read acknowledgement order. */
    *pdm_events_started = 0;
    uint32_t events_started = *pdm_events_started;
    *pdm_events_stopped = 0;
    uint32_t events_stopped = *pdm_events_stopped;
    arch_irq_enable(0x26, uVar9, events_started, events_stopped, param_1);
    *(volatile uint32_t *)(NRF_PDM_BASE /*=0x50026000*/+0x304) = 3;
}
