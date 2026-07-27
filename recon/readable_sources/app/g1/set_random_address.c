#include "g1_app_symbols.h"
#include <stddef.h>
/* readable reconstruction; identity: FUN_00054d88 @ 0x00054d88
 * public-name: set_random_address
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_cmd_create                        <= FUN_00053cd4 @ 0x00053cd4
 *   bt_hci_cmd_send_sync                     <= FUN_00053d70 @ 0x00053d70
 *   bt_addr_copy                             <= FUN_00080fba @ 0x00080fba
 *   net_buf_simple_add_mem                   <= FUN_00083740 @ 0x00083740
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 * address symbols (name @ address):
 *   g_20002069                               @ 0x20002069
 */
/* Reconstructed tail_54d88 @ 0x54d88
 * CFG_VERIFY_CALL_ARITIES=3,2,3,3,2
 * Readable identity: set_random_address.
 * Raw/address backmap: set_random_address <= tail_54d88 @ 0x00054d88.
 */
#include <stdint.h>
extern int memcmp(const void *, const void *, size_t); /* memcmp */
extern uint8_t *bt_hci_cmd_create(uint32_t, uint32_t); /* bt_hci_cmd_create */
extern void *net_buf_simple_add_mem(void *, const void *, uint32_t); /* memcpy */
extern int bt_hci_cmd_send_sync(uint32_t, void *, void *); /* bt_hci_cmd_send_sync */
extern uint8_t *bt_addr_copy(void *, const void *); /* bt_addr_copy */

int set_random_address(const void *address)
{
    uint8_t *packet;
    int error;
    if (memcmp(address, (const void *)((unsigned long)&g_20002069) /*=0x20002069*/, 6U) == 0) return 0;
    packet = bt_hci_cmd_create(0x2005U, 6U);
    if (packet == 0) return -105;
    net_buf_simple_add_mem(packet + 12, address, 6U);
    error = bt_hci_cmd_send_sync(0x2005U, packet, 0);
    if (error != 0) return error;
    packet = bt_addr_copy((void *)((unsigned long)&g_20002069) /*=0x20002069*/, address);
    packet[-1] = 1U;
    return 0;
}
