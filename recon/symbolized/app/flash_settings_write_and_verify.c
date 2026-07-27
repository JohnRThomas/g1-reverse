#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00022658 @ 0x00022658
 * public-name: flash_settings_write_and_verify
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   free                                     <= FUN_00076d7c @ 0x00076d7c
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 *   safe_memcpy_checked                      <= FUN_00086c1e @ 0x00086c1e
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_9e2da                             @ 0x0009e2da   [INLINED -- G6 literal batch]
 *   rodata_9e324                             @ 0x0009e324   [INLINED -- G6 literal batch]
 *   rodata_9e345                             @ 0x0009e345   [INLINED -- G6 literal batch]
 *   rodata_9e36d                             @ 0x0009e36d   [INLINED -- G6 literal batch]
 *   rodata_9e385                             @ 0x0009e385   [INLINED -- G6 literal batch]
 *   rodata_9e3af                             @ 0x0009e3af   [INLINED -- G6 literal batch]
 *   rodata_9e3c6                             @ 0x0009e3c6   [INLINED -- G6 literal batch]
 *   rodata_9e508                             @ 0x0009e508   [INLINED -- G6 literal batch]
 *   rodata_a40ec                             @ 0x000a40ec
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed flash_settings_write_and_verify @ 0x00022658 (FUN_00022658; CFG-verified). */
/* Firmware application owner; the prior LIBRARY classification was incorrect. */
#include <stdint.h>
#include <stddef.h>
extern void *malloc(size_t);
extern void free(void *);
extern _Bool z_device_is_ready(const struct device *);
extern void memset_bytes(void*, int, int);
extern int memcmp(const void *, const void *, size_t);
extern void safe_memcpy_checked(void *, const void *, size_t, size_t);
extern int get_device_info(void);
extern void log_message(unsigned long, ...);
extern void debug_print(unsigned long, ...);
typedef int (*flash_read_t)(uintptr_t, uint32_t, void *, uint32_t);
typedef int (*flash_erase_t)(uintptr_t, uint32_t, uint32_t);
typedef int (*flash_write_t)(uintptr_t, uint32_t, const void *, uint32_t);

int flash_settings_write_and_verify(uint32_t address, const void *source,
                                    uint32_t length, uint32_t unused)
{
    (void)unused;
    uint8_t *buffer = malloc(0x1000u);
    if (buffer == 0) {
        if (*(volatile uint32_t *)(uintptr_t)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0u)
            log_message(((unsigned long)"[%s-%d]error, have no memory ! \n") /*=0x9e324*/, ((unsigned long)"flash_settings_write_and_verify") /*=0x9e508*/, 0xd2u, 0u);
        else
            debug_print(((unsigned long)"[%s-%d]error, have no memory ! \n") /*=0x9e324*/, ((unsigned long)"flash_settings_write_and_verify") /*=0x9e508*/, 0xd2u, 0u);
        return -1;
    }

    int result;
    const uintptr_t flash_device = ((unsigned long)&rodata_87bf0) /*=0x87bf0*/;
    if (z_device_is_ready((const void *)flash_device) == 0) {
        log_message(((unsigned long)&rodata_a40ec) /*=0xa40ec*/,
                     *(volatile uint32_t *)(uintptr_t)flash_device);
        result = -1;
        goto out;
    }

    memset_bytes(buffer, 0, 0x1000u);
    uintptr_t info = get_device_info();
    flash_read_t read = *(flash_read_t *)(info + 0x1030u);
    info = get_device_info();
    result = read(info, address, buffer, 0x1000u);
    if (result != 0) {
        log_message(((unsigned long)"Flash read failed! %d\n") /*=0x9e2da*/, result);
        goto out;
    }
    if (memcmp(source, buffer, length) == 0) {
        log_message(((unsigned long)"write data and read data is same, exit\n") /*=0x9e345*/);
        result = 0;
        goto out;
    }

    info = get_device_info();
    flash_erase_t erase = *(flash_erase_t *)(info + 0x1038u);
    info = get_device_info();
    int status = erase(info, address, 0x1000u);
    if (status != 0) {
        log_message(((unsigned long)"Flash erase failed! %d\n") /*=0x9e36d*/, status);
        result = status;
        goto out;
    }

    memset_bytes(buffer, 0, 0x1000u);
    safe_memcpy_checked(buffer, source, length, 0x1000u);
    info = get_device_info();
    flash_write_t write = *(flash_write_t *)(info + 0x1034u);
    info = get_device_info();
    status = write(info, address, buffer, 0x1000u);
    if (status != 0) {
        log_message(((unsigned long)"Flash write failed! %d addr %08X size %d\n") /*=0x9e385*/, status, address, length);
        result = status;
        goto out;
    }

    info = get_device_info();
    read = *(flash_read_t *)(info + 0x1030u);
    info = get_device_info();
    status = read(info, address, buffer, 0x1000u);
    if (status != 0) {
        log_message(((unsigned long)"Flash read failed! %d\n") /*=0x9e2da*/, status);
        result = status;
        goto out;
    }
    if (memcmp(source, buffer, length) != 0) {
        log_message(((unsigned long)"flash verify failed\n") /*=0x9e3c6*/);
        result = 1;
        goto out;
    }
    log_message(((unsigned long)"flash verify success!\n") /*=0x9e3af*/);
    result = 0;
out:
    free(buffer);
    return result;
}
