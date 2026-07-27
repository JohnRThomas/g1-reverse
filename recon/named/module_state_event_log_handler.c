/* readable reconstruction; identity: FUN_0004f860 @ 0x0004f860
 * public-name: module_state_event_log_handler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   module_state_event_log_handler           <= FUN_0004f860 @ 0x0004f860
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_880f0                             @ 0x000880f0
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_9a1dd                             @ 0x0009a1dd
 *   rodata_f176a                             @ 0x000f176a   [INLINED -- G6 literal batch]
 *   rodata_f17a1                             @ 0x000f17a1   [INLINED -- G6 literal batch]
 *   rodata_f17c3                             @ 0x000f17c3   [INLINED -- G6 literal batch]
 *   rodata_f17eb                             @ 0x000f17eb   [INLINED -- G6 literal batch]
 *   rodata_f1823                             @ 0x000f1823   [INLINED -- G6 literal batch]
 *   rodata_fa9b4                             @ 0x000fa9b4
 */
/* Full reconstruction of FUN_0004f860 @ 0x4f860 (204 bytes). */
#include <stdint.h>
#include "../headers/g1_log.h"

typedef struct {
    uint32_t reserved;
    uint32_t *owner;
    uint32_t *value;
    uint8_t operation;
} work_event;

typedef struct {
    uint32_t kind;
    uintptr_t label;
    uint32_t owner_value;
    uint32_t data_value;
    uintptr_t operation_name;
    uint32_t encoding;
    uint16_t encoding_size;
} dispatch_record;

extern void z_log_msg_runtime_create(unsigned int, unsigned int, unsigned int, unsigned int);
extern void assert_post_action(uintptr_t file, uint32_t line) __attribute__((noreturn));

void module_state_event_log_handler(const work_event *event)
{
    if (event->owner != (uint32_t *)0x000fa9b4u)
        __builtin_trap();

    if (event->operation >= 4) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f17a1u, 0x000f176au, 0x1cu);
        assert_post_action(0x000f176au, 0x1cu);
    }

    static const uintptr_t operation_names[4] = {
        0x000f184eu, 0x000f1854u, 0x000f1858u, 0x000f1860u
    };
    uintptr_t operation_name = operation_names[event->operation];
    if (operation_name == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f17c3u, 0x000f176au, 0x1du);
        assert_post_action(0x000f176au, 0x1du);
    }
    if (event->value == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x0009a1ddu, 0x000f17ebu, 0x51u);
        assert_post_action(0x000f17ebu, 0x51u);
    }

    dispatch_record record = {
        .kind = 0x03000005u,
        .label = 0x000f1823u,
        .owner_value = *event->owner,
        .data_value = *event->value,
        .operation_name = operation_name,
        .encoding = 0x03010200u,
        .encoding_size = 0x0402u,
    };
    z_log_msg_runtime_create(0x000880f0u, 0x34c0u, &record, 0);
}
