#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103547c @ 0x0103547c
 * public-name: rpmsg_register_endpoint
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   rpmsg_register_endpoint                  <= FUN_0103547c @ 0x0103547c
 *   strncpy                                  <= FUN_0103b5a4 @ 0x0103b5a4
 * address symbols (name @ address):
 *   rodata_103cf0a                           @ 0x0103cf0a
 */
/* net-core FUN_0103547c @ 0x0103547c */
#include <stdint.h>

extern void strncpy(uint32_t, uint32_t, uint32_t);

void rpmsg_register_endpoint(uint32_t list_head, uint32_t object, uint32_t name,
                  uint32_t callback, uint32_t callback_arg,
                  uint32_t option_a, uint32_t option_b)
{
    uint32_t link;
    volatile uint32_t *fields = (volatile uint32_t *)(uintptr_t)object;

    if (name == 0u) {
        name = ((unsigned long)&rodata_103cf0a) /*=0x103cf0a*/;
    }
    strncpy(object, name, 0x20u);
    fields[9] = callback;
    fields[10] = callback_arg;
    fields[8] = list_head;
    fields[11] = option_a;
    fields[12] = option_b;

    link = object + 0x34u;
    fields[13] = list_head;
    fields[14] = *(uint32_t *)(uintptr_t)(list_head + 4u);
    *(uint32_t *)(uintptr_t)(list_head + 4u) = link;
    *(volatile uint32_t *)(uintptr_t)fields[14] = link;
}
