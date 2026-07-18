/* readable reconstruction; identity: FUN_000225b4 @ 0x000225b4
 * public-name: flash_settings_read
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_9e2da                             @ 0x0009e2da
 *   rodata_9e2f1                             @ 0x0009e2f1
 *   rodata_9e528                             @ 0x0009e528
 *   rodata_a40ec                             @ 0x000a40ec
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed flash_settings_read @ 0x225b4  (CFG-directed candidate) */

#include <stdint.h>

extern int z_device_is_ready(const void *device);
extern uintptr_t get_device_info(void);
extern void log_message(uintptr_t format, ...);
extern void FUN_00074844(uint32_t ticks, uint32_t unused);
extern void debug_print(void);

typedef int (*flash_read_api_t)(uintptr_t device, uint32_t address,
                                void *destination, uint32_t length);

int flash_settings_read(uint32_t address, void *destination, uint32_t length)
{
    unsigned int retry = 0;
    int result;

    for (;;) {
        if (!z_device_is_ready((const void *)0x00087bf0UL)) {
            log_message(0x000a40ecUL,
                         *(volatile uint32_t *)0x00087bf0UL);
            result = -1;
        } else {
            uintptr_t info = get_device_info();
            flash_read_api_t read_api =
                *(flash_read_api_t *)(info + 0x1030U);
            uintptr_t device = get_device_info();

            result = read_api(device, address, destination, length);
            if (result == 0) {
                return 0;
            }
            log_message(0x0009e2daUL, result);
        }

        if (retry == 10U) {
            return result;
        }
        FUN_00074844(0x0ccdU, 0U);
        ++retry;

        if (*(volatile int32_t *)0x2000230cUL > 0) {
            if (*(volatile uint32_t *)0x20007554UL == 0U) {
                log_message(0x0009e2f1UL, 0x0009e528UL, retry);
            } else {
                debug_print();
            }
        }
    }
}
