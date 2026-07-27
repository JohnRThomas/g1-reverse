#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00060990 @ 0x00060990
 * public-name: qspi_get_zephyr_ret_code
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed qspi_get_zephyr_ret_code @ 0x60990  (CFG-directed candidate) */
#include <stdint.h>
int qspi_get_zephyr_ret_code(int result) { static const int16_t zephyr_errors[11] = {0,-16,-16,-16,-22,-140,-16,-16,-16,-16,-22}; uint32_t index=result-0x0bad0000u; return index <= 10u ? zephyr_errors[index] : -16; }
