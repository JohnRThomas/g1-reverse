/* readable reconstruction; identity: FUN_01009f58 @ 0x01009f58
 * public-name: FUN_01009f58
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_buffer_data_get                      <= FUN_01027790 @ 0x01027790
 *   controller_record_tail_ptr               <= FUN_010277a6 @ 0x010277a6
 * address symbols (name @ address):
 *   g_net_obj_table_root_ptr                 @ 0x21000bb4
 */
/* net-core FUN_01009f58 @ 0x01009f58, exact Thumb extent 0xec bytes. */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t reason, uint32_t location);
extern uint16_t FUN_010277c2(uint16_t a, uint16_t b);
extern uint16_t FUN_010277f2(uint16_t a, uint16_t b);
extern uint16_t FUN_01027822(uint16_t a, uint16_t b);
extern void *FUN_01027302(void *pool, uint16_t key);
extern void FUN_0102776a(void *entry, uint16_t key, uint16_t second);
extern void *sdc_buffer_data_get(void *entry);
extern void FUN_0102759e(void *side, uint16_t combined, uint16_t original,
                         uint32_t kind, uint16_t limit);
extern void *controller_record_tail_ptr(void *entry);
extern void FUN_010276b2(void *side, uint16_t combined, uint16_t original,
                         uint32_t kind, uint16_t limit);
/* Back-map: FUN_01008d00 @ 0x01008d00 = sdc_assertion_fail. */

#define POOL_STATE_SLOT ((volatile uintptr_t *)0x21000bb4u)

struct controller_pool_state {
    void *pool;
    void **entries;
    uint8_t count;
};

uint32_t FUN_01009f58(uint16_t index, uint16_t first_a, uint16_t second_a,
                      uint16_t first_b, uint16_t second_b)
{
    struct controller_pool_state *state =
        (struct controller_pool_state *)(uintptr_t)*POOL_STATE_SLOT;
    if (state == 0) {
        sdc_assertion_fail(0x18u, 0xa5u);
        state = (struct controller_pool_state *)(uintptr_t)*POOL_STATE_SLOT;
    }
    if (index >= state->count || state->entries[index] != 0) {
        return 3u;
    }

    uint16_t first = FUN_010277c2(first_a, first_b);
    uint16_t second = FUN_010277f2(second_a, second_b);
    uint16_t combined = FUN_01027822(first, second);
    void *entry = FUN_01027302(state->pool, combined);
    if (entry == 0) {
        return 1u;
    }

    FUN_0102776a(entry, combined, second);
    FUN_0102759e(sdc_buffer_data_get(entry), second, second_a, 9u, second_b);
    FUN_010276b2(controller_record_tail_ptr(entry), first, first_a, 10u, first_b);
    state->entries[index] = entry;
    return 0u;
}
