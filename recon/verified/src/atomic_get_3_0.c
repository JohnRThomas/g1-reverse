/* Reconstructed atomic_get_3_0 @ 0x431a8  (CFG-directed candidate) */
#include <stdint.h>
uint32_t atomic_get_3_0(void)
{
    return __atomic_load_n((volatile uint32_t *)(uintptr_t)0x2000a030u, __ATOMIC_SEQ_CST);
}
