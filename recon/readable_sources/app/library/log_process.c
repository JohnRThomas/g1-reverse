#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   0x0004d590       => struct g1_layout_log_process_state__global_1068         [global_1068; library]
 * Raw function identity: 0x0004d594.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0004d594 @ 0x0004d594
 * public-name: log_process
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_dropped                              <= FUN_0004d4a8 @ 0x0004d4a8
 *   z_log_msg_local_claim                    <= FUN_0004d56c @ 0x0004d56c
 *   log_process                              <= FUN_0004d594 @ 0x0004d594
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_882a0                             @ 0x000882a0
 *   __settings_handler_static_list_start     @ 0x000882b0
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0cae                             @ 0x000f0cae
 *   rodata_f0cff                             @ 0x000f0cff   [INLINED -- G6 literal batch]
 *   rodata_f0d20                             @ 0x000f0d20   [INLINED -- G6 literal batch]
 *   log_process_timestamp                    @ 0x200056a0
 *   log_backend_count                        @ 0x2000a0d4
 *   log_buffered_cnt                         @ 0x2000a0d8
 *   log_process_active                       @ 0x2001d44b
 */
/* Full ABI-faithful reconstruction of FUN_0004d594 @ 0x4d594 (220 bytes). */
#include <stdint.h>

extern uint32_t z_log_msg_local_claim(void);
extern void g1_recon_z_log_msg_free(uint32_t item);
extern void printk(uintptr_t, ...);
extern void assert_post_action(uintptr_t, uint32_t);
extern uint64_t thunk_FUN_00074f68(void);
extern void log_dropped(uint32_t low, uint32_t high);
extern int g1_recon_z_log_msg_pending(void);

struct listener_entry {
    void (**vtable)(struct listener_entry *, uint32_t);
    const uint8_t *state;
    uint32_t reserved[2];
};

int log_process(void)
{
    if (*(volatile uint8_t *)((unsigned long)&log_process_active) /*=0x2001d44b*/ == 0)
        return 0;

    uint32_t item = z_log_msg_local_claim();
    if (item != 0) {
        __atomic_sub_fetch((uint32_t *)((unsigned long)&log_buffered_cnt) /*=0x2000a0d8*/, 1, __ATOMIC_ACQ_REL);

        struct listener_entry *entry = (struct listener_entry *)((unsigned long)&rodata_882a0) /*=0x882a0*/;
        struct listener_entry *end = (struct listener_entry *)((unsigned long)&__settings_handler_static_list_start) /*=0x882b0*/;
        while (entry < end) {
            if (end < entry) {
                printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"backend <= _log_backend_list_end") /*=0xf0cff*/,
                             ((unsigned long)&rodata_f0cae) /*=0xf0cae*/, 0x1c5u);
                printk(((unsigned long)"\tunexpected list end location\n") /*=0xf0d20*/);
                assert_post_action(((unsigned long)&rodata_f0cae) /*=0xf0cae*/, 0x1c5u);
            }
            if (entry->state[5] != 0)
                (*entry->vtable)(entry, item);
            ++entry;
        }
        g1_recon_z_log_msg_free(item);
    }

    volatile uint64_t *deadline = (volatile uint64_t *)((unsigned long)&log_process_timestamp) /*=0x200056a0*/;
    if (*(volatile int32_t *)((unsigned long)&log_backend_count) /*=0x2000a0d4*/ > 0) {
        uint64_t now = (thunk_FUN_00074f68() * UINT64_C(1000)) >> 15;
        uint64_t elapsed = now - *deadline;
        if (elapsed >= UINT64_C(1001))
            log_dropped((uint32_t)elapsed, (uint32_t)(elapsed >> 32));
    }
    *deadline += UINT64_C(1000);

    return g1_recon_z_log_msg_pending();
}
