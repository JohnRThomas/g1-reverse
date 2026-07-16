/* Full reconstruction FUN_0005c5f0 @ 0x5c5f0, exact extent 206 bytes. */
#include <stdint.h>

extern uint8_t *FUN_00059c70(void);
extern void FUN_000836ec(void *, const void *, uint32_t);
extern void *FUN_0005f594(void *, uint32_t);
extern void FUN_00082a42(uintptr_t, uint32_t, const void *);
extern void FUN_0005c4f0(void *, void *);

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

void FUN_0005c5f0(uint8_t *context, const void *data, uint32_t length)
{
    uint8_t *group = FUN_00059c70();
    struct cursor_5c5f0 cursor;
    if (group == 0)
        return;
    FUN_000836ec(&cursor, data, length);
    while (cursor.remaining > 4) {
        uint16_t *header = FUN_0005f594(&cursor, 4);
        uint16_t type = header[0], payload_length = header[1];
        if (cursor.remaining < payload_length) {
            struct { uint32_t count; uintptr_t message; uint32_t length; uint32_t total; } log =
                { 4, 0x000f4d6fu, payload_length, length };
            FUN_00082a42(0x00088128u, 0x2040, &log);
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
                    FUN_0005c4f0(context, node);
                if (next == 0) break;
                node = next;
                next = node->next;
                if (next != 0) next = (void *)((uint8_t *)next - 24);
            }
        }
        FUN_0005f594(&cursor, payload_length);
    }
}
