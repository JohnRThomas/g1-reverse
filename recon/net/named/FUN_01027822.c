/* readable reconstruction; identity: FUN_01027822 @ 0x01027822
 * public-name: FUN_01027822
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01027822 @ 0x1027822  (CFG-directed candidate) */
#include <stdint.h>
uint16_t FUN_01027822(uint16_t first_size, uint16_t second_size)
{
    volatile uint16_t saved_first = first_size;
    volatile uint16_t saved_second = second_size;
    return (uint16_t)(saved_first + saved_second + 4u);
}
