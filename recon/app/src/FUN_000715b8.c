/* Reconstructed value_encode_len @ 0x000715b8 from pinned zcbor v0.7.0.
 * Raw backmap: FUN_000715b8@0x000715b8. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct zcbor_state_prefix {
    uint8_t *payload;
    const uint8_t *payload_backup;
    size_t element_count;
    const uint8_t *payload_end;
};

extern bool FUN_000861d4(struct zcbor_state_prefix *state,
                         uint32_t major_type, uint32_t additional);
extern void FUN_000861c2(struct zcbor_state_prefix *state, uint32_t error);
#define encode_header_byte FUN_000861d4
#define zcbor_error FUN_000861c2

static inline __attribute__((always_inline))
uint8_t value_length_log2_ceil(size_t length)
{
    if (length <= 2u) {
        return (uint8_t)(length - 1u);
    }
    if (length <= 4u) {
        return 2u;
    }
    if (length <= 8u) {
        return 3u;
    }
    return 0u;
}

#define value_encode_len FUN_000715b8
bool value_encode_len(struct zcbor_state_prefix *state, uint32_t major_type,
                      const void *result_arg, size_t result_length)
{
    const uint8_t *result = (const uint8_t *)result_arg;
    size_t encoded_length =
        (result_length == 1u && result[0] <= 23u) ? 0u : result_length;

    if (state->payload + 1u + encoded_length > state->payload_end) {
        zcbor_error(state, 8u);
        return false;
    }

    uint8_t additional = encoded_length == 0u
        ? result[0]
        : (uint8_t)(24u + value_length_log2_ceil(encoded_length));
    if (!encode_header_byte(state, major_type, additional)) {
        return false;
    }

    while (encoded_length != 0u) {
        *state->payload++ = result[encoded_length - 1u];
        encoded_length--;
    }
    state->element_count++;
    return true;
}
