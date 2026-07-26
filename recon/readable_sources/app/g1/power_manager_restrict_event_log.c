#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_power_restrict_event_entry__param_0163 [param_0163; G1-original]
 * Raw function identity: 0x0004f92c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0004f92c @ 0x0004f92c
 * public-name: power_manager_restrict_event_log
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   power_manager_restrict_event_log         <= FUN_0004f92c @ 0x0004f92c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_880f0                             @ 0x000880f0
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f1885                             @ 0x000f1885   [INLINED -- G6 literal batch]
 *   rodata_f18bd                             @ 0x000f18bd   [INLINED -- G6 literal batch]
 *   rodata_f18e0                             @ 0x000f18e0   [INLINED -- G6 literal batch]
 *   rodata_f18ff                             @ 0x000f18ff   [INLINED -- G6 literal batch]
 *   rodata_f1920                             @ 0x000f1920   [INLINED -- G6 literal batch]
 *   rodata_faa2c                             @ 0x000faa2c
 */
/* Full reconstruction of FUN_0004f92c @ 0x4f92c (240 bytes). */
#include <stdint.h>
#include "../../../headers/g1_log.h"

typedef struct {
    uint32_t reserved;
    uint32_t *owner;
    uint32_t index;
    int8_t operation;
} indexed_event;

typedef struct {
    uint32_t kind;
    uintptr_t label;
    uint32_t owner_value;
    uintptr_t indexed_value;
    uintptr_t operation_name;
    uint32_t encoding;
    uint16_t encoding_size;
} dispatch_record;

extern void z_log_msg_runtime_create(uintptr_t target, uint32_t command,
                        const dispatch_record *record, uint32_t zero);
extern void assert_post_action(uintptr_t file, uint32_t line) __attribute__((noreturn));

void power_manager_restrict_event_log(const indexed_event *event)
{
    if (event->owner != (uint32_t *)0x000fa9e4u)
        __builtin_trap();

    if (event->index >= 2) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"event->module_idx < module_count()") /*=0xf18bd*/, ((unsigned long)"WEST_TOPDIR/nrf/subsys/caf/events/power_manager_event.c") /*=0xf1885*/, 0x15u);
        assert_post_action(((unsigned long)"WEST_TOPDIR/nrf/subsys/caf/events/power_manager_event.c") /*=0xf1885*/, 0x15u);
    }
    if (event->operation > 2) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"lvl <= POWER_MANAGER_LEVEL_MAX") /*=0xf18e0*/, ((unsigned long)"WEST_TOPDIR/nrf/subsys/caf/events/power_manager_event.c") /*=0xf1885*/, 0x16u);
        assert_post_action(((unsigned long)"WEST_TOPDIR/nrf/subsys/caf/events/power_manager_event.c") /*=0xf1885*/, 0x16u);
    }
    if (event->operation < -1) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"lvl >= POWER_MANAGER_LEVEL_ALIVE") /*=0xf18ff*/, ((unsigned long)"WEST_TOPDIR/nrf/subsys/caf/events/power_manager_event.c") /*=0xf1885*/, 0x17u);
        assert_post_action(((unsigned long)"WEST_TOPDIR/nrf/subsys/caf/events/power_manager_event.c") /*=0xf1885*/, 0x17u);
    }

    static const uintptr_t operation_names[3] = {
        0x000f1941u, 0x000f1854u, 0x000f18fbu
    };
    uintptr_t operation_name = (event->operation >= 0 && event->operation <= 2)
        ? operation_names[(uint8_t)event->operation] : 0x000f191au;
    const uintptr_t *values = (const uintptr_t *)((unsigned long)&rodata_faa2c) /*=0xfaa2c*/;
    dispatch_record record = {
        .kind = 0x03000005u,
        .label = ((unsigned long)"e:%s module \"%s\" restricts to %s") /*=0xf1920*/,
        .owner_value = *event->owner,
        .indexed_value = values[event->index],
        .operation_name = operation_name,
        .encoding = 0x03010200u,
        .encoding_size = 0x0402u,
    };
    z_log_msg_runtime_create(((unsigned long)&rodata_880f0) /*=0x880f0*/, 0x34c0u, &record, 0);
}
