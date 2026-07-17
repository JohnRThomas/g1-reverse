/* Reconstructed decode_rle_byte_pairs @ 0x7da70 (raw FUN_0007da70).
 * Reviewed executable extent: 0x34 bytes, ending before FUN_0007daa4. */
#include <stdint.h>

extern void memset_bytes(void *destination, uint32_t value, uint32_t length);

uint32_t decode_rle_byte_pairs(const uint8_t *encoded,
                               uint32_t encoded_byte_count,
                               uint8_t *decoded)
{
    uint32_t encoded_offset = 0;
    uint32_t decoded_byte_count = 0;

    /* Each run is exactly [count, value].  The shipped loop tests only the
     * pair's first-byte offset, so an odd encoded length still consumes the
     * following value byte. */
    while (encoded_offset < encoded_byte_count) {
        uint32_t run_length = encoded[encoded_offset];
        uint8_t run_value = encoded[encoded_offset + 1];

        memset_bytes(decoded + decoded_byte_count, run_value, run_length);
        decoded_byte_count += run_length;
        encoded_offset += 2;
    }
    return decoded_byte_count;
}
