#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00065f04 @ 0x00065f04
 * public-name: nvmc_word_write
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   REG_50039400                             @ 0x50039400
 */
/* nvmc_word_write @ 0x00065f04; raw FUN_00065f04.
 * nrfx_nvmc.c private helper for the nRF5340 NVMC write transaction. */
#include <stdint.h>
void nvmc_word_write(uint32_t address, uint32_t value)
{
    volatile uint32_t *const ready =
        (volatile uint32_t *)REG_50039400 /*=0x50039400*/; /* NRF_NVMC->READY */
    while (*ready == 0u) {
    }
    *(volatile uint32_t *)(uintptr_t)address = value;
    __atomic_thread_fence(__ATOMIC_SEQ_CST);
}
