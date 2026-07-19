#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   local_78         => struct g1_layout_snprintf_bounds__stack_1572            [stack_1572; G1-original]
 * Raw function identity: 0x0008712e.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0008712e @ 0x0008712e
 * public-name: snprintf_engine_bounded
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   printf_parse_format                      <= FUN_00078d90 @ 0x00078d90
 *   snprintf_engine_bounded                  <= FUN_0008712e @ 0x0008712e
 */
/* Full reconstruction FUN_0008712e @ 0x8712e (exact 86-byte extent).
 * CFG_VERIFY_NO_IF_CONVERSION: Unicorn leaks Thumb IT state past this block. */
#include <stdint.h>

struct format_descriptor {
    uint8_t *cursor;
    uint8_t *reserved;
    int32_t remaining;
    uint16_t flags;
    uint16_t limit;
    uint8_t *start;
    int32_t initial_remaining;
};

extern int printf_parse_format(uint32_t *error, struct format_descriptor *descriptor,
                        uint32_t option, uint32_t context);

int snprintf_engine_bounded(uint32_t *error, uint8_t *buffer, int32_t length,
                 uint32_t option, uint32_t context)
{
    if (length < 0) {
        *error = 0x8b;
        return -1;
    }
    int32_t remaining = length == 0 ? 0 : length - 1;
    struct format_descriptor descriptor = {
        .cursor = buffer,
        .remaining = remaining,
        .flags = 0x0208,
        .limit = 0xffff,
        .start = buffer,
        .initial_remaining = remaining,
    };
    int result = printf_parse_format(error, &descriptor, option, context);
    if (result < -1)
        *error = 0x8b;
    if (length != 0)
        *descriptor.cursor = 0;
    return result;
}
