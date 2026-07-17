#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000571e8 @ 0x000571e8
 * public-name: FUN_000571e8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_destroy                          <= FUN_00056080 @ 0x00056080
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_ref                              <= FUN_0005f2d4 @ 0x0005f2d4
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   atomic_and_2                             <= FUN_000813b4 @ 0x000813b4
 *   k_fifo_peek_head_impl                    <= FUN_0008652c @ 0x0008652c
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f3a5d                             @ 0x000f3a5d
 *   rodata_f45be                             @ 0x000f45be
 *   g_bt_dev_hci_buf_ready                   @ 0x20002104
 */
/* Full reconstruction of FUN_000571e8 @ 0x571e8 (owned code: 258 bytes). */
#include <stdint.h>

typedef struct {
    uint8_t reserved_00[0x0d];
    uint8_t state;
    uint8_t reserved_0e[0x2a];
    uint8_t queue[1];
} stream_owner_t;

typedef struct {
    uint8_t reserved_00[0x10];
    uint16_t length;
    uint8_t reserved_12[6];
    void *pending;
    uint8_t split;
    uint8_t tag;
} stream_fragment_t;

extern int atomic_and_2(const void *object, int selector);
extern void FUN_00056300(stream_owner_t *owner);
extern void *k_fifo_peek_head_impl(void *queue);
extern void printk(uintptr_t subsystem, uintptr_t file,
                         uintptr_t message, unsigned line);
extern stream_fragment_t *net_buf_ref(void *object);
extern stream_fragment_t *FUN_000571dc(unsigned kind, int a, int b, int c);
extern int FUN_000560cc(stream_owner_t *owner, stream_fragment_t *source,
                        stream_fragment_t *destination, unsigned mode);
extern void net_buf_unref(void *object);
extern void net_buf_destroy(stream_owner_t *owner, void *pending);

void FUN_000571e8(stream_owner_t *owner)
{
    stream_fragment_t *fragment;
    int result;
    uint8_t split;

    if (owner->state == 0 &&
        ((uint32_t)atomic_and_2((uint8_t *)owner + 4, -65) & 0x40u) != 0) {
        FUN_00056300(owner);
        return;
    }

    void *queued = k_fifo_peek_head_impl(owner->queue);
    if (queued == 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f45be) /*=0xf45be*/, ((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/, 0x397u);
        /* The following BASEPRI/SVC fatal path does not return in firmware. */
        return;
    }

    fragment = net_buf_ref(queued);
    split = fragment->split;

    if (fragment->length <= *(volatile uint16_t *)((unsigned long)&g_bt_dev_hci_buf_ready) /*=0x20002104*/ && split == 0) {
        result = FUN_000560cc(owner, fragment, 0, 2);
    } else {
        for (;;) {
            if (fragment->length <= *(volatile uint16_t *)((unsigned long)&g_bt_dev_hci_buf_ready) /*=0x20002104*/) {
                fragment->split = 1;
                result = FUN_000560cc(owner, fragment, 0, 3);
                break;
            }

            stream_fragment_t *part = FUN_000571dc(0, -1, -1, -1);
            if (owner->state != 7) {
                net_buf_unref(part);
                net_buf_unref(fragment);
                return;
            }

            part->pending = 0;
            part->split = 0;
            part->tag = fragment->tag;
            result = FUN_000560cc(owner, fragment, part, split);
            if (result != 0) {
                fragment->split = split & 1u;
                net_buf_unref(part);
                break;
            }
            split = 1;
        }
    }

    net_buf_unref(fragment);
    if (result == -5) {
        void *pending = fragment->pending;
        fragment->pending = 0;
        net_buf_unref(fragment);
        if (pending != 0)
            net_buf_destroy(owner, pending);
    }
}
