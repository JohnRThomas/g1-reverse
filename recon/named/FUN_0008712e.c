/* readable reconstruction; identity: FUN_0008712e @ 0x0008712e
 * public-name: FUN_0008712e
 * durable-map: recon/catalogs/function_names_app.json
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

extern int FUN_00078d90(uint32_t *error, struct format_descriptor *descriptor,
                        uint32_t option, uint32_t context);

int FUN_0008712e(uint32_t *error, uint8_t *buffer, int32_t length,
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
    int result = FUN_00078d90(error, &descriptor, option, context);
    if (result < -1)
        *error = 0x8b;
    if (length != 0)
        *descriptor.cursor = 0;
    return result;
}
