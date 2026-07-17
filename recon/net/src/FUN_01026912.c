/* net-core FUN_01026912 @ 0x01026912, exact Thumb extent 0x28 bytes. */
#include <stdint.h>

/* Compare the complete encoded 16-bit packet positions, including epoch. */
uint8_t FUN_01026912(uint16_t first, uint16_t second)
{
    return (uint8_t)(first == second);
}
