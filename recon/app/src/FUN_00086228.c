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

extern void FUN_000861c2(zcbor_state_prefix_t *state, int error);
extern unsigned int FUN_0007158c(char *, unsigned int);
extern int FUN_00086208(zcbor_state_prefix_t *state, unsigned int major_type,
                       const void *result, size_t max_result_len);
extern void *FUN_00086c44(void *destination, const void *source, size_t size);

int FUN_00086228(zcbor_state_prefix_t *state, const zcbor_string_t *input,
                 unsigned int major_type)
{
    size_t encoded_length_size;
    int encoded;

    if (state->payload >= state->payload_end ||
        input->len > (size_t)(state->payload_end - state->payload)) {
        FUN_000861c2(state, 8);
        return 0;
    }

    if (input->value != NULL) {
        encoded_length_size = FUN_0007158c(&input->len, sizeof(input->len));
        if ((size_t)state->payload + encoded_length_size + 1U + input->len >
            (size_t)state->payload_end) {
            FUN_000861c2(state, 8);
            return 0;
        }
    }

    encoded = FUN_00086208(state, major_type, &input->len, sizeof(input->len));
    if (!encoded) {
        return 0;
    }

    if (state->payload != input->value) {
        FUN_00086c44(state->payload, input->value, input->len);
    }
    state->payload += input->len;
    return encoded;
}
