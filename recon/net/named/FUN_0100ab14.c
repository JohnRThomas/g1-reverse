/* readable reconstruction; identity: FUN_0100ab14 @ 0x0100ab14
 * public-name: FUN_0100ab14
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_rand_poll                            <= FUN_01009204 @ 0x01009204
 *   sdc_ecb_run_blocking                     <= FUN_0100a7e8 @ 0x0100a7e8
 */
/* net-core FUN_0100ab14 @ 0x0100ab14, exact Thumb extent 0x6a bytes. */
#include <stdint.h>

extern void FUN_010091f8(uint8_t *nonce_tail);
extern void sdc_rand_poll(uint8_t *nonce_tail);
extern void sdc_ecb_run_blocking(void *request);
/* Back-maps: FUN_0100a7e8 @ 0x0100a7e8 = sdc_ecb_run_blocking. */

struct ecb_request_image {
    uint8_t key[16];
    uint8_t clear0[12];
    uint8_t zero;
    uint8_t header2;
    uint8_t header1;
    uint8_t header0;
    uint8_t pad[13];
    uint8_t result2;
    uint8_t result1;
    uint8_t result0;
};

void FUN_0100ab14(const uint32_t key[4], uint8_t packet[6], uint32_t direction)
{
    if (direction == 0u) {
        sdc_rand_poll(packet + 3);
    } else {
        FUN_010091f8(packet + 3);
    }

    packet[5] = (uint8_t)((packet[5] & 0x3fu) | 0x40u);
    struct ecb_request_image request;
    ((uint32_t *)(void *)request.key)[0] = key[0];
    ((uint32_t *)(void *)request.key)[1] = key[1];
    ((uint32_t *)(void *)request.key)[2] = key[2];
    ((uint32_t *)(void *)request.key)[3] = key[3];
    ((uint32_t *)(void *)request.clear0)[0] = 0u;
    ((uint32_t *)(void *)request.clear0)[1] = 0u;
    ((uint32_t *)(void *)request.clear0)[2] = 0u;
    request.zero = 0u;
    request.header0 = packet[3];
    request.header1 = packet[4];
    request.header2 = packet[5];
    sdc_ecb_run_blocking(&request);
    packet[0] = request.result0;
    packet[1] = request.result1;
    packet[2] = request.result2;
}
