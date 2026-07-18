#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00066ae0 @ 0x00066ae0
 * public-name: nrfx_qspi_mem_busy_check
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_qspi_cinstr_xfer                    <= FUN_000669f4 @ 0x000669f4
 *   nrfx_qspi_mem_busy_check                 <= FUN_00066ae0 @ 0x00066ae0
 */
/* Reconstructed FUN_00066ae0 @ 0x00066ae0.
 * Raw/address back-map: FUN_00066ae0 / 0x00066ae0.
 * Private namespace target: g1_recon_nrfx_qspi_mem_busy_check.
 */
#include <stdint.h>

struct g1_qspi_cinstr_config {
    uint32_t command;
    uint16_t reserved;
};

#define nrfx_qspi_cinstr_xfer nrfx_qspi_cinstr_xfer
extern uint32_t nrfx_qspi_cinstr_xfer(
    const struct g1_qspi_cinstr_config *, const void *, void *, uint32_t);

#define nrfx_qspi_mem_busy_check nrfx_qspi_mem_busy_check
uint32_t nrfx_qspi_mem_busy_check(void)
{
    uint8_t status = 0;
    const struct g1_qspi_cinstr_config config = {
        .command = 0x01000205u,
        .reserved = 0,
    };
    uint32_t result = nrfx_qspi_cinstr_xfer(
        &config, &status, &status, 0);
    if (result == 0x0bad0000u && (status & 1u) != 0u)
        result = 0x0bad000bu;
    return result;
}
