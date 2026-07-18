/* Reconstructed zcbor str_decode helper @ 0x00085ef0.
 * Raw/address back-map: FUN_00085ef0 / 0x00085ef0.
 */
#include <stdint.h>

struct zcbor_state_prefix_raw {
    uint8_t *payload;
};

struct zcbor_string_raw {
    const uint8_t *value;
    uint32_t len;
};

#define zcbor_str_start_decode FUN_00085ebc
extern int zcbor_str_start_decode(void *state, struct zcbor_string_raw *result,
                                  uint32_t expected_major_type,
                                  uint32_t inherited_r3);

#define zcbor_str_decode FUN_00085ef0
int zcbor_str_decode(struct zcbor_state_prefix_raw *state,
                     struct zcbor_string_raw *result,
                     uint32_t expected_major_type, uint32_t inherited_r3)
{
    int success = zcbor_str_start_decode(state, result, expected_major_type,
                                         inherited_r3);
    if (success == 0) {
        return 0;
    }
    state->payload += result->len;
    return success;
}
