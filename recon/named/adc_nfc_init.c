/* readable reconstruction; identity: FUN_00024b98 @ 0x00024b98
 * public-name: adc_nfc_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_87c20                             @ 0x00087c20
 *   rodata_88a2a                             @ 0x00088a2a
 *   rodata_9f0b0                             @ 0x0009f0b0   [INLINED -- G6 literal batch]
 *   rodata_9f0db                             @ 0x0009f0db   [INLINED -- G6 literal batch]
 *   rodata_9f1cf                             @ 0x0009f1cf   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed application adc_nfc_init @ 0x00024b98.
 * Raw/address back-map: FUN_00024b98 / 0x00024b98.
 */
#include <stdint.h>
#include "../headers/g1_log.h"

struct device_raw {
    const char *name;
    const void *config;
    const void *api;
};

struct adc_api_raw {
    int (*channel_setup)(const struct device_raw *, const void *);
};

extern int z_device_is_ready(const struct device_raw *device);

int adc_nfc_init(void)
{
    const struct device_raw *device =
        (const struct device_raw *)0x00087c20u;

    if (z_device_is_ready(device) != 0) {
        const struct adc_api_raw *api =
            (const struct adc_api_raw *)device->api;
        int result = api->channel_setup(device, (const void *)0x00088a2au);
        if (result < 0 && *(volatile int32_t *)0x2000230cu > 0) {
            if (*(volatile uint32_t *)0x20007554u == 0u) {
                log_message((const void *)0x0009f0dbu,
                             (const void *)0x0009f1cfu, 0);
            } else {
                debug_print((const void *)0x0009f0dbu,
                             (const void *)0x0009f1cfu, 0);
            }
        }
    } else if (*(volatile int32_t *)0x2000230cu > 0) {
        if (*(volatile uint32_t *)0x20007554u == 0u) {
            log_message((const void *)0x0009f0b0u,
                         (const void *)0x0009f1cfu, device->name);
        } else {
            debug_print((const void *)0x0009f0b0u,
                         (const void *)0x0009f1cfu, device->name);
        }
    }
    return 0;
}
