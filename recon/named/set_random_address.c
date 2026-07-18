/* readable reconstruction; identity: FUN_00054d88 @ 0x00054d88
 * public-name: set_random_address
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_cmd_create                        <= FUN_00053cd4 @ 0x00053cd4
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
extern int memcmp(const void *, const void *, uint32_t); /* memcmp */
extern uint8_t *bt_hci_cmd_create(uint32_t, uint32_t); /* bt_hci_cmd_create */
extern void *FUN_00083740(void *, const void *, uint32_t); /* memcpy */
extern int FUN_00053d70(uint32_t, void *, void *); /* bt_hci_cmd_send_sync */
extern uint8_t *FUN_00080fba(void *, const void *); /* bt_addr_copy */

int set_random_address(const void *address)
{
    uint8_t *packet;
    int error;
    if (memcmp(address, (const void *)0x20002069UL, 6U) == 0) return 0;
    packet = bt_hci_cmd_create(0x2005U, 6U);
    if (packet == 0) return -105;
    FUN_00083740(packet + 12, address, 6U);
    error = FUN_00053d70(0x2005U, packet, 0);
    if (error != 0) return error;
    packet = FUN_00080fba((void *)0x20002069UL, address);
    packet[-1] = 1U;
    return 0;
}
