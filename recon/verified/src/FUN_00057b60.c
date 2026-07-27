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
extern void FUN_00081b30(transfer_t *transfer);
extern void FUN_00057a04(int, int);
extern int FUN_00083718(int);
extern uint32_t FUN_00083730(const void *cursor);
extern void FUN_0005774c(transfer_t *transfer, uint32_t reason);

static __attribute__((always_inline)) inline void log_two(uint32_t level,
                                                          uintptr_t message)
{
    const struct { uint32_t count; uintptr_t message; } record = {2u, message};
    FUN_00081746(0x00088160u, level, &record);
}

void FUN_00057b60(transfer_t *transfer, request_t *request)
{
    for (;;) {
        uint32_t old = FUN_000816a2(&transfer->credits);
        if (old == 0) {
            log_two(0x1040u, 0x000f40e4u);
            FUN_00081b30(transfer);
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
        } record = {4u, 0x000f4080u, requested, transfer->fragment_size};
        FUN_00081746(0x00088160u, 0x2080u, &record);
        FUN_00081b30(transfer);
        return;
    }
    if (transfer->packet != 0) {
        FUN_00057a04(transfer, request);
        return;
    }
    if (requested < 2) {
        log_two(0x1080u, 0x000f4099u);
        FUN_00081b30(transfer);
        return;
    }

    uint32_t used = FUN_00083718(request->cursor);
    if (used > transfer->capacity) {
        log_two(0x1040u, 0x000f40afu);
        FUN_00081b30(transfer);
        return;
    }

    if (transfer->ops->allocate != 0) {
        transfer->packet = transfer->ops->allocate(transfer);
        if (transfer->packet == 0) {
            log_two(0x1040u, 0x000f40c2u);
            FUN_00081b30(transfer);
            return;
        }
        transfer->packet_length = (uint16_t)used;
        uint32_t available = used - request->length;
        uint32_t room = FUN_00083730((void *)(transfer->packet + 12));
        uint32_t amount = room > available ? available :
                          FUN_00083730((void *)(transfer->packet + 12));
        uint32_t fragments = (transfer->fragment_size - 1u + amount) /
                             transfer->fragment_size;
        if ((uint16_t)fragments != 0)
            FUN_0005774c(transfer, fragments);
        FUN_00057a04(transfer, request);
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
        } record = {3u, 0x000f4079u, status};
        FUN_00081746(0x00088160u, 0x1840u, &record);
        FUN_00081b30(transfer);
        return;
    }
    if (transfer->state == 3)
        FUN_0005774c(transfer, 1u);
}
