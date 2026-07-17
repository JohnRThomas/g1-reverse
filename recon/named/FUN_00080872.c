/* readable reconstruction; identity: FUN_00080872 @ 0x00080872
 * public-name: FUN_00080872
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decode_tstr                         <= FUN_00085f9c @ 0x00085f9c
 *   cbor_decode_map_start                    <= FUN_00085fa2 @ 0x00085fa2
 *   thunk_FUN_00085df6                       <= FUN_00085fce @ 0x00085fce
 *   cbor_decode_skip_value                   <= FUN_00086064 @ 0x00086064
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 */
/* Full reconstruction of FUN_00080872 @ 0x00080872 (174 bytes). */
#include <stdint.h>

typedef int (*field_decoder_t)(void *input, void *destination);

struct field_decoder {
    uint32_t identifier;
    uint32_t kind;
    field_decoder_t decode;
    void *destination;
    uint8_t decoded;
    uint8_t reserved[3];
};

extern int cbor_decode_map_start(void);
extern int cbor_decode_tstr(void *input, uint32_t item[2]);
extern int thunk_FUN_00085df6(void *input);
extern int cbor_decode_skip_value(void *input, int argument);
extern int memcmp(uint32_t identifier, uint32_t expected);

int FUN_00080872(void *input, struct field_decoder *fields,
                 uint32_t field_count, uint32_t *decoded_count)
{
    struct field_decoder *field;
    uint32_t item[2];

    if (cbor_decode_map_start() == 0)
        return -77;

    *decoded_count = 0;
    field = fields;

    for (;;) {
        if (cbor_decode_tstr(input, item) != 0) {
            uint32_t index = 0;

            while (index != field_count) {
                if (field >= fields + field_count)
                    field = fields;

                if (item[1] == field->kind &&
                    memcmp(item[0], field->identifier) == 0) {
                    if (field->decoded != 0)
                        return -112;
                    if (field->decode(input, field->destination) == 0)
                        return -35;

                    field->decoded = 1;
                    ++field;
                    ++*decoded_count;
                    break;
                }

                ++field;
                ++index;
            }

            if (index != field_count)
                continue;
            if (cbor_decode_skip_value(input, 0) != 0)
                continue;
        }

        if (thunk_FUN_00085df6(input) != 0)
            return 0;
        return -77;
    }
}
