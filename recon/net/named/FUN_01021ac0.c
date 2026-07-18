/* readable reconstruction; identity: FUN_01021ac0 @ 0x01021ac0
 * public-name: FUN_01021ac0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01021ac0 @ 0x1021ac0  (CFG-directed candidate) */

#include <stdint.h>
uint32_t FUN_01021ac0(uint32_t index)
{
    volatile uint8_t *state = (volatile uint8_t *)(uintptr_t)0x210016e4u;
    if (index < state[4])
        return *(volatile uint32_t *)(uintptr_t)state + index * 0x30u;
    return 0;
}
