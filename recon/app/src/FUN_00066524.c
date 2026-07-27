/* Reconstructed FUN_00066524 @ 0x66524
 * Readable identity: qspi_xfer (static nrfx_qspi.c transfer engine).
 * Raw/address backmap: qspi_xfer <= FUN_00066524 @ 0x00066524.
 */

#include <stdint.h>

extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(uint32_t, uint32_t);
extern uint32_t FUN_000664f0(uint32_t enable);
extern uint32_t FUN_0006649c(void);

uint32_t FUN_00066524(uint32_t buffer0, uint32_t buffer1,
                      uint32_t transfer_count, uint32_t direction)
{
    volatile uint8_t *const controller =
        (volatile uint8_t *)0x2000b348UL;
    volatile uint32_t *const peripheral =
        (volatile uint32_t *)0x5002b000UL;
    uint8_t state = controller[0x30];

    if (state == 0U) {
        FUN_0007e2fa(0x00099cbdUL, 0x000f6d9aUL, 0x000f6d5eUL, 0x7aUL);
        FUN_0007e2ec(0x000f6d5eUL, 0x7aUL);
    }
    if (buffer0 == 0U) {
        FUN_0007e2fa(0x00099cbdUL, 0x000f6dc6UL, 0x000f6d5eUL, 0x7bUL);
        FUN_0007e2ec(0x000f6d5eUL, 0x7bUL);
    }

    if (((buffer0 & 0xe0000000UL) != 0x20000000UL) ||
        ((buffer0 & 3U) != 0U)) {
        return 0x0bad000aUL;
    }

    if ((state != 1U) &&
        ((state != (uint8_t)direction) || (controller[0x38] == 0U))) {
        return 0x0bad000bUL;
    }

    if (direction == 2U) {
        peripheral[0x510U / 4U] = transfer_count;
        peripheral[0x514U / 4U] = buffer0;
        peripheral[0x518U / 4U] = buffer1;
    } else {
        peripheral[0x504U / 4U] = transfer_count;
        peripheral[0x508U / 4U] = buffer0;
        peripheral[0x50cU / 4U] = buffer1;
    }

    controller[0x39] = 0U;

    if (*(volatile uint32_t *)(controller + 0x00) == 0U) {
        if (controller[0x38] == 0U) {
            uint32_t result = FUN_000664f0(1U);
            if (result == 0x0bad0007UL) {
                return result;
            }
        }

        peripheral[0x100U / 4U] = 0U;
        *(volatile uint32_t *)(0x5002b000UL +
                              ((direction == 2U) ? 8U : 4U)) = 1U;
        return FUN_0006649c();
    }

    if (*(volatile uint32_t *)(controller + 0x08) != 0U) {
        *(volatile uint32_t *)(controller + 0x0c) = buffer0;
        *(volatile uint32_t *)(controller + 0x14) = buffer1;
        *(volatile uint32_t *)(controller + 0x1c) = transfer_count;
        return 0x0bad0000UL;
    }

    controller[0x30] = (uint8_t)direction;
    *(volatile uint32_t *)(controller + 0x18) = transfer_count;
    *(volatile uint32_t *)(controller + 0x08) = buffer0;
    *(volatile uint32_t *)(controller + 0x10) = buffer1;
    peripheral[0x100U / 4U] = 0U;
    peripheral[0x304U / 4U] = 1U;

    if (controller[0x38] == 0U) {
        (void)FUN_000664f0(0U);
    } else {
        *(volatile uint32_t *)(0x5002b000UL +
                              ((direction == 2U) ? 8U : 4U)) = 1U;
    }

    return 0x0bad0000UL;
}
