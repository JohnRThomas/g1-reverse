#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100d808 @ 0x0100d808
 * public-name: controller_boot_defaults_load
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_boot_defaults_load            <= FUN_0100d808 @ 0x0100d808
 * address symbols (name @ address):
 *   rodata_103cc60                           @ 0x0103cc60
 *   g_net_esb_own_addr                       @ 0x21000010
 *   g_net_esb_own_addr_valid                 @ 0x21000ea8
 */
/* net-core controller_boot_defaults_load @ 0x0100d808, exact extent 0x2c.
 * Raw/address backmaps:
 *   FUN_0100d808@0x0100d808
 *   boot_defaults@0x0103cc60
 *   controller_defaults@0x21000010
 *   reset_latch@0x21000ea8
 */
#include <stdint.h>
#define controller_boot_defaults_load controller_boot_defaults_load

void controller_boot_defaults_load(void)
{
    volatile const uint8_t *boot_defaults =
        (volatile const uint8_t *)((unsigned long)&rodata_103cc60) /*=0x103cc60*/;
    volatile uint8_t *controller_defaults =
        (volatile uint8_t *)((unsigned long)&g_net_esb_own_addr) /*=0x21000010*/;
    volatile uint8_t *reset_latch = (volatile uint8_t *)((unsigned long)&g_net_esb_own_addr_valid) /*=0x21000ea8*/;

    *(volatile uint32_t *)controller_defaults =
        *(volatile const uint32_t *)boot_defaults;
    controller_defaults[4] = boot_defaults[4];
    *reset_latch = 0xffu;
    *reset_latch = 0u;
}
