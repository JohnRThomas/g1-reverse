#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005757c @ 0x0005757c
 * public-name: FUN_0005757c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_pool_get                         <= FUN_0005ee08 @ 0x0005ee08
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_ref                              <= FUN_0005f2d4 @ 0x0005f2d4
 *   net_buf_simple_reserve                   <= FUN_0005f4d4 @ 0x0005f4d4
 *   net_buf_simple_pull_5f558                <= FUN_0005f558 @ 0x0005f558
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   net_buf_frags_len                        <= FUN_00081616 @ 0x00081616
 *   bt_conn_create_pdu                       <= FUN_00081820 @ 0x00081820
 *   net_buf_add_le16                         <= FUN_000836f8 @ 0x000836f8
 *   net_buf_simple_headroom                  <= FUN_00083728 @ 0x00083728
 *   net_buf_simple_tailroom                  <= FUN_00083730 @ 0x00083730
 *   net_buf_push_le16                        <= FUN_00083766 @ 0x00083766
 * address symbols (name @ address):
 *   ADDR_FUN_00081a60_THUMB                  @ 0x00081a61
 *   ADDR_FUN_00081a76_THUMB                  @ 0x00081a77
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f3f55                             @ 0x000f3f55
 *   rodata_f3f86                             @ 0x000f3f86
 */
/* Full reconstruction of FUN_0005757c @ 0x5757c (owned code: 442 bytes). */
#include <stdint.h>

typedef struct packet packet_t;
struct packet {
    uint8_t reserved_00[4];
    packet_t *linked;
    uint8_t reserved_08[2];
    uint8_t kind;
    uint8_t reserved_0b;
    uint8_t cursor[4];
    uint16_t length;
    uint8_t reserved_12[2];
    uintptr_t base;
    uintptr_t context;
};

typedef struct transfer transfer_t;
typedef struct {
    uint8_t reserved_00[12];
    packet_t *(*allocate)(transfer_t *transfer);
    uint8_t reserved_10[12];
    void (*drained)(transfer_t *transfer);
} transfer_ops_t;

struct transfer {
    uintptr_t endpoint;
    transfer_ops_t *ops;
    uint8_t reserved_08[8];
    uint32_t flags;
    uint8_t reserved_14[16];
    uint16_t channel;
    uint8_t reserved_26[2];
    uint16_t capacity;
    uint8_t reserved_2a[2];
    uint32_t credits;
};

extern uint32_t FUN_000816a2(const uint32_t *value);
extern uint32_t net_buf_simple_headroom(const void *cursor);
extern uint16_t net_buf_frags_len(const packet_t *packet);
extern void net_buf_add_le16(void *cursor, uint16_t amount);
extern packet_t *net_buf_ref(packet_t *packet);
extern uint64_t net_buf_pool_get(uint8_t kind);
extern packet_t *FUN_000836de(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
extern packet_t *FUN_000569ec(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
extern void printk(uintptr_t subsystem, uintptr_t file,
                         uintptr_t message, unsigned line);
extern void assert_post_action(uintptr_t message, unsigned line);
extern void net_buf_simple_reserve(void *cursor, unsigned amount);
extern void net_buf_push_le16(void *cursor, uint16_t amount);
extern uint32_t net_buf_simple_tailroom(const void *cursor);
extern void FUN_00083740(void *cursor, uintptr_t source);
extern void net_buf_simple_pull_5f558(void *cursor, uint16_t amount);
extern int bt_conn_create_pdu(uintptr_t endpoint, uint16_t channel, packet_t *packet,
                        uintptr_t handler, uintptr_t context);
extern void net_buf_unref(packet_t *packet);

static int take_credit(uint32_t *credits)
{
    for (;;) {
        uint32_t old = FUN_000816a2(credits);
        if (old == 0)
            return 0;
        uint32_t expected = old;
        if (__atomic_compare_exchange_n(credits, &expected, old - 1, 0,
                                        __ATOMIC_RELEASE, __ATOMIC_RELAXED))
            return 1;
    }
}

static void give_credit(uint32_t *credits)
{
    (void)__atomic_fetch_add(credits, 1, __ATOMIC_ACQ_REL);
}

int FUN_0005757c(transfer_t *transfer, packet_t *source, uint32_t reserve)
{
    uint16_t original_length;
    uint32_t original_cursor;
    packet_t *packet;
    uint16_t sent_length;
    int result;

    if (!take_credit(&transfer->credits))
        return -11;

    original_cursor = net_buf_simple_headroom(source->cursor);
    original_length = source->length;

    if ((uint32_t)original_length + reserve <= transfer->capacity &&
        (uint16_t)(reserve + 9u) <= net_buf_simple_headroom(source->cursor) &&
        source->linked == 0) {
        if (reserve != 0)
            net_buf_add_le16(source->cursor, net_buf_frags_len(source));
        packet = net_buf_ref(source);
        if (packet == 0) {
            give_credit(&transfer->credits);
            return -11;
        }
    } else {
        uint64_t allocation_key = net_buf_pool_get(source->kind);
        if (transfer->ops->allocate != 0) {
            packet = transfer->ops->allocate(transfer);
            if (packet == 0) {
                printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f3f86) /*=0xf3f86*/,
                             ((unsigned long)&rodata_f3f55) /*=0xf3f55*/, 0x70du);
                assert_post_action(((unsigned long)&rodata_f3f55) /*=0xf3f55*/, 0x70du);
                return -11;
            }
        } else {
            packet = FUN_000836de((uint32_t)allocation_key,
                                  (uint32_t)(allocation_key >> 32), 0, 0);
            if (packet == 0)
                packet = FUN_000569ec(0, 4, 0, 0);
            if (packet == 0) {
                give_credit(&transfer->credits);
                return -11;
            }
        }

        net_buf_simple_reserve(packet->cursor, 9);
        if (reserve != 0)
            net_buf_push_le16(packet->cursor, net_buf_frags_len(source));

        uint32_t available = transfer->capacity - reserve;
        uint32_t room = net_buf_simple_tailroom(packet->cursor);
        uint16_t copied = room < available ? (uint16_t)room : (uint16_t)available;
        if (source->length < copied)
            copied = source->length;
        FUN_00083740(packet->cursor, source->base);
        net_buf_simple_pull_5f558(source->cursor, copied);
    }

    sent_length = packet->length;
    uintptr_t handler = (packet != source && source->length != 0)
                            ? ADDR_FUN_00081a60_THUMB /*=0x81a61*/ : ADDR_FUN_00081a76_THUMB /*=0x81a77*/;
    result = bt_conn_create_pdu(transfer->endpoint, transfer->channel, packet,
                          handler, source->context);
    if (result != 0) {
        give_credit(&transfer->credits);
        net_buf_unref(packet);
        if (result == -105) {
            source->length = original_length;
            source->base = source->base + (uint16_t)original_cursor;
            return -11;
        }
        return result;
    }

    if (FUN_000816a2(&transfer->credits) == 0) {
        (void)__atomic_fetch_and(&transfer->flags, ~1u, __ATOMIC_ACQ_REL);
        if (transfer->ops->drained != 0)
            transfer->ops->drained(transfer);
    }
    return (uint16_t)(sent_length - reserve);
}
