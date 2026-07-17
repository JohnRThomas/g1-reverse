/* readable reconstruction; identity: FUN_0100a960 @ 0x0100a960
 * public-name: controller_tx_buffer_ready_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_tx_buffer_ready_get           <= FUN_0100a960 @ 0x0100a960
 */
/* net-core FUN_0100a960 @ 0x100a960  (CFG-directed candidate) */

#include <stdint.h>
uint32_t controller_tx_buffer_ready_get(void **result)
{
    volatile uint8_t *state = (volatile uint8_t *)0x21000bf8u;
    if (*(volatile uint16_t *)(state + 0x34u) != *(volatile uint16_t *)(state + 0x38u)) return 0u;
    if (state[0x32u] == 0u) return 0u;
    *result = (void *)state;
    return 1u;
}
