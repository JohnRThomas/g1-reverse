/* readable reconstruction; identity: FUN_0100aa3c @ 0x0100aa3c
 * public-name: sdc_ble_address_equal
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100aa3c @ 0x100aa3c  (CFG-directed candidate) */

#include <stdint.h>
#include <stdbool.h>

/* Constant-time comparison of a one-byte address type plus a six-byte BLE address. */
bool sdc_ble_address_equal(uint32_t lhs_type, const uint8_t *lhs,
                           uint32_t rhs_type, const uint8_t *rhs)
{
    uint32_t difference = lhs_type ^ rhs_type;
    difference += (uint32_t)(lhs[0] ^ rhs[0]);
    difference += (uint32_t)(lhs[1] ^ rhs[1]);
    difference += (uint32_t)(lhs[2] ^ rhs[2]);
    difference += (uint32_t)(lhs[3] ^ rhs[3]);
    difference += (uint32_t)(lhs[4] ^ rhs[4]);
    difference += (uint32_t)(lhs[5] ^ rhs[5]);
    return difference == 0u;
}
