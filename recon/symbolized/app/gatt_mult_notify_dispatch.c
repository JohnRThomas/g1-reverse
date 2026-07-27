#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005c5f0 @ 0x0005c5f0
 * public-name: gatt_mult_notify_dispatch
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_find_conn_in_known_table            <= FUN_00059c70 @ 0x00059c70
 *   bt_gatt_unsubscribe                      <= FUN_0005c4f0 @ 0x0005c4f0
 *   gatt_mult_notify_dispatch                <= FUN_0005c5f0 @ 0x0005c5f0
 *   net_buf_simple_pull_5f594                <= FUN_0005f594 @ 0x0005f594
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 *   net_buf_simple_init_with_data            <= FUN_000836ec @ 0x000836ec
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f4d6f                             @ 0x000f4d6f   [INLINED -- G6 literal batch]
 */
/* Full reconstruction FUN_0005c5f0 @ 0x5c5f0, exact extent 206 bytes. */
#include <stdint.h>

extern uint8_t * gatt_find_conn_in_known_table(unsigned long);
extern void net_buf_simple_init_with_data(void *, const void *, uint32_t);
extern void *net_buf_simple_pull_5f594(void *, uint32_t);
extern void log_msg_create_3arg(uintptr_t, uint32_t, const void *);
extern void bt_gatt_unsubscribe(void *, void *);

struct cursor_5c5f0 { uint8_t opaque[4]; uint16_t remaining; };
struct handler_5c5f0 {
    int (*invoke)(void *, struct handler_5c5f0 *, const void *, uint32_t);
    uint8_t pad04[8];
    uint16_t type;
    uint8_t pad0e[4];
    uint8_t minimum;
    uint8_t pad13[5];
    struct handler_5c5f0 *next;
};

void gatt_mult_notify_dispatch(uint8_t *context, const void *data, uint32_t length)
{
    uint8_t *group = gatt_find_conn_in_known_table(context);
    struct cursor_5c5f0 cursor;
    if (group == 0)
        return;
    net_buf_simple_init_with_data(&cursor, data, length);
    while (cursor.remaining > 4) {
        uint16_t *header = net_buf_simple_pull_5f594(&cursor, 4);
        uint16_t type = header[0], payload_length = header[1];
        if (cursor.remaining < payload_length) {
            struct { uint32_t count; uintptr_t message; uint32_t length; uint32_t total; } log =
                { 4, ((unsigned long)"Invalid data len %u > %u") /*=0xf4d6f*/, payload_length, length };
            log_msg_create_3arg(((unsigned long)&rodata_88128) /*=0x88128*/, 0x2040, &log);
            return;
        }
        struct handler_5c5f0 *node = *(struct handler_5c5f0 **)(group + 8);
        if (node != 0) {
            struct handler_5c5f0 *next = node->next;
            if (next != 0) next = (void *)((uint8_t *)next - 24);
            node = (void *)((uint8_t *)node - 24);
            for (;;) {
                if (node->type == type && node->minimum <= context[9] &&
                    node->invoke(context, node, header + 2, payload_length) == 0)
                    bt_gatt_unsubscribe(context, node);
                if (next == 0) break;
                node = next;
                next = node->next;
                if (next != 0) next = (void *)((uint8_t *)next - 24);
            }
        }
        net_buf_simple_pull_5f594(&cursor, payload_length);
    }
}
