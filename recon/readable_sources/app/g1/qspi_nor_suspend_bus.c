#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_param_0299_driver_data_collision__param_0299 [param_0299; G1-original]
 * Raw function identity: 0x00060a5c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00060a5c @ 0x00060a5c
 * public-name: qspi_nor_suspend_bus
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   qspi_nor_suspend_bus                     <= FUN_00060a5c @ 0x00060a5c
 *   nrfx_qspi_mem_busy_check                 <= FUN_00066ae0 @ 0x00066ae0
 *   nrfx_qspi_uninit                         <= FUN_00066b24 @ 0x00066b24
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
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
extern int g1_recon_nrfx_qspi_mem_busy_check(void);
extern void k_sleep(uint32_t, uint32_t);
extern void nrfx_qspi_uninit(void);
extern void audio_i2s_start_channels(void *device);

void qspi_nor_suspend_bus(uint8_t *device)
{
    uint8_t *state = *(uint8_t **)(device + 0x10);
    if (*(volatile uint8_t *)(state + 0x60) != 0)
        return;

    uint64_t inherited = audio_i2s_stop_and_reset_channels(device);
    z_impl_k_sem_take(state + 0x48, (uint32_t)(inherited >> 32), 0, 0);
    if (*(volatile uint32_t *)(state + 0x50) == 0) {
        while (g1_recon_nrfx_qspi_mem_busy_check() != 0x0bad0000u)
            k_sleep(0x667u, 0);
        nrfx_qspi_uninit();
        *(volatile uint8_t *)((unsigned long)&g_qspi_nor_initialized) /*=0x2001d535*/ = 0;
    }
    audio_i2s_start_channels(device);
}
