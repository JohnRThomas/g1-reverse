#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010282fc @ 0x010282fc
 * public-name: controller_default_bounds_build
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_duration_to_units             <= FUN_0100d538 @ 0x0100d538
 *   controller_default_bounds_build          <= FUN_010282fc @ 0x010282fc
 */
/* net-core FUN_010282fc @ 0x010282fc
 * Readable identity: controller_default_bounds_build.
 */
#include <stdint.h>

extern uint32_t FUN_01013d90(const void *timing);
extern uint32_t FUN_0101bbc8(const void *timing);
extern uint32_t controller_duration_to_units(uint32_t duration, uint32_t units);

void controller_default_bounds_build(const uint16_t *controller, uint32_t use_default,
                  volatile uint16_t *bounds)
{
    const void *timing = controller + 0x18u;
    uint32_t duration = use_default == 0u
        ? FUN_01013d90(timing)
        : FUN_0101bbc8(timing);
    uint32_t first_limit = controller_duration_to_units(duration, 2u);
    uint32_t second_limit = controller_duration_to_units(duration, 2u);
    uint32_t first = controller[0x2bu];
    uint32_t second = controller[0x2cu];

    if (first_limit <= first) {
        first = first_limit;
    }
    bounds[0] = controller[0];
    first &= 0xffffu;
    if (first < 0x1bu) {
        first = 0x1bu;
    }
    if (first >= 0xfbu) {
        first = 0xfbu;
    }

    if (second_limit <= second) {
        second = second_limit;
    }
    bounds[1] = (uint16_t)first;
    second &= 0xffffu;
    if (second < 0x1bu) {
        second = 0x1bu;
    }
    if (second >= 0xfbu) {
        second = 0xfbu;
    }

    if (duration < 0x148u) {
        duration = 0x148u;
    }
    bounds[3] = (uint16_t)second;
    if (duration >= 0xa90u) {
        duration = 0xa90u;
    }
    bounds[2] = (uint16_t)duration;
    bounds[4] = (uint16_t)duration;
}
