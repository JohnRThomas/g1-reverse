/* Reconstructed FUN_00065324 @ 0x65324  (parity: 300/300 trials, PROVEN)
 * Readable namespace target: g1_nrfx_clock_stop_checked.
 */
#include <stdint.h>
extern __attribute__((noreturn)) void FUN_0007e2ec(uint32_t,uint32_t);
extern void FUN_0007e2fa(uint32_t,uint32_t,uint32_t,uint32_t);
extern void FUN_00065000(int domain);

void FUN_00065324(int domain)
{
    if (*(volatile uint8_t*)0x2000b320 == 0) {
        FUN_0007e2fa(0x00099cbd, 0x000f6acd, 0x000f6a4e, 0x1ad);
        FUN_0007e2ec(0x000f6a4e, 0x1ad);
    }
    FUN_00065000(domain);
}
