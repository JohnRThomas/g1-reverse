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

extern int FUN_00085fa2(void);
extern int FUN_00085f9c(void *input, uint32_t item[2]);
extern int FUN_00085fce(void *input);
extern int FUN_00086064(void *input, int argument);
extern int FUN_00086be4(uint32_t identifier, uint32_t expected);

int FUN_00080872(void *input, struct field_decoder *fields,
                 uint32_t field_count, uint32_t *decoded_count)
{
    struct field_decoder *field;
    uint32_t item[2];

    if (FUN_00085fa2() == 0)
        return -77;

    *decoded_count = 0;
    field = fields;

    for (;;) {
        if (FUN_00085f9c(input, item) != 0) {
            uint32_t index = 0;

            while (index != field_count) {
                if (field >= fields + field_count)
                    field = fields;

                if (item[1] == field->kind &&
                    FUN_00086be4(item[0], field->identifier) == 0) {
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
            if (FUN_00086064(input, 0) != 0)
                continue;
        }

        if (FUN_00085fce(input) != 0)
            return 0;
        return -77;
    }
}
