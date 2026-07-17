/* readable reconstruction; identity: FUN_0005774c @ 0x0005774c
 * public-name: FUN_0005774c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   att_send_simple                          <= FUN_00081940 @ 0x00081940
 *   thunk_FUN_000727ac                       <= FUN_000836e8 @ 0x000836e8
 * address symbols (name @ address):
 *   rodata_88160                             @ 0x00088160
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f3f55                             @ 0x000f3f55
 *   rodata_f3f8a                             @ 0x000f3f8a
 *   rodata_f3fc5                             @ 0x000f3fc5
 *   rodata_f3fe3                             @ 0x000f3fe3
 */
/* Full reconstruction of FUN_0005774c @ 0x5774c (exact extent: 270 bytes). */
#include <stdint.h>

typedef struct transfer transfer_t;
typedef struct {
    uint8_t reserved_00[0x1c];
    void (*stopped)(transfer_t *transfer, uint32_t *flags);
} transfer_ops_t;

struct transfer {
    uintptr_t endpoint;              /* 0x00 */
    transfer_ops_t *ops;             /* 0x04 */
    uint8_t reserved_08[8];
    uint32_t flags;                  /* 0x10 */
    uint16_t channel;                /* 0x14 */
    uint8_t reserved_16[6];
    uint32_t pending_owner;          /* 0x1c */
    uint8_t reserved_20[0x10];
    uint8_t pending_a[0x1c];         /* 0x30 */
    uint32_t packet_a;               /* 0x4c */
    uint8_t reserved_50[0x30];
    uint32_t packet_b;               /* 0x80 */
    uint16_t packet_b_length;        /* 0x84 */
    uint8_t reserved_86[0x12];
    uint8_t pending_b[0x1c];         /* 0x98 */
    uint8_t state;                   /* 0xb4 */
};

typedef struct {
    uint16_t channel;
    uint16_t reason;
} stop_record_t;

extern uintptr_t FUN_00057394(void);
extern int FUN_000573f4(uint32_t type, uintptr_t object, uint32_t count);
extern void FUN_00081746(uintptr_t sink, uint32_t level, const void *record);
extern void net_buf_unref(uintptr_t packet);
extern uintptr_t thunk_FUN_000727ac(void *queue, uint32_t wait, uint32_t unused);
extern uint32_t FUN_000816a2(const uint32_t *value);
extern stop_record_t *net_buf_simple_add(uintptr_t pool, uint32_t size);
extern void att_send_simple(uintptr_t endpoint, int status);
extern void printk(uintptr_t subsystem, uintptr_t file,
                         uintptr_t message, uint32_t line);
extern void assert_post_action(uintptr_t message, uint32_t line);

static __attribute__((always_inline)) inline void fatal_state(uintptr_t file,
                                                              uint32_t line)
{
    printk(0x00099cbdu, file, 0x000f3f55u, line);
    assert_post_action(0x000f3f55u, line);
}

void FUN_0005774c(transfer_t *transfer, uint32_t reason)
{
    if (transfer->state != 3) {
        fatal_state(0x000f3f8au, 0x8f8u);
        return;
    }

    int status = FUN_000573f4(0x16u, FUN_00057394(), 4u);
    if (status != 0) {
        uint32_t old_owner = FUN_000816a2(&transfer->pending_owner);
        if (old_owner != 0) {
            fatal_state(0x000f3fe3u, 0x905u);
            return;
        }
        (void)__atomic_exchange_n(&transfer->pending_owner, reason,
                                  __ATOMIC_ACQ_REL);
        stop_record_t *record = net_buf_simple_add((uintptr_t)(status + 12), 4u);
        record->channel = transfer->channel;
        record->reason = (uint16_t)reason;
        att_send_simple(transfer->endpoint, status);
        return;
    }

    const struct {
        uint32_t count;
        uintptr_t message;
    } notice = { 2u, 0x000f3fc5u };
    FUN_00081746(0x00088160u, 0x1040u, &notice);
    (void)__atomic_fetch_or(&transfer->flags, 2u, __ATOMIC_ACQ_REL);

    if (transfer->packet_b != 0) {
        net_buf_unref(transfer->packet_b);
        transfer->packet_b = 0;
        transfer->packet_b_length = 0;
    }
    if (transfer->packet_a != 0) {
        net_buf_unref(transfer->packet_a);
        transfer->packet_a = 0;
    }
    uintptr_t packet;
    while ((packet = thunk_FUN_000727ac(transfer->pending_a, 0, 0)) != 0)
        net_buf_unref(packet);
    while ((packet = thunk_FUN_000727ac(transfer->pending_b, 0, 0)) != 0)
        net_buf_unref(packet);

    if (transfer->ops->stopped != 0)
        transfer->ops->stopped(transfer, &transfer->flags);
}
