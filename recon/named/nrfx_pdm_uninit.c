/* readable reconstruction; identity: FUN_000661dc @ 0x000661dc
 * public-name: nrfx_pdm_uninit
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_irq_disable                         <= FUN_000500c8 @ 0x000500c8
 *   pdm_release_pin                          <= FUN_00066130 @ 0x00066130
 *   nrfx_pdm_uninit                          <= FUN_000661dc @ 0x000661dc
 * address symbols (name @ address):
 *   g_pdm_cb                                 @ 0x2000b330
 *   NRF_PDM_BASE                             @ 0x50026000
 */
/* Reconstructed FUN_000661dc @ 0x661dc  (parity: 300/300 trials, PROVEN) */

extern void arch_irq_disable(unsigned int);
extern void pdm_release_pin(unsigned int);

void nrfx_pdm_uninit(void)
{
    arch_irq_disable(0x26);
    *(volatile unsigned int*)(0x50026000UL + 0x500) = 0;
    if (*(volatile unsigned char*)(0x2000b330UL + 0x15) == 0) {
        unsigned int uVar3 = *(volatile unsigned int*)(0x50026000UL + 0x544);
        pdm_release_pin(*(volatile unsigned int*)(0x50026000UL + 0x540));
        pdm_release_pin(uVar3);
    }
    *(volatile unsigned char*)(0x2000b330UL + 0x10) = 0;
    return;
}
