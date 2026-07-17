#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00057b60 @ 0x00057b60
 * public-name: FUN_00057b60
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   l2cap_chan_le_recv_seg                   <= FUN_00057a04 @ 0x00057a04
 *   gatt_send_service_changed_ind            <= FUN_00081b30 @ 0x00081b30
 *   net_buf_simple_pull_le16                 <= FUN_00083718 @ 0x00083718
 *   net_buf_simple_tailroom                  <= FUN_00083730 @ 0x00083730
 * address symbols (name @ address):
 *   rodata_88160                             @ 0x00088160
 *   rodata_f4079                             @ 0x000f4079
 *   rodata_f4080                             @ 0x000f4080
 *   rodata_f4099                             @ 0x000f4099
 *   rodata_f40af                             @ 0x000f40af
 *   rodata_f40c2                             @ 0x000f40c2
 *   rodata_f40e4                             @ 0x000f40e4
 */
/* Full reconstruction of FUN_00057b60 @ 0x57b60 (exact extent: 326 bytes). */
#include <stdint.h>

typedef struct transfer transfer_t;
typedef struct {
    uint8_t reserved_00[0x10];
    uintptr_t (*allocate)(transfer_t *transfer);
    int (*submit)(transfer_t *transfer, void *request);
} transfer_ops_t;

struct transfer {
    uintptr_t endpoint;
    transfer_ops_t *ops;
    uint8_t reserved_08[0x0e];
    uint16_t capacity;               /* 0x16 */
    uint16_t fragment_size;          /* 0x18 */
    uint8_t reserved_1a[2];
    uint32_t credits;                /* 0x1c */
    uint8_t reserved_20[0x60];
    uintptr_t packet;                /* 0x80 */
    uint16_t packet_length;          /* 0x84 */
    uint8_t reserved_86[0x2e];
    uint8_t state;                   /* 0xb4 */
};

typedef struct {
    uint8_t reserved_00[0x0c];
    uint8_t cursor[4];
    uint16_t length;
} request_t;

extern uint32_t FUN_000816a2(const uint32_t *value);
extern void FUN_00081746(uintptr_t sink, uint32_t level, const void *record);
extern void gatt_send_service_changed_ind(transfer_t *transfer);
extern void l2cap_chan_le_recv_seg(transfer_t *transfer, request_t *request);
extern uint32_t net_buf_simple_pull_le16(const void *cursor);
extern uint32_t net_buf_simple_tailroom(const void *cursor);
extern void FUN_0005774c(transfer_t *transfer, uint32_t reason);

static __attribute__((always_inline)) inline void log_two(uint32_t level,
                                                          uintptr_t message)
{
    const struct { uint32_t count; uintptr_t message; } record = {2u, message};
    FUN_00081746(((unsigned long)&rodata_88160) /*=0x88160*/, level, &record);
}

void FUN_00057b60(transfer_t *transfer, request_t *request)
{
    for (;;) {
        uint32_t old = FUN_000816a2(&transfer->credits);
        if (old == 0) {
            log_two(0x1040u, ((unsigned long)&rodata_f40e4) /*=0xf40e4*/);
            gatt_send_service_changed_ind(transfer);
            return;
        }
        uint32_t expected = old;
        if (__atomic_compare_exchange_n(&transfer->credits, &expected, old - 1,
                                        0, __ATOMIC_RELEASE,
                                        __ATOMIC_RELAXED))
            break;
    }

    uint32_t requested = request->length;
    if (requested > transfer->fragment_size) {
        const struct {
            uint32_t count;
            uintptr_t message;
            uint32_t requested;
            uint32_t limit;
        } record = {4u, ((unsigned long)&rodata_f4080) /*=0xf4080*/, requested, transfer->fragment_size};
        FUN_00081746(((unsigned long)&rodata_88160) /*=0x88160*/, 0x2080u, &record);
        gatt_send_service_changed_ind(transfer);
        return;
    }
    if (transfer->packet != 0) {
        l2cap_chan_le_recv_seg(transfer, request);
        return;
    }
    if (requested < 2) {
        log_two(0x1080u, ((unsigned long)&rodata_f4099) /*=0xf4099*/);
        gatt_send_service_changed_ind(transfer);
        return;
    }

    uint32_t used = net_buf_simple_pull_le16(request->cursor);
    if (used > transfer->capacity) {
        log_two(0x1040u, ((unsigned long)&rodata_f40af) /*=0xf40af*/);
        gatt_send_service_changed_ind(transfer);
        return;
    }

    if (transfer->ops->allocate != 0) {
        transfer->packet = transfer->ops->allocate(transfer);
        if (transfer->packet == 0) {
            log_two(0x1040u, ((unsigned long)&rodata_f40c2) /*=0xf40c2*/);
            gatt_send_service_changed_ind(transfer);
            return;
        }
        transfer->packet_length = (uint16_t)used;
        uint32_t available = used - request->length;
        uint32_t room = net_buf_simple_tailroom((void *)(transfer->packet + 12));
        uint32_t amount = room > available ? available :
                          net_buf_simple_tailroom((void *)(transfer->packet + 12));
        uint32_t fragments = (transfer->fragment_size - 1u + amount) /
                             transfer->fragment_size;
        if ((uint16_t)fragments != 0)
            FUN_0005774c(transfer, fragments);
        l2cap_chan_le_recv_seg(transfer, request);
        return;
    }

    int status = transfer->ops->submit(transfer, request);
    if (status < 0) {
        if (status == -119)
            return;
        const struct {
            uint32_t count;
            uintptr_t message;
            int status;
        } record = {3u, ((unsigned long)&rodata_f4079) /*=0xf4079*/, status};
        FUN_00081746(((unsigned long)&rodata_88160) /*=0x88160*/, 0x1840u, &record);
        gatt_send_service_changed_ind(transfer);
        return;
    }
    if (transfer->state == 3)
        FUN_0005774c(transfer, 1u);
}
