#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01021800 @ 0x01021800
 * public-name: FUN_01021800
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01021800 @ 0x01021800, exact Thumb extent 0x1c bytes. */
#include <stdint.h>

extern void *FUN_01029c22(void **queue_head);
extern void FUN_01027a94(void **list_head, void *node);
#define controller_queue_pop FUN_01029c22
#define controller_intrusive_list_prepend FUN_01027a94

/* Drain the context queue into the controller's shared free-node list. */
void FUN_01021800(uint8_t *context)
{
    void *node;
    void **const free_list =
        *(void ***)(uintptr_t)(G1N_21001670 + 0x10u);

    while ((node = controller_queue_pop((void **)(context + 0x38))) != 0) {
        controller_intrusive_list_prepend(free_list, node);
    }
}
