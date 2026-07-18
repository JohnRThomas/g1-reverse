/* Full reconstruction FUN_00060a5c @ 0x00060a5c (100-byte exact extent). */
#include <stdint.h>

extern uint64_t FUN_00083906(void *device);
extern void FUN_00072908(void *object, uint32_t inherited_r1, uint32_t, uint32_t);
#define g1_recon_nrfx_qspi_mem_busy_check FUN_00066ae0
extern uintptr_t g1_recon_nrfx_qspi_mem_busy_check(void);
extern void FUN_00074844(uint32_t, uint32_t);
extern void FUN_00066b24(void);
extern void FUN_0008392e(void *device);

void FUN_00060a5c(uint8_t *device)
{
    uint8_t *state = *(uint8_t **)(device + 0x10);
    if (*(volatile uint8_t *)(state + 0x60) != 0)
        return;

    uint64_t inherited = FUN_00083906(device);
    FUN_00072908(state + 0x48, (uint32_t)(inherited >> 32), 0, 0);
    if (*(volatile uint32_t *)(state + 0x50) == 0) {
        while (g1_recon_nrfx_qspi_mem_busy_check() != 0x0bad0000u)
            FUN_00074844(0x667u, 0);
        FUN_00066b24();
        *(volatile uint8_t *)0x2001d535u = 0;
    }
    FUN_0008392e(device);
}
