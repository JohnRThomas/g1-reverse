#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00024c14 @ 0x00024c14
 * public-name: adc_nfc_run
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   adc_gain_invert                          <= FUN_0005f60c @ 0x0005f60c
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 * address symbols (name @ address):
 *   rodata_87c20                             @ 0x00087c20
 *   rodata_9f104                             @ 0x0009f104   [INLINED -- G6 literal batch]
 *   rodata_9f120                             @ 0x0009f120   [INLINED -- G6 literal batch]
 *   rodata_9f1c3                             @ 0x0009f1c3   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed application adc_nfc_run @ 0x00024c14.
 * Raw/address back-map: FUN_00024c14 / 0x00024c14.
 */
#include <stdint.h>
#include <string.h>
#include "../../../headers/g1_log.h"

struct device_raw {
    const char *name;
    const void *config;
    const void *api;
};

struct adc_api_raw {
    int (*channel_setup)(const struct device_raw *, const void *);
    int (*read)(const struct device_raw *, const void *);
    uint16_t scale;
};

struct adc_sequence_raw {
    uint32_t options;
    uint32_t channels;
    void *buffer;
    uint32_t buffer_size;
    uint8_t resolution;
    uint8_t oversampling;
    uint8_t calibrate;
    uint8_t reserved;
};

extern int adc_gain_invert(int32_t whole, int32_t *fraction);

uint32_t adc_nfc_run(void)
{
    int16_t sample;
    int32_t scaled;
    struct adc_sequence_raw sequence;
    memset(&sequence, 0, sizeof(sequence));
    sequence.channels = 8u;
    sequence.buffer = &sample;
    sequence.buffer_size = 2u;
    sequence.resolution = 12u;

    const struct device_raw *device =
        (const struct device_raw *)((unsigned long)&rodata_87c20) /*=0x87c20*/;
    const struct adc_api_raw *api =
        (const struct adc_api_raw *)device->api;
    int result = api->read(device, &sequence);
    if (result < 0) {
        if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
            if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0u) {
                log_message((const void *)((unsigned long)"%s(): Could not read (%d)\n\n") /*=0x9f104*/,
                             (const void *)((unsigned long)"adc_nfc_run") /*=0x9f1c3*/);
            } else {
                debug_print((const void *)((unsigned long)"%s(): Could not read (%d)\n\n") /*=0x9f104*/,
                             (const void *)((unsigned long)"adc_nfc_run") /*=0x9f1c3*/);
            }
        }
        return 0;
    }

    uint32_t value = (uint16_t)sample;
    scaled = (int32_t)(value * api->scale);
    result = adc_gain_invert(0, &scaled);
    if (result == 0) {
        value = (uint32_t)scaled >> 12;
    } else if (result < 0) {
        if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
            if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0u) {
                log_message((const void *)((unsigned long)"%s():  (value in mV not available)\n\n") /*=0x9f120*/,
                             (const void *)((unsigned long)"adc_nfc_run") /*=0x9f1c3*/);
            } else {
                debug_print((const void *)((unsigned long)"%s():  (value in mV not available)\n\n") /*=0x9f120*/,
                             (const void *)((unsigned long)"adc_nfc_run") /*=0x9f1c3*/);
            }
        }
        return 0;
    }

    return (value >= 1u && value <= 1199u) ? value : 0u;
}
