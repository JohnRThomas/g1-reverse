#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01027a94 @ 0x01027a94
 * public-name: FUN_01027a94
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01027a94 @ 0x1027a94  (CFG-directed candidate) */
/* CPUNET 0x01027a94, true executable extent 0x3e. Raw backmap: FUN_01027a94. */
#include <stdint.h>
#include <cmsis_gcc.h>

void FUN_01027a94(void **head, void **node)
{
    uint32_t key = __get_PRIMASK();
    __disable_irq();
    *node = *head;
    *head = node;
    if (key == 0u) {
        __enable_irq();
    }
}
