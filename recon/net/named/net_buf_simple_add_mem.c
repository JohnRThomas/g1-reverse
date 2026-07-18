/* readable reconstruction; identity: FUN_0103a478 @ 0x0103a478
 * public-name: net_buf_simple_add_mem
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   net_buf_simple_add                       <= FUN_01030084 @ 0x01030084
 *   net_buf_simple_add_mem                   <= FUN_0103a478 @ 0x0103a478
 */
/* Zephyr net_buf_simple_push_mem @ 0x0103a478, exact extent 0x18.
 * Raw/address backmaps:
 *   FUN_0103a478@0x0103a478
 *   net_buf_simple_push = FUN_01030084@0x01030084
 *   memcpy = FUN_0103b614@0x0103b614
 */
#include <stdint.h>
#define net_buf_simple_push_mem net_buf_simple_add_mem

extern void *net_buf_simple_add(void *buffer, uint32_t length);
extern void *FUN_0103b614(void *destination, const void *source,
                          uint32_t length);
#define net_buf_simple_push net_buf_simple_add
#define memory_copy FUN_0103b614

void *net_buf_simple_push_mem(void *buffer, const void *memory,
                              uint32_t length)
{
    return memory_copy(net_buf_simple_push(buffer, length), memory, length);
}
