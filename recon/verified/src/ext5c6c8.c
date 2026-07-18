/* Reconstructed ext5c6c8 @ 0x0005c6c8 (bt_gatt_connected).
 * Raw/address backmap: ext5c6c8/FUN_0005c6c8 @ 0x0005c6c8, extent 0x8e.
 */
#include <stdint.h>
extern int FUN_00080f92(uint8_t, const void *); /* bt_addr_le_is_bonded */
extern void FUN_0007dc4a(char *, uint32_t, uint8_t); /* u8_to_dec */
extern int FUN_00052e7c(char *, uint32_t, const char *, const void *, const char *);
extern int FUN_0004e434(const char *, void *, void *); /* settings_load_subtree_direct */
extern void FUN_00082c9c(uint16_t, uint16_t, void *, void *); /* bt_gatt_foreach_attr */
extern uint8_t FUN_000814e2(void *); /* bt_conn_get_security */
extern int FUN_0008149a(void *, uint8_t); /* bt_conn_set_security */
extern void FUN_00082a42(uint32_t, uint32_t, const void *); /* logger */

struct conn_data_recovered { void *connection; uint8_t security; };

void ext5c6c8(uint8_t *connection)
{
    struct conn_data_recovered data = { connection, 1U };
    const void *peer = connection + 0x90;
    if (FUN_00080f92(connection[8], peer)) {
        char key[36];
        char identity[4];
        const char *identity_component = 0;
        if (connection[8] != 0U) {
            FUN_0007dc4a(identity, sizeof(identity), connection[8]);
            identity_component = identity;
        }
        FUN_00052e7c(key, sizeof(key), (const char *)0x000f4aa1U,
                     peer, identity_component);
        FUN_0004e434(key, (void *)0x0005af8dU, key);
    }
    FUN_00082c9c(1U, 0xffffU, (void *)0x0005b555U, &data);
    if (FUN_000814e2(connection) < data.security) {
        int error = FUN_0008149a(connection, data.security);
        if (error != 0) {
            const uint32_t package[3] = { 3U, 0x000f4d88U, (uint32_t)error };
            FUN_00082a42(0x00088128U, 0x1880U, package);
        }
    }
}
