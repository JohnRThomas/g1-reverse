#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005c6c8 @ 0x0005c6c8
 * public-name: bt_gatt_connected
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   settings_load_subtree_direct             <= FUN_0004e434 @ 0x0004e434
 *   bt_settings_encode_key                   <= FUN_00052e7c @ 0x00052e7c
 *   u8_to_dec                                <= FUN_0007dc4a @ 0x0007dc4a
 *   bt_addr_le_is_bonded                     <= FUN_00080f92 @ 0x00080f92
 *   g1_recon_bt_conn_set_security            <= FUN_0008149a @ 0x0008149a
 *   bt_conn_get_security                     <= FUN_000814e2 @ 0x000814e2
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 *   bt_gatt_foreach_attr_0                   <= FUN_00082c9c @ 0x00082c9c
 * address symbols (name @ address):
 *   ADDR_gatt_ccc_settings_set_THUMB         @ 0x0005af8d
 *   ADDR_sc_restore_THUMB                    @ 0x0005b555
 *   rodata_88128                             @ 0x00088128
 *   rodata_f4aa1                             @ 0x000f4aa1
 *   rodata_f4d88                             @ 0x000f4d88   [INLINED -- G6 literal batch]
 */
/* Reconstructed ext5c6c8 @ 0x0005c6c8 (bt_gatt_connected).
 * Raw/address backmap: ext5c6c8/FUN_0005c6c8 @ 0x0005c6c8, extent 0x8e.
 */
#include <stdint.h>
extern int bt_addr_le_is_bonded(uint8_t, const void *); /* bt_addr_le_is_bonded */
extern void u8_to_dec(char *, uint32_t, uint8_t); /* u8_to_dec */
extern int bt_settings_encode_key(char *, uint32_t, const char *, const void *, const char *);
extern int settings_load_subtree_direct(const char *, void *, void *); /* settings_load_subtree_direct */
extern void bt_gatt_foreach_attr_0(uint16_t, uint16_t, void *, void *); /* bt_gatt_foreach_attr */
extern uint8_t bt_conn_get_security(void *); /* bt_conn_get_security */
extern int g1_recon_bt_conn_set_security(void *, uint8_t); /* bt_conn_set_security */
extern void log_msg_create_3arg(uint32_t, uint32_t, const void *); /* logger */

struct conn_data_recovered { void *connection; uint8_t security; };

void bt_gatt_connected(uint8_t *connection)
{
    struct conn_data_recovered data = { connection, 1U };
    const void *peer = connection + 0x90;
    if (bt_addr_le_is_bonded(connection[8], peer)) {
        char key[36];
        char identity[4];
        const char *identity_component = 0;
        if (connection[8] != 0U) {
            u8_to_dec(identity, sizeof(identity), connection[8]);
            identity_component = identity;
        }
        bt_settings_encode_key(key, sizeof(key), (const char *)((unsigned long)&rodata_f4aa1) /*=0xf4aa1*/,
                     peer, identity_component);
        settings_load_subtree_direct(key, (void *)ADDR_gatt_ccc_settings_set_THUMB /*=0x5af8d*/, key);
    }
    bt_gatt_foreach_attr_0(1U, 0xffffU, (void *)ADDR_sc_restore_THUMB /*=0x5b555*/, &data);
    if (bt_conn_get_security(connection) < data.security) {
        int error = g1_recon_bt_conn_set_security(connection, data.security);
        if (error != 0) {
            const uint32_t package[3] = { 3U, ((unsigned long)"Failed to set security for bonded peer (%d)") /*=0xf4d88*/, (uint32_t)error };
            log_msg_create_3arg(((unsigned long)&rodata_88128) /*=0x88128*/, 0x1880U, package);
        }
    }
}
