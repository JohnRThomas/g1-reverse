/* Full reconstruction FUN_000644f8 @ 0x644f8, exact 310-byte extent. */
#include <stddef.h>
#include <stdint.h>

struct output_buffer {
    uint8_t *begin;
    uint8_t *end;
    uint8_t *limit;
};

extern uint8_t *FUN_00084f58(struct output_buffer *, uint32_t);
extern void FUN_00086c04(void *, const void *, size_t);
extern void FUN_0008705a(uint8_t *, const void *, size_t);
extern void FUN_00077914(uint8_t *, size_t, uintptr_t);

int FUN_000644f8(const uint8_t *text, struct output_buffer *out,
                 uint32_t unused)
{
    const uint8_t descriptor[3] = { 0x74, 0x69, 0x0f };
    (void)unused;

    if (out == NULL)
        return 0;

    if (text == NULL) {
        uint8_t *slot = FUN_00084f58(out, 3);
        if (slot == NULL)
            return 0;
        FUN_0008705a(slot, descriptor, (size_t)(out->end - out->limit));
        return 1;
    }

    size_t length = 0;
    size_t extra = 0;
    for (const uint8_t *p = text; *p != 0; ++p, ++length) {
        uint8_t c = *p;
        if (c < 8)
            extra += 5;
        else if (c <= 34) {
            if (((0x04000037u >> (uint8_t)(c - 8)) & 1u) != 0)
                extra += 1;
            else if (c <= 31)
                extra += 5;
        } else if (c == '\\') {
            extra += 1;
        }
    }

    size_t encoded_length = length + extra;
    uint8_t *slot = FUN_00084f58(out, encoded_length + 3);
    if (slot == NULL)
        return 0;

    slot[0] = '"';
    uint8_t *dst = slot + 1;
    if (extra == 0) {
        FUN_00086c04(dst, text, encoded_length);
        dst += encoded_length;
    } else {
        for (const uint8_t *p = text; *p != 0; ++p) {
            uint8_t c = *p;
            if (c >= 0x20 && c != '"' && c != '\\') {
                *dst++ = c;
                continue;
            }

            *dst++ = '\\';
            switch (c) {
            case '\b': *dst++ = 'b'; break;
            case '\t': *dst++ = 't'; break;
            case '\n': *dst++ = 'n'; break;
            case '\f': *dst++ = 'f'; break;
            case '\r': *dst++ = 'r'; break;
            case '"':
            case '\\': *dst++ = c; break;
            default:
                FUN_00077914(dst, (size_t)(out->end - (dst - out->begin)),
                             0x000f696eu);
                dst += 5;
                break;
            }
        }
    }
    *dst++ = '"';
    *dst = 0;
    return 1;
}
