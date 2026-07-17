/* Reconstructed k_uptime_get_1 @ 0x7cb2c  (CFG-directed candidate) */
#include <stdint.h>
extern uint64_t thunk_FUN_00074f68(void);
uint64_t k_uptime_get_1(void) {
    return (thunk_FUN_00074f68() * UINT64_C(1000)) >> 15;
}
