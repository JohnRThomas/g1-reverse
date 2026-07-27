/* Reconstructed application adc_nfc_init @ 0x00024b98.
 * Raw/address back-map: FUN_00024b98 / 0x00024b98.
 */
#include <stdint.h>

struct device_raw {
    const char *name;
    const void *config;
    const void *api;
};

struct adc_api_raw {
    int (*channel_setup)(const struct device_raw *, const void *);
};

extern int FUN_0008638c(const struct device_raw *device);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_0007dda4(unsigned long, ...);

int adc_nfc_init(void)
{
    const struct device_raw *device =
        (const struct device_raw *)0x00087c20u;

    if (FUN_0008638c(device) != 0) {
        const struct adc_api_raw *api =
            (const struct adc_api_raw *)device->api;
        int result = api->channel_setup(device, (const void *)0x00088a2au);
        if (result < 0 && *(volatile int32_t *)0x2000230cu > 0) {
            if (*(volatile uint32_t *)0x20007554u == 0u) {
                FUN_0007dda4((const void *)0x0009f0dbu,
                             (const void *)0x0009f1cfu, 0);
            } else {
                FUN_00019c70((const void *)0x0009f0dbu,
                             (const void *)0x0009f1cfu, 0);
            }
        }
    } else if (*(volatile int32_t *)0x2000230cu > 0) {
        if (*(volatile uint32_t *)0x20007554u == 0u) {
            FUN_0007dda4((const void *)0x0009f0b0u,
                         (const void *)0x0009f1cfu, device->name);
        } else {
            FUN_00019c70((const void *)0x0009f0b0u,
                         (const void *)0x0009f1cfu, device->name);
        }
    }
    return 0;
}
