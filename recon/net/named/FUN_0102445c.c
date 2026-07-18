/* readable reconstruction; identity: FUN_0102445c @ 0x0102445c
 * public-name: FUN_0102445c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102445c @ 0x0102445c -- raw backmap retained. */
#include <stdint.h>

/* 64-bit form of the same rounded fixed-point conversion. */
uint64_t FUN_0102445c(uint32_t low, uint32_t high)
{
    uint32_t minor = ((low >> 9) & 0x7fffu) * 0x3d09u +
                     (((low & 0x1ffu) * 0x3d09u + 0x100u) >> 9);
    uint32_t xlo = (low >> 24) | (high << 8);
    uint32_t xhi = high >> 24;

    uint32_t a_lo = (xlo << 5) - xlo;
    uint32_t a_hi = ((xhi << 5) | (xlo >> 27)) - xhi -
                    ((xlo << 5) < xlo);
    uint32_t b_lo = (a_lo << 6) - a_lo;
    uint32_t b_hi = ((a_hi << 6) | (a_lo >> 26)) - a_hi -
                    ((a_lo << 6) < a_lo);
    uint32_t c_lo = (b_lo << 3) + xlo;
    uint32_t c_hi = ((b_hi << 3) | (b_lo >> 29)) + xhi +
                    (c_lo < xlo);

    uint32_t result_lo = (c_lo << 15) + minor;
    uint32_t result_hi = (c_hi << 15) | (c_lo >> 17);
    result_hi += result_lo < minor;
    return ((uint64_t)result_hi << 32) | result_lo;
}
