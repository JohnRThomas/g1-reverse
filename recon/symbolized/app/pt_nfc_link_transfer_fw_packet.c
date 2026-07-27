#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00030340 @ 0x00030340
 * public-name: pt_nfc_link_transfer_fw_packet
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   attr_store_retry_delay                   <= FUN_0003016c @ 0x0003016c
 *   attr_store_set                           <= FUN_00030178 @ 0x00030178
 *   attr_store_get                           <= FUN_000302f8 @ 0x000302f8
 *   pt_nfc_link_transfer_fw_packet           <= FUN_00030340 @ 0x00030340
 *   malloc                                   <= FUN_00076d6c @ 0x00076d6c
 *   free                                     <= FUN_00076d7c @ 0x00076d7c
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   g_20000800                               @ 0x20000800
 *   g_pt_nfc_link_cfg                        @ 0x20007bc0
 *   g_pt_nfc_link_busy                       @ 0x20019dad
 */
/* Full reconstruction FUN_00030340 @ 0x00030340 (408-byte exact extent). CFG_VERIFY_CALL_ARITIES=1,2,1,2 */
#include <stdint.h>

extern void *malloc(uint32_t);
extern void free(int);
extern void memcpy(void *, const void *, uint32_t, uint32_t, uint32_t);
extern int attr_store_set(uint32_t, uint32_t);
extern void attr_store_retry_delay(uint32_t);
extern int attr_store_get(uint32_t, uint32_t *);

static uint32_t bswap32(uint32_t x)
{
    return __builtin_bswap32(x);
}

int pt_nfc_link_transfer_fw_packet(uint32_t first, uint32_t second,
                 const uint8_t *payload, uint32_t length)
{
    uint32_t packet_size = (length + 14u) & 0xffffu;
    volatile uint8_t *packet = malloc(packet_size);
    if (!packet) return -1;
    *(uint32_t *)packet = 0x02000008u;
    packet[5] = (uint8_t)(length + 12u);
    packet[4] = (uint8_t)((length + 12u) >> 8);
    uint32_t sum = first + second + length;
    for (uint32_t offset = 0; offset < length; offset += 4)
        sum += bswap32(*(const uint32_t *)(payload + offset));
    uint32_t checksum = -sum;
    packet[6] = checksum >> 24;
    packet[7] = checksum >> 16;
    *(volatile uint16_t *)(packet + 8) = (uint16_t)((checksum << 8) | ((checksum >> 8) & 0xff));
    packet[10] = first; packet[11] = second;
    *(volatile uint16_t *)(packet + 12) = (uint16_t)bswap32(length);
    if (length && payload) memcpy((void *)(packet + 14), payload, length, bswap32(length), first);

    uintptr_t driver = *(volatile uintptr_t *)((unsigned long)&g_pt_nfc_link_cfg) /*=0x20007bc0*/;
    int attempt = 5, result;
    do result = ((int (*)(void *, uint32_t))*(uintptr_t *)(driver + 4))((void *)packet, packet_size);
    while (result < 0 && attempt-- != -1);
    free((void *)packet);
    if (attempt == -1) return -1;
    if (attr_store_set(0x1c10, ((unsigned long)&g_20000800) /*=0x20000800*/) || attr_store_set(0x4408, 0x15)) return -1;

    volatile uint8_t *modep = (volatile uint8_t *)((unsigned long)&g_pt_nfc_link_busy) /*=0x20019dad*/;
    uint32_t index = (*modep - 1u) & 0xffu;
    int response_length = index < 5 ? *(const int8_t *)(0x000a49a0u + index) : 0;
    uint32_t setup = index < 5 ? *(const uint8_t *)(0x000a499bu + index) : 0;
    attr_store_retry_delay(setup);
    uint32_t status = 0;
    int timeout = *modep == 3 ? 100 : 10;
    for (;;) {
        if (attr_store_get(0x4410, &status)) return -1;
        if ((int32_t)(status << 2) < 0) break;
        attr_store_retry_delay(1);
        if (timeout-- == 0) return -1;
    }
    status = (status & 0xffff0000u) | 0x18u;
    uint32_t response_size = (uint32_t)(response_length + 15);
    uint16_t *response = malloc(response_size);
    if (!response) return -1;
    attempt = 5;
    while ((result = ((int (*)(uint32_t *, uint32_t, void *, uint32_t))*(uintptr_t *)driver)
                    (&status, 2, response, response_size)) < 0) {
        if (attempt-- == -1) { free(response); return -1; }
    }
    response[0] = __builtin_bswap16(response[0]);
    response[1] = __builtin_bswap16(response[1]);
    response[5] = __builtin_bswap16(response[5]);
    *(uint32_t *)(response + 2) = bswap32(*(uint32_t *)(response + 2));
    if ((uint8_t)response[4] != first || *((uint8_t *)response + 9) != second ||
        *(uint32_t *)(response + 6) != 0) return -1;
    free(response);
    return 0;
}
