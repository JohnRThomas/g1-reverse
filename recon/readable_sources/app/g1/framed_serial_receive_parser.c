#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00033554 @ 0x00033554
 * public-name: framed_serial_receive_parser
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_a7993                             @ 0x000a7993
 *   rodata_a7aab                             @ 0x000a7aab
 *   rodata_a7ac1                             @ 0x000a7ac1
 *   rodata_f5400                             @ 0x000f5400
 *   g_uart_rx_frame_len                      @ 0x2001a128
 *   g_uart_rx_frame_buf                      @ 0x2001a129
 *   g_2001a12d                               @ 0x2001a12d
 */
/* CPUAPP framed serial receive/parser @ 0x00033554.
 * Raw/back-map identity: FUN_00033554, exact extent 0x14c bytes. */
#include <stdint.h>

extern void memcpy(void *destination, const void *source, uint32_t size);
extern void log_message(uintptr_t format, ...);

uint32_t framed_serial_receive_parser(uint32_t transport, uint8_t **output,
                      uint32_t *output_size)
{
    volatile uint8_t *const received_size = (volatile uint8_t *)((unsigned long)&g_uart_rx_frame_len) /*=0x2001a128*/;
    volatile uint8_t *const received = (volatile uint8_t *)((unsigned long)g_uart_rx_frame_buf) /*=0x2001a129*/;
    uint32_t offset;

    if (transport == 0u || output == 0 || output_size == 0)
        return 0xffffffffu;
    if (*received_size == 0u)
        return 0xfffffffeu;

    for (offset = 0u; offset <= 0x100u - (uint32_t)*received_size; ++offset) {
        uint32_t payload_size;
        uint32_t index;
        uint8_t checksum;

        if (received[offset] != 0x5au || received[offset + 1u] != 0xa5u ||
            received[offset + 2u] != 0x7fu)
            continue;
        payload_size = received[offset + 3u];
        if ((int32_t)(payload_size + 4u) >= (int32_t)(0x100u - offset))
            continue;

        checksum = 0u;
        for (index = 0u; index != payload_size + 4u; ++index)
            checksum = (uint8_t)(checksum + received[offset + index]);
        if (received[offset + payload_size + 4u] != checksum)
            continue;

        memcpy(*output, (const void *)(uintptr_t)
                     (((unsigned long)&g_2001a12d) /*=0x2001a12d*/ + offset), payload_size);
        *output_size = payload_size;
        log_message(((unsigned long)&rodata_a7aab) /*=0xa7aab*/);
        for (index = 0u; index != payload_size; ++index)
            log_message(((unsigned long)&rodata_a7993) /*=0xa7993*/, (uint32_t)(*output)[index]);
        log_message(((unsigned long)&rodata_f5400) /*=0xf5400*/);
        if (offset <= 0x100u - (uint32_t)*received_size) {
            *received_size = 0u;
            return 0u;
        }
        break;
    }

    *received_size = 0u;
    log_message(((unsigned long)&rodata_a7ac1) /*=0xa7ac1*/);
    return 0xfffffffdu;
}
