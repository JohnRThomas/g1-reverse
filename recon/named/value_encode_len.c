/* readable reconstruction; identity: FUN_000715b8 @ 0x000715b8
 * public-name: value_encode_len
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_encode_set_error                    <= FUN_000861c2 @ 0x000861c2
 *   cbor_encode_put_type_byte                <= FUN_000861d4 @ 0x000861d4
 */
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

extern bool cbor_encode_put_type_byte(struct zcbor_state_prefix *state,
                         uint32_t major_type, uint32_t additional);
extern void cbor_encode_set_error(struct zcbor_state_prefix *state, uint32_t error);
#define encode_header_byte cbor_encode_put_type_byte
#define zcbor_error cbor_encode_set_error

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
