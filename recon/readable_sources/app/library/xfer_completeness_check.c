#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_nrfx_twim_control_block__param_0349    [param_0349; library]
 *   param_2          => struct g1_layout_nrfx_twim_cb__param_0350               [param_0350; library]
 * Raw function identity: 0x00085316.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00085316 @ 0x00085316
 * public-name: xfer_completeness_check
 * durable-map: recon/catalogs/function_names_app.json
 */
/* NCS 2.5.1 xfer_completeness_check @ 0x00085316 (FUN_00085316). */
#include <stdbool.h>
#include <stdint.h>

bool xfer_completeness_check(volatile uint8_t *twim,
                             const uint8_t *control_block)
{
    uint32_t expected;
    uint32_t actual;
    switch (control_block[0x20]) {
    case 0:
        expected = *(const uint32_t *)(control_block + 0x10);
        actual = *(volatile uint32_t *)(twim + 0x54c);
        break;
    case 1:
        expected = *(const uint32_t *)(control_block + 0x10);
        actual = *(volatile uint32_t *)(twim + 0x53c);
        break;
    case 2:
        if (*(const uint32_t *)(control_block + 0x10) !=
            *(volatile uint32_t *)(twim + 0x54c)) {
            goto incomplete;
        }
        expected = *(const uint32_t *)(control_block + 0x18);
        actual = *(volatile uint32_t *)(twim + 0x53c);
        break;
    case 3:
        if ((*(const uint32_t *)(control_block + 8) & (1u << 18)) != 0u) {
            if (*(const uint32_t *)(control_block + 0x10) !=
                *(volatile uint32_t *)(twim + 0x54c)) {
                goto incomplete;
            }
            return true;
        }
        expected = *(const uint32_t *)(control_block + 0x18);
        actual = *(volatile uint32_t *)(twim + 0x54c);
        break;
    default:
        return true;
    }
    if (expected == actual) {
        return true;
    }
incomplete:
    *(volatile uint32_t *)(twim + 0x500) = 0u;
    *(volatile uint32_t *)(twim + 0x500) = 6u;
    return false;
}
