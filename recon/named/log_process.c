/* readable reconstruction; identity: FUN_0004d594 @ 0x0004d594
 * public-name: log_process
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_dropped                              <= FUN_0004d4a8 @ 0x0004d4a8
 *   mpsc_pbuf_claim                          <= FUN_0004d56c @ 0x0004d56c
 *   mpsc_pbuf_free                           <= FUN_0004d578 @ 0x0004d578
 *   log_process                              <= FUN_0004d594 @ 0x0004d594
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_882a0                             @ 0x000882a0
 *   __settings_handler_static_list_start     @ 0x000882b0
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f0cae                             @ 0x000f0cae
 *   rodata_f0cff                             @ 0x000f0cff
 *   rodata_f0d20                             @ 0x000f0d20
 *   log_process_timestamp                    @ 0x200056a0
 *   log_backend_count                        @ 0x2000a0d4
 *   log_buffered_cnt                         @ 0x2000a0d8
 *   log_process_active                       @ 0x2001d44b
 */
/* Full ABI-faithful reconstruction of FUN_0004d594 @ 0x4d594 (220 bytes). */
#include <stdint.h>

extern uint32_t mpsc_pbuf_claim(void);
extern void mpsc_pbuf_free(uint32_t item);
extern void printk(uintptr_t, ...);
extern void assert_post_action(uintptr_t, uint32_t);
extern uint64_t thunk_FUN_00074f68(void);
extern void log_dropped(uint32_t low, uint32_t high);
extern int FUN_0004d588(void);

struct listener_entry {
    void (**vtable)(struct listener_entry *, uint32_t);
    const uint8_t *state;
    uint32_t reserved[2];
};

int log_process(void)
{
    if (*(volatile uint8_t *)0x2001d44bu == 0)
        return 0;

    uint32_t item = mpsc_pbuf_claim();
    if (item != 0) {
        __atomic_sub_fetch((uint32_t *)0x2000a0d8u, 1, __ATOMIC_ACQ_REL);

        struct listener_entry *entry = (struct listener_entry *)0x000882a0u;
        struct listener_entry *end = (struct listener_entry *)0x000882b0u;
        while (entry < end) {
            if (end < entry) {
                printk(0x00099cbdu, 0x000f0cffu,
                             0x000f0caeu, 0x1c5u);
                printk(0x000f0d20u);
                assert_post_action(0x000f0caeu, 0x1c5u);
            }
            if (entry->state[5] != 0)
                (*entry->vtable)(entry, item);
            ++entry;
        }
        mpsc_pbuf_free(item);
    }

    volatile uint64_t *deadline = (volatile uint64_t *)0x200056a0u;
    if (*(volatile int32_t *)0x2000a0d4u > 0) {
        uint64_t now = (thunk_FUN_00074f68() * UINT64_C(1000)) >> 15;
        uint64_t elapsed = now - *deadline;
        if (elapsed >= UINT64_C(1001))
            log_dropped((uint32_t)elapsed, (uint32_t)(elapsed >> 32));
    }
    *deadline += UINT64_C(1000);

    return FUN_0004d588();
}
