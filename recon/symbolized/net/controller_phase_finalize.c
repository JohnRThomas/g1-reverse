#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010129f4 @ 0x010129f4
 * public-name: controller_phase_finalize
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_phase_finalize                <= FUN_010129f4 @ 0x010129f4
 */
/* net-core FUN_010129f4 @ 0x010129f4 */
#include <stdint.h>

/* Raw/address backmap: controller_fatal = FUN_01008d00@0x01008d00. */
extern void sdc_assertion_fail(uint32_t module, uint32_t line);

static __attribute__((always_inline)) inline uint32_t
finish_phase(volatile uint8_t *phase, uint8_t bit, uint32_t result)
{
    uint8_t next_count = (uint8_t)(phase[5] + 1u);
    phase[5] = next_count;
    if (next_count == phase[1]) {
        uint8_t next_state = (uint8_t)(phase[3] | bit);
        phase[5] = 0;
        phase[3] = next_state;
        if (phase[2] == next_state) {
            phase[3] = 0;
            phase[4] = (uint8_t)(phase[4] + 1u);
        }
    }
    return result;
}

uint32_t controller_phase_finalize(volatile uint8_t *phase)
{
    uint8_t flags = phase[2];

    if ((flags & 1u) != 0 && (phase[3] & 1u) == 0) {
        return finish_phase(phase, 1u, 0x25u);
    }
    if ((flags & 2u) != 0 && (phase[3] & 2u) == 0) {
        return finish_phase(phase, 2u, 0x26u);
    }

    for (;;) {
        if ((flags & 4u) == 0) {
            uint8_t next_count = (uint8_t)(phase[5] + 1u);
            phase[5] = next_count;
            if (next_count == phase[1]) {
                phase[5] = 0;
                if (phase[3] == flags) {
                    phase[3] = 0;
                    phase[4] = (uint8_t)(phase[4] + 1u);
                }
            }
            sdc_assertion_fail(0x2eu, 0x39u);
        }
        if ((phase[3] & 4u) == 0) {
            return finish_phase(phase, 4u, 0x27u);
        }
        flags = phase[2];
    }
}
