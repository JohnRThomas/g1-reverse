#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00060a5c @ 0x00060a5c
 * public-name: FUN_00060a5c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_qspi_mem_busy_check                 <= FUN_00066ae0 @ 0x00066ae0
 *   nrfx_qspi_uninit                         <= FUN_00066b24 @ 0x00066b24
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   audio_i2s_stop_and_reset_channels        <= FUN_00083906 @ 0x00083906
 *   audio_i2s_start_channels                 <= FUN_0008392e @ 0x0008392e
 * address symbols (name @ address):
 *   g_qspi_nor_initialized                   @ 0x2001d535
 */
/* Full reconstruction FUN_00060a5c @ 0x00060a5c (100-byte exact extent). */
#include <stdint.h>

extern uint64_t audio_i2s_stop_and_reset_channels(void *device);
extern void z_impl_k_sem_take(void *object, uint32_t inherited_r1, uint32_t, uint32_t);
#define g1_recon_nrfx_qspi_mem_busy_check nrfx_qspi_mem_busy_check
extern uintptr_t g1_recon_nrfx_qspi_mem_busy_check(void);
extern void FUN_00074844(uint32_t, uint32_t);
extern void nrfx_qspi_uninit(void);
extern void audio_i2s_start_channels(void *device);

void FUN_00060a5c(uint8_t *device)
{
    uint8_t *state = *(uint8_t **)(device + 0x10);
    if (*(volatile uint8_t *)(state + 0x60) != 0)
        return;

    uint64_t inherited = audio_i2s_stop_and_reset_channels(device);
    z_impl_k_sem_take(state + 0x48, (uint32_t)(inherited >> 32), 0, 0);
    if (*(volatile uint32_t *)(state + 0x50) == 0) {
        while (g1_recon_nrfx_qspi_mem_busy_check() != 0x0bad0000u)
            FUN_00074844(0x667u, 0);
        nrfx_qspi_uninit();
        *(volatile uint8_t *)((unsigned long)&g_qspi_nor_initialized) /*=0x2001d535*/ = 0;
    }
    audio_i2s_start_channels(device);
}
