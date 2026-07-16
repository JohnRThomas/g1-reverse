/* net-core FUN_0103b14a @ 0x103b14a */
#include <stdint.h>
#include <cmsis_gcc.h>

uint32_t FUN_0103b14a(void)
{
    return __get_IPSR() != 0U;
}
