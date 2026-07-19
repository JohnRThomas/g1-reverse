/* readable reconstruction; identity: FUN_00084ed8 @ 0x00084ed8
 * public-name: cjson_skip_whitespace
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_skip_whitespace                    <= FUN_00084ed8 @ 0x00084ed8
 */
/* Full reconstruction FUN_00084ed8 @ 0x84ed8 (46-byte extent). */
#include <stdint.h>

struct text_cursor {
    uint8_t *data;
    uint32_t length;
    uint32_t position;
};

struct text_cursor *cjson_skip_whitespace(struct text_cursor *cursor)
{
    if (cursor == 0 || cursor->data == 0)
        return cursor == 0 ? 0 : (struct text_cursor *)0;

    if (cursor->position < cursor->length) {
        while (cursor->position < cursor->length) {
            if (cursor->data[cursor->position] > 0x20)
                return cursor;
            cursor->position++;
        }
        if (cursor->position == cursor->length)
            cursor->position--;
    }
    return cursor;
}
