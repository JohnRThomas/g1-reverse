/* readable reconstruction; identity: FUN_00012580 @ 0x00012580
 * public-name: us_to_ticks_scaled
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __floatdidf                              <= FUN_0000d89c @ 0x0000d89c
 *   __muldf3                                 <= FUN_0000d8f8 @ 0x0000d8f8
 *   __aeabi_ldivmod                          <= FUN_0000e1a4 @ 0x0000e1a4
 *   __fixdfdi                                <= FUN_0000ec34 @ 0x0000ec34
 *   us_to_ticks_scaled                       <= FUN_00012580 @ 0x00012580
 */
/* Reconstructed FUN_00012580 @ 0x12580 */
#include <stdint.h>

extern uint64_t __floatdidf(uint32_t, uint32_t);
extern uint64_t __muldf3(uint32_t, uint32_t, uint32_t, uint32_t);
extern uint64_t __fixdfdi(void);
extern uint32_t __aeabi_ldivmod(uint32_t, uint32_t, uint32_t, uint32_t);

void us_to_ticks_scaled(uint32_t result[2], uint32_t multiplicand,
                  uint32_t multiplier)
{
    uint64_t product = (uint64_t)multiplicand * multiplier;
    uint32_t high = (uint32_t)(product >> 32) +
                    multiplier * (uint32_t)((int32_t)multiplicand >> 31);
    uint64_t quotient = __floatdidf((uint32_t)product, high);
    uint64_t state = __muldf3((uint32_t)quotient,
                                  (uint32_t)(quotient >> 32),
                                  0x3a92a305u, 0x40239d01u);
    state = __fixdfdi();
    result[0] = __aeabi_ldivmod((uint32_t)state, (uint32_t)(state >> 32),
                             1000000u, 0);
    result[1] = 1000000u;
}
