#include "g1_app_symbols.h"
/* named: nrfx_pdm_uninit */
/* globals referenced:
//   0x2000b330  g_pdm_cb                     
//   0x50026000  NRF_PDM_BASE                 
*/
/* Reconstructed nrfx_pdm_uninit @ 0x661dc  (parity: 300/300 trials, PROVEN) */

extern void arch_irq_disable(unsigned int);
extern void pdm_release_pin(unsigned int);

void nrfx_pdm_uninit(void)
{
    arch_irq_disable(0x26);
    *(volatile unsigned int*)(NRF_PDM_BASE /*=0x50026000*/ + 0x500) = 0;
    if (*(volatile unsigned char*)(((uintptr_t)&g_pdm_cb) /*=0x2000b330*/ + 0x15) == 0) {
        unsigned int uVar3 = *(volatile unsigned int*)(NRF_PDM_BASE /*=0x50026000*/ + 0x544);
        pdm_release_pin(*(volatile unsigned int*)(NRF_PDM_BASE /*=0x50026000*/ + 0x540));
        pdm_release_pin(uVar3);
    }
    *(volatile unsigned char*)(((uintptr_t)&g_pdm_cb) /*=0x2000b330*/ + 0x10) = 0;
    return;
}

