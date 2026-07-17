#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101e660 @ 0x0101e660
 * public-name: FUN_0101e660
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ble_conn_create_ctx                @ 0x21000eac
 */
/* net-core FUN_0101e660 @ 0x101e660 */
#include <stdint.h>
extern uint32_t FUN_0101f8d8(void);
extern void FUN_0100d584(uint32_t, const void *);

uint32_t FUN_0101e660(uint32_t context)
{
    volatile const uint8_t *configuration = (const uint8_t *)((unsigned long)&g_net_ble_conn_create_ctx) /*=0x21000eac*/;
    uint32_t first = configuration[0x12];
    uint32_t second = configuration[0x13];
    uint16_t tail = *(volatile const uint16_t *)(configuration + 0x14);
    uint8_t message[4];

    if (first == 0)
        first = FUN_0101f8d8();
    if (second == 0)
        second = FUN_0101f8d8();
    if (first == 0 || second == 0)
        return 9;

    message[0] = (uint8_t)first;
    message[1] = (uint8_t)second;
    *(uint16_t *)(message + 2) = tail;
    FUN_0100d584(context, message);
    return 0;
}
