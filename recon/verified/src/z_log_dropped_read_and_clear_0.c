/* z_log_dropped_read_and_clear_0 @ 0x0004d490; raw FUN_0004d490 */
#include <stdint.h>

uint32_t z_log_dropped_read_and_clear_0(void)
{
    return __atomic_exchange_n((uint32_t *)0x2000a0d4u, 0,
                               __ATOMIC_SEQ_CST);
}
