#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086228 @ 0x00086228
 * public-name: zcbor_str_encode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_min_encoded_size                    <= FUN_0007158c @ 0x0007158c
 *   cbor_encode_set_error                    <= FUN_000861c2 @ 0x000861c2
 *   cbor_encode_length_header                <= FUN_00086208 @ 0x00086208
 *   zcbor_str_encode                         <= FUN_00086228 @ 0x00086228
 *   memmove                                  <= FUN_00086c44 @ 0x00086c44
 */
/* Reconstructed zcbor_str_encode @ 0x00086228 (pinned zcbor_encode.c:str_encode). */
#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t *payload;
    const uint8_t *payload_bak;
    size_t elem_count;
    const uint8_t *payload_end;
} zcbor_state_prefix_t;

typedef struct {
    const uint8_t *value;
    size_t len;
} zcbor_string_t;

extern void cbor_encode_set_error(zcbor_state_prefix_t *state, int error);
extern unsigned int cbor_min_encoded_size(char *, unsigned int);
extern int cbor_encode_length_header(zcbor_state_prefix_t *state, unsigned int major_type,
                       const void *result, size_t max_result_len);
extern void *memmove(void *, const void *, size_t);

int zcbor_str_encode(zcbor_state_prefix_t *state, const zcbor_string_t *input,
                 unsigned int major_type)
{
    size_t encoded_length_size;
    int encoded;

    if (state->payload >= state->payload_end ||
        input->len > (size_t)(state->payload_end - state->payload)) {
        cbor_encode_set_error(state, 8);
        return 0;
    }

    if (input->value != NULL) {
        encoded_length_size = cbor_min_encoded_size(&input->len, sizeof(input->len));
        if ((size_t)state->payload + encoded_length_size + 1U + input->len >
            (size_t)state->payload_end) {
            cbor_encode_set_error(state, 8);
            return 0;
        }
    }

    encoded = cbor_encode_length_header(state, major_type, &input->len, sizeof(input->len));
    if (!encoded) {
        return 0;
    }

    if (state->payload != input->value) {
        memmove(state->payload, input->value, input->len);
    }
    state->payload += input->len;
    return encoded;
}
