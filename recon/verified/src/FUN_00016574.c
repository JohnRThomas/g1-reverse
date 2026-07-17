/* Reconstructed FUN_00016574 @ 0x16574 (uncatalogued exact leaf entry). */

#include <stdint.h>

uint32_t FUN_00016574(uint32_t value)
{
    *(volatile uint32_t *)0x2007fc00UL = value;
    return value;
}
