#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01012ad4 @ 0x01012ad4
 * public-name: FUN_01012ad4
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01012ad4 @ 0x1012ad4  (CFG-directed candidate) */
#include <stdint.h>
uint32_t FUN_01012ad4(const uint8_t *p) {
    uint32_t a = (p[2] & 1u) + ((p[2] >> 1) & 1u) + ((p[2] >> 2) & 1u);
    uint32_t b = (p[3] & 1u) + ((p[3] >> 1) & 1u) + ((p[3] >> 2) & 1u);
    return (uint8_t)(a * ((uint32_t)p[0] - p[4]) * p[1] - p[5] - b * p[1]);
}
