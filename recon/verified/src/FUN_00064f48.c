/* Reconstructed g1_recon_nrfx_gppi_event_endpoint_setup @ 0x64f48.
 * Raw identity/back-map: FUN_00064f48.
 */
#include <stdint.h>

extern void FUN_0007e2fa(unsigned long, ...);
/* The real routine is noreturn.  The return type models unreachable r0 only. */
extern uint32_t FUN_0007e2ec(uint32_t source, uint32_t line);

void g1_recon_nrfx_gppi_event_endpoint_setup(
    uint32_t channel, volatile uint8_t *event_endpoint)
{
    if (event_endpoint == 0) {
        FUN_0007e2fa(0x00099cbd, 0x000f6a46, 0x000f6a09, 0x44);
        channel = FUN_0007e2ec(0x000f6a09, 0x44);
        /* The original loaded r1 with the diagnostic line before the noreturn
         * call, so this is its continuation address if that call returns. */
        event_endpoint = (volatile uint8_t *)(uintptr_t)0x44u;
    }

    *(volatile uint32_t *)(event_endpoint + 0x80) =
        channel | UINT32_C(0x80000000);
}
