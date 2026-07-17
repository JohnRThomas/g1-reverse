/* readable reconstruction; identity: FUN_01010834 @ 0x01010834
 * public-name: FUN_01010834
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_lookup_table_desc                  @ 0x21000f14
 */
/* net-core FUN_01010834 @ 0x1010834 */
#include <stdint.h>

extern int32_t FUN_010106dc(uint32_t, uint32_t, uint8_t *);
extern void FUN_0102590c(void *, void *, uint32_t);

int32_t FUN_01010834(int32_t add_flag, const uint32_t *request)
{
    volatile uint8_t removed_index;
    volatile uint8_t *const queue_count = (volatile uint8_t *)0x21000f14;
    uint32_t flags = ((const uint8_t *)request)[4] |
                     ((uint32_t)((const uint8_t *)request)[5] << 8);
    int32_t result;

    if (add_flag == 1)
        flags |= 0x10000;
    result = FUN_010106dc(request[0], flags, (uint8_t *)&removed_index);
    if (result != 0) {
        uint8_t old_count = *queue_count;
        uint8_t new_count = (uint8_t)(old_count - 1);
        uint8_t index = removed_index;
        *queue_count = new_count;
        if (index < new_count) {
            uint8_t *base = *(uint8_t * volatile *)(queue_count + 4);
            uint32_t bytes = ((uint8_t)(old_count - 2 - index) + 1u) * 8u;
            FUN_0102590c(base + index * 8u, base + (index + 1u) * 8u, bytes);
        }
    }
    return result;
}
