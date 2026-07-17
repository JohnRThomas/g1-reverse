/* readable reconstruction; identity: FUN_0003af04 @ 0x0003af04
 * public-name: send_dashboard_status_sync_compact
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   sync_dashboard_default_language          <= FUN_00037060 @ 0x00037060
 *   getStocksIndex                           <= FUN_000370bc @ 0x000370bc
 *   getNewsIndex                             <= FUN_0003719c @ 0x0003719c
 *   send_dashboard_status_sync_compact       <= FUN_0003af04 @ 0x0003af04
 *   send_response_data_to_msgqueue           <= FUN_00047b1c @ 0x00047b1c
 *   send_response_data_to_ble                <= FUN_00047ba8 @ 0x00047ba8
 * address symbols (name @ address):
 *   g_dashboard_disp_mode                    @ 0x2000496a
 */
/* Reconstructed FUN_0003af04 @ 0x3af04 (exact 110-byte extent). */
#include <stdint.h>

extern uint8_t *get_device_info(void);
extern uint32_t sync_dashboard_default_language(void);
extern uint32_t getStocksIndex(void);
extern uint32_t getNewsIndex(void);
extern void send_response_data_to_msgqueue(void *packet, uint32_t length);
extern void send_response_data_to_ble(void);

void send_dashboard_status_sync_compact(void)
{
    if (*get_device_info() == 2)
        return;

    uint32_t packet_words[4];
    packet_words[0] = 0;
    packet_words[1] = 0;
    packet_words[2] = 0;
    packet_words[3] = 0;
    uint8_t *packet = (uint8_t *)packet_words;
    packet[0] = 0x22;
    packet[1] = 0x08;
    packet[4] = 2;
    uint8_t *state = get_device_info();
    packet[5] = *(uint8_t *)(*(uint32_t *)(state + 0xfec) + 0x64);
    uint8_t mode = *(volatile uint8_t *)0x2000496au;
    packet[6] = mode;

    if (mode == 0)
        packet[7] = (uint8_t)(sync_dashboard_default_language() + 1);
    else if (mode == 1)
        packet[7] = (uint8_t)(getStocksIndex() + 1);
    else if (mode == 2)
        packet[7] = (uint8_t)(getNewsIndex() + 1);

    send_response_data_to_msgqueue(packet, 8);
    send_response_data_to_ble();
}
