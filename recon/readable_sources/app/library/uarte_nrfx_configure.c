#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_uart_config__param_0311                [param_0311; library]
 *   param_1          => struct g1_layout_uarte_nrfx_data__param_0312            [param_0312; library]
 * Raw function identity: 0x00062ad8.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00062ad8 @ 0x00062ad8
 * public-name: uarte_nrfx_configure
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_9d000                             @ 0x0009d000
 */
/* Reconstructed uarte_nrfx_configure @ 0x00062ad8.
 * Raw/address back-map: FUN_00062ad8 / 0x00062ad8.
 */
#include <stdint.h>

struct device_raw {
    const char *name;
    const void *config;
    const void *api;
    void *state;
    void *data;
};

struct uarte_config_raw {
    volatile uint8_t *peripheral;
};

struct uarte_data_raw {
    uint32_t reserved;
    uint32_t baudrate;
    uint8_t parity;
    uint8_t stop_bits;
    uint8_t data_bits;
    uint8_t flow_ctrl;
};

struct uart_config_raw {
    uint32_t baudrate;
    uint8_t parity;
    uint8_t stop_bits;
    uint8_t data_bits;
    uint8_t flow_ctrl;
};

static uint32_t baudrate_register(uint32_t baudrate)
{
    switch (baudrate) {
    case 300: return 0x00014000u;
    case 600: return 0x00027000u;
    case 1200: return 0x0004f000u;
    case 2400: return ((unsigned long)&rodata_9d000) /*=0x9d000*/;
    case 4800: return 0x0013b000u;
    case 9600: return 0x00275000u;
    case 14400: return 0x003af000u;
    case 19200: return 0x004ea000u;
    case 28800: return 0x0075c000u;
    case 31250: return 0x00800000u;
    case 38400: return 0x009d0000u;
    case 56000: return 0x00e50000u;
    case 57600: return 0x00eb0000u;
    case 76800: return 0x013a9000u;
    case 115200: return 0x01d60000u;
    case 230400: return 0x03b00000u;
    case 250000: return 0x04000000u;
    case 460800: return 0x07400000u;
    case 921600: return 0x0f000000u;
    case 1000000: return 0x10000000u;
    default: return 0u;
    }
}

int uarte_nrfx_configure(const struct device_raw *device,
                         const struct uart_config_raw *config)
{
    uint32_t stop;
    uint32_t parity = 0;
    uint32_t hwfc;

    if (config->stop_bits == 1u) {
        stop = 0;
    } else if (config->stop_bits == 3u) {
        stop = 0x10u;
    } else {
        return -134;
    }
    if (config->data_bits != 3u) {
        return -134;
    }
    if (config->flow_ctrl > 1u) {
        return -134;
    }
    hwfc = config->flow_ctrl;

    if (config->parity == 0u) {
        parity = 0;
    } else if (config->parity == 1u) {
        parity = 0x100u;
    } else if (config->parity == 2u) {
        parity = 0;
    } else {
        return -134;
    }
    if (config->parity != 0u) {
        parity |= 0x0eu;
    }

    uint32_t baud = baudrate_register(config->baudrate);
    if (baud == 0u) {
        return -134;
    }

    const struct uarte_config_raw *dev_config =
        (const struct uarte_config_raw *)device->config;
    *(volatile uint32_t *)(dev_config->peripheral + 0x524) = baud;
    *(volatile uint32_t *)(dev_config->peripheral + 0x56c) =
        stop | parity | hwfc;

    struct uarte_data_raw *data = (struct uarte_data_raw *)device->data;
    *(uint64_t *)&data->baudrate = *(const uint64_t *)config;
    return 0;
}
