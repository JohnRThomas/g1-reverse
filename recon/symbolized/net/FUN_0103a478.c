#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103a478 @ 0x0103a478
 * public-name: FUN_0103a478
 * durable-map: recon/catalogs/function_names_net.json
 */
/* Zephyr net_buf_simple_push_mem @ 0x0103a478, exact extent 0x18.
 * Raw/address backmaps:
 *   FUN_0103a478@0x0103a478
 *   net_buf_simple_push = FUN_01030084@0x01030084
 *   memcpy = FUN_0103b614@0x0103b614
 */
#include <stdint.h>
#define net_buf_simple_push_mem FUN_0103a478

extern void *FUN_01030084(void *buffer, uint32_t length);
extern void *FUN_0103b614(void *destination, const void *source,
                          uint32_t length);
#define net_buf_simple_push FUN_01030084
#define memory_copy FUN_0103b614

void *net_buf_simple_push_mem(void *buffer, const void *memory,
                              uint32_t length)
{
    return memory_copy(net_buf_simple_push(buffer, length), memory, length);
}
