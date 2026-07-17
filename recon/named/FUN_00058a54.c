/* readable reconstruction; identity: FUN_00058a54 @ 0x00058a54
 * public-name: FUN_00058a54
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_88100                             @ 0x00088100
 *   rodata_8b29c                             @ 0x0008b29c
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f4388                             @ 0x000f4388
 *   rodata_f445b                             @ 0x000f445b
 *   rodata_f452b                             @ 0x000f452b
 *   rodata_f453e                             @ 0x000f453e
 *   rodata_f4557                             @ 0x000f4557
 *   rodata_f7a30                             @ 0x000f7a30
 */
/* Full reconstruction FUN_00058a54 @ 0x58a54, exact extent 254 bytes.
 * The following 38 bytes are its literal pool, not executable ownership. */
#include <stdint.h>

extern int FUN_00083496(uint32_t);
extern void FUN_00081ddc(uintptr_t, uint32_t, const void *);
extern void FUN_0005833c(void *);
extern void net_buf_unref(void *); /* FUN_0005f24c @ 0x0005f24c */
extern uint32_t net_buf_simple_headroom(void *); /* FUN_00083728 @ 0x00083728 */
extern uint32_t att_op_get_type(uint8_t); /* FUN_000582b8 @ 0x000582b8 */
extern int bt_conn_create_pdu(uint32_t, uint32_t, void *, uint32_t, void *); /* FUN_00081820 @ 0x00081820 */
extern void printk(uintptr_t, ...); /* FUN_0007e2fa @ 0x0007e2fa */
extern void assert_post_action(uintptr_t, uint32_t) __attribute__((noreturn)); /* FUN_0007e2ec @ 0x0007e2ec */

struct packet_58a54 {
    uint8_t pad00[12];
    uint8_t *cursor;
    uint16_t length;
    uint8_t pad12[2];
    uint32_t base;
    uint32_t *owner_slot;
};

int FUN_00058a54(uint32_t **context, struct packet_58a54 *packet)
{
    uint32_t *slot = packet->owner_slot;
    uint32_t saved_owner = *slot;
    int result;

    if ((__atomic_load_n((uint32_t *)((uint8_t *)context + 0x120),
                         __ATOMIC_ACQUIRE) & 4) == 0) {
        struct { uint32_t count; uintptr_t message; } record = { 2, 0x000f445bu };
        FUN_00081ddc(0x00088100u, 0x1040, &record);
        return -22;
    }
    if (*packet->cursor == 0xd2 &&
        (result = FUN_00083496(**context)) != 0) {
        struct { uint32_t count; uintptr_t message; } record = { 2, 0x000f452bu };
        FUN_00081ddc(0x00088100u, 0x1040, &record);
        FUN_0005833c(packet->owner_slot);
        net_buf_unref(packet);
        return result;
    }

    uint32_t consumed = net_buf_simple_headroom(&packet->cursor);
    uint16_t saved_length = packet->length;
    *slot = (uint32_t)(uintptr_t)context;
    uint32_t connection = **context;
    uint32_t opcode = att_op_get_type(*packet->cursor);
    if (opcode > 5) {
        printk(0x00099cbdu, 0x000f7a30u, 0x000f4388u, 0x28b);
        printk(0x000f453eu, opcode);
        assert_post_action(0x000f4388u, 0x28b);
    }
    result = bt_conn_create_pdu(connection, 4, packet,
                                ((const uint32_t *)0x0008b29cu)[opcode], slot);
    if (result != 0) {
        if (result == -105) {
            struct { uint32_t count; uintptr_t message; } record = { 2, 0x000f4557u };
            FUN_00081ddc(0x00088100u, 0x1040, &record);
        }
        packet->length = saved_length;
        packet->cursor = (uint8_t *)(uintptr_t)(packet->base + (uint16_t)consumed);
        *slot = saved_owner;
    }
    return result;
}
