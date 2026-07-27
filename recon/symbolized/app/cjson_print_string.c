#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000644f8 @ 0x000644f8
 * public-name: cjson_print_string
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_print_string                       <= FUN_000644f8 @ 0x000644f8
 *   snprintf                                 <= FUN_00077914 @ 0x00077914
 *   growbuf_ensure_capacity                  <= FUN_00084f58 @ 0x00084f58
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   strncpy_zero_pad                         <= FUN_0008705a @ 0x0008705a
 * address symbols (name @ address):
 *   rodata_f696e                             @ 0x000f696e
 */
/* Full reconstruction FUN_000644f8 @ 0x644f8, exact 310-byte extent. */
#include <stddef.h>
#include <stdint.h>

struct output_buffer {
    uint8_t *begin;
    uint8_t *end;
    uint8_t *limit;
};

extern uint8_t *growbuf_ensure_capacity(struct output_buffer *, uint32_t);
extern void *memcpy(void *, const void *, size_t);
extern void strncpy_zero_pad(uint8_t *, const void *, size_t);
extern void snprintf(uint8_t *, size_t, uintptr_t);

int cjson_print_string(const uint8_t *text, struct output_buffer *out,
                 uint32_t unused)
{
    const uint8_t descriptor[3] = { 0x74, 0x69, 0x0f };
    (void)unused;

    if (out == NULL)
        return 0;

    if (text == NULL) {
        uint8_t *slot = growbuf_ensure_capacity(out, 3);
        if (slot == NULL)
            return 0;
        strncpy_zero_pad(slot, descriptor, (size_t)(out->end - out->limit));
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
    uint8_t *slot = growbuf_ensure_capacity(out, encoded_length + 3);
    if (slot == NULL)
        return 0;

    slot[0] = '"';
    uint8_t *dst = slot + 1;
    if (extra == 0) {
        memcpy(dst, text, encoded_length);
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
                snprintf(dst, (size_t)(out->end - (dst - out->begin)),
                             ((unsigned long)&rodata_f696e) /*=0xf696e*/);
                dst += 5;
                break;
            }
        }
    }
    *dst++ = '"';
    *dst = 0;
    return 1;
}
