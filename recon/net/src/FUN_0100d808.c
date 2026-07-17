/* net-core controller_boot_defaults_load @ 0x0100d808, exact extent 0x2c.
 * Raw/address backmaps:
 *   FUN_0100d808@0x0100d808
 *   boot_defaults@0x0103cc60
 *   controller_defaults@0x21000010
 *   reset_latch@0x21000ea8
 */
#include <stdint.h>
#define controller_boot_defaults_load FUN_0100d808

void controller_boot_defaults_load(void)
{
    volatile const uint8_t *boot_defaults =
        (volatile const uint8_t *)0x0103cc60u;
    volatile uint8_t *controller_defaults =
        (volatile uint8_t *)0x21000010u;
    volatile uint8_t *reset_latch = (volatile uint8_t *)0x21000ea8u;

    *(volatile uint32_t *)controller_defaults =
        *(volatile const uint32_t *)boot_defaults;
    controller_defaults[4] = boot_defaults[4];
    *reset_latch = 0xffu;
    *reset_latch = 0u;
}
