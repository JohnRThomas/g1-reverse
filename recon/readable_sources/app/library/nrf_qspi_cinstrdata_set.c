#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   0x00066780       => struct g1_layout_qspi_cinstrdat_regs__global_1338       [global_1338; library]
 * Raw function identity: 0x00066720.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00066720 @ 0x00066720
 * public-name: nrf_qspi_cinstrdata_set
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   NRF_QSPI_BASE                            @ 0x5002b000
 */
/* nrf_qspi_cinstrdata_set @ 0x00066720; raw FUN_00066720 */
#include <stdint.h>

void nrf_qspi_cinstrdata_set(uint32_t length, const uint8_t *data)
{
    volatile uint32_t *qspi = (volatile uint32_t *)NRF_QSPI_BASE /*=0x5002b000*/;
    uint32_t reg = 0;

    switch (length) {
    case 9:
        reg |= (uint32_t)data[7] << 24;
    case 8:
        reg |= (uint32_t)data[6] << 16;
    case 7:
        reg |= (uint32_t)data[5] << 8;
    case 6:
        reg |= data[4];
        qspi[0x63c / 4] = reg;
        reg = 0;
    case 5:
        reg |= (uint32_t)data[3] << 24;
    case 4:
        reg |= (uint32_t)data[2] << 16;
    case 3:
        reg |= (uint32_t)data[1] << 8;
    case 2:
        reg |= data[0];
        qspi[0x638 / 4] = reg;
    default:
        return;
    }
}
