/* Reconstructed flash_settings_write_and_verify @ 0x00022658 (FUN_00022658; CFG-verified). */
/* Firmware application owner; the prior LIBRARY classification was incorrect. */
#include <stdint.h>
#include <stddef.h>
extern void *FUN_00076d6c(size_t);
extern void FUN_00076d7c(void *);
extern int FUN_0008638c(const void *);
extern void FUN_00086c78(void *, int, size_t);
extern int FUN_00086be4(const void *, const void *, size_t);
extern void FUN_00086c1e(void *, const void *, size_t, size_t);
extern uintptr_t FUN_000167a8(void);
extern void FUN_0007dda4(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
typedef int (*flash_read_t)(uintptr_t, uint32_t, void *, uint32_t);
typedef int (*flash_erase_t)(uintptr_t, uint32_t, uint32_t);
typedef int (*flash_write_t)(uintptr_t, uint32_t, const void *, uint32_t);

int flash_settings_write_and_verify(uint32_t address, const void *source,
                                    uint32_t length, uint32_t unused)
{
    (void)unused;
    uint8_t *buffer = FUN_00076d6c(0x1000u);
    if (buffer == 0) {
        if (*(volatile uint32_t *)(uintptr_t)0x20007554u == 0u)
            FUN_0007dda4(0x0009e324u, 0x0009e508u, 0xd2u, 0u);
        else
            FUN_00019c70(0x0009e324u, 0x0009e508u, 0xd2u, 0u);
        return -1;
    }

    int result;
    const uintptr_t flash_device = 0x00087bf0u;
    if (FUN_0008638c((const void *)flash_device) == 0) {
        FUN_0007dda4(0x000a40ecu,
                     *(volatile uint32_t *)(uintptr_t)flash_device);
        result = -1;
        goto out;
    }

    FUN_00086c78(buffer, 0, 0x1000u);
    uintptr_t info = FUN_000167a8();
    flash_read_t read = *(flash_read_t *)(info + 0x1030u);
    info = FUN_000167a8();
    result = read(info, address, buffer, 0x1000u);
    if (result != 0) {
        FUN_0007dda4(0x0009e2dau, result);
        goto out;
    }
    if (FUN_00086be4(source, buffer, length) == 0) {
        FUN_0007dda4(0x0009e345u);
        result = 0;
        goto out;
    }

    info = FUN_000167a8();
    flash_erase_t erase = *(flash_erase_t *)(info + 0x1038u);
    info = FUN_000167a8();
    int status = erase(info, address, 0x1000u);
    if (status != 0) {
        FUN_0007dda4(0x0009e36du, status);
        result = status;
        goto out;
    }

    FUN_00086c78(buffer, 0, 0x1000u);
    FUN_00086c1e(buffer, source, length, 0x1000u);
    info = FUN_000167a8();
    flash_write_t write = *(flash_write_t *)(info + 0x1034u);
    info = FUN_000167a8();
    status = write(info, address, buffer, 0x1000u);
    if (status != 0) {
        FUN_0007dda4(0x0009e385u, status, address, length);
        result = status;
        goto out;
    }

    info = FUN_000167a8();
    read = *(flash_read_t *)(info + 0x1030u);
    info = FUN_000167a8();
    status = read(info, address, buffer, 0x1000u);
    if (status != 0) {
        FUN_0007dda4(0x0009e2dau, status);
        result = status;
        goto out;
    }
    if (FUN_00086be4(source, buffer, length) != 0) {
        FUN_0007dda4(0x0009e3c6u);
        result = 1;
        goto out;
    }
    FUN_0007dda4(0x0009e3afu);
    result = 0;
out:
    FUN_00076d7c(buffer);
    return result;
}
