/* net-core FUN_01039768 @ 0x1039768 */
#include <stdint.h>

extern uint32_t FUN_0103973c(void *arena, uint32_t offset, uint32_t mode);

uint32_t FUN_01039768(void *arena, uint32_t offset)
{
    return FUN_0103973c(arena, offset, 1) >> 1;
}
