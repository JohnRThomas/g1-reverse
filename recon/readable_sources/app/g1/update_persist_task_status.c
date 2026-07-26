#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_g1_device_runtime_state__param_0027    [param_0027; G1-original]
 * Raw function identity: 0x0002bef4.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0002bef4 @ 0x0002bef4
 * public-name: update_persist_task_status
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_a2597                             @ 0x000a2597
 *   rodata_a25b9                             @ 0x000a25b9
 *   rodata_a25d9                             @ 0x000a25d9
 *   rodata_a2660                             @ 0x000a2660   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_persist_task_status_lock               @ 0x20018d9c
 *   g_persist_task_status                    @ 0x20018d9d
 */
/* Reconstructed update_persist_task_status @ 0x2bef4.
 * Raw identity/back-map: FUN_0002bef4 @ 0x0002bef4.
 * Executable extent: 0xe4 bytes; literals begin at 0x0002bfd8. */
typedef unsigned char u8;
typedef unsigned int  u32;

extern void log_message(u32 format, u32 source, u32 task_id); /* FUN_0007dda4 */
extern void debug_print(u32 format, u32 source, u32 task_id); /* FUN_00019c70 */
extern void display_close_screen(u32 screen_id);              /* FUN_00049858 */
extern void wait_for_persist_task_status_lock(void);          /* FUN_0007cdf8 */

struct persist_task_record {
    u32 task_id;
    u8 status;
};

#define g_persist_task_status_lock (*(volatile u8 *)((unsigned long)&g_persist_task_status_lock) /*=0x20018d9c*/)
#define g_persist_task_status      (*(volatile u8 *)((unsigned long)&g_persist_task_status) /*=0x20018d9d*/)
#define g_log_level                (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define g_log_use_alt_sink         (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)

enum {
    TASK_STATUS_ACTIVE = 1,
    TASK_STATUS_ASSIGNED = 2,
    TASK_STATUS_COMPLETE = 3,
};

static inline __attribute__((always_inline))
void log_task_status(u32 format, u32 task_id)
{
    if (g_log_level > 0) {
        if (g_log_use_alt_sink == 0) {
            log_message(format, ((unsigned long)"update_persist_task_status") /*=0xa2660*/, task_id);
        } else {
            debug_print(format, ((unsigned long)"update_persist_task_status") /*=0xa2660*/, task_id);
        }
    }
}

u32 update_persist_task_status(u8 *context, u32 task_id, u32 requested_status)
{
    struct persist_task_record *record;
    u8 active_task;

    while (g_persist_task_status_lock != 0) {
        wait_for_persist_task_status_lock();
    }
    g_persist_task_status_lock = 1;

    record = *(struct persist_task_record **)(context + 0x1054);
    if (record->task_id == task_id &&
        (record->status == TASK_STATUS_ACTIVE ||
         record->status == requested_status)) {
        goto unlock;
    }

    active_task = context[0xd5];
    if (active_task > 1) {
        display_close_screen(active_task);
        if (requested_status == TASK_STATUS_ASSIGNED &&
            (task_id > 0x10 || (0x00010050u & (1u << task_id)) == 0)) {
            goto unlock;
        }
    }

    if (requested_status == TASK_STATUS_ASSIGNED) {
        log_task_status(((unsigned long)&rodata_a2597) /*=0xa2597*/, task_id);
        if (task_id == 0x10) {
            g_persist_task_status = context[0xf98];
            if (context[0xf98] == 1) {
                context[0xf98] = 0;
            }
        }
    } else {
        log_task_status(requested_status == TASK_STATUS_COMPLETE ?
                        ((unsigned long)&rodata_a25b9) /*=0xa25b9*/ : ((unsigned long)&rodata_a25d9) /*=0xa25d9*/,
                        task_id);
    }

    context[0xd5] = (u8)task_id;
    record->task_id = task_id;
    record->status = (u8)requested_status;

unlock:
    g_persist_task_status_lock = 0;
    return requested_status;
}
