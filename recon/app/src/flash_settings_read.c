/* Reconstructed flash_settings_read @ 0x225b4  (CFG-directed candidate) */

#include <stdint.h>

extern int FUN_0008638c(const void *device);
extern uintptr_t FUN_000167a8(void);
extern void FUN_0007dda4(uintptr_t format, ...);
extern void FUN_00074844(uint32_t ticks, uint32_t unused);
extern void FUN_00019c70(void);

typedef int (*flash_read_api_t)(uintptr_t device, uint32_t address,
                                void *destination, uint32_t length);

int flash_settings_read(uint32_t address, void *destination, uint32_t length)
{
    unsigned int retry = 0;
    int result;

    for (;;) {
        if (!FUN_0008638c((const void *)0x00087bf0UL)) {
            FUN_0007dda4(0x000a40ecUL,
                         *(volatile uint32_t *)0x00087bf0UL);
            result = -1;
        } else {
            uintptr_t info = FUN_000167a8();
            flash_read_api_t read_api =
                *(flash_read_api_t *)(info + 0x1030U);
            uintptr_t device = FUN_000167a8();

            result = read_api(device, address, destination, length);
            if (result == 0) {
                return 0;
            }
            FUN_0007dda4(0x0009e2daUL, result);
        }

        if (retry == 10U) {
            return result;
        }
        FUN_00074844(0x0ccdU, 0U);
        ++retry;

        if (*(volatile int32_t *)0x2000230cUL > 0) {
            if (*(volatile uint32_t *)0x20007554UL == 0U) {
                FUN_0007dda4(0x0009e2f1UL, 0x0009e528UL, retry);
            } else {
                FUN_00019c70();
            }
        }
    }
}
