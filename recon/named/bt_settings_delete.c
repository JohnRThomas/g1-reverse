/* readable reconstruction; identity: FUN_00052fbc @ 0x00052fbc
 * public-name: bt_settings_delete
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_settings_encode_key                   <= FUN_00052e7c @ 0x00052e7c
 *   bt_settings_delete                       <= FUN_00052fbc @ 0x00052fbc
 *   u8_to_dec                                <= FUN_0007dc4a @ 0x0007dc4a
 *   snprintk                                 <= FUN_0007ddbe @ 0x0007ddbe
 *   settings_delete                          <= FUN_0007f198 @ 0x0007f198
 * address symbols (name @ address):
 *   rodata_f2c6b                             @ 0x000f2c6b
 */
/* Reconstructed FUN_00052fbc @ 0x52fbc
 * Readable identity: bt_settings_delete (NCS 2.5.1 Bluetooth settings ABI).
 * Raw/address backmap: bt_settings_delete <= FUN_00052fbc @ 0x00052fbc.
 */

#include <stddef.h>
#include <stdint.h>

extern void u8_to_dec(char *buffer, size_t buffer_size, uint8_t value);
extern void bt_settings_encode_key(char *path, size_t path_size, const char *subsystem,
                         const void *address, const char *key);
extern int snprintk(char *buffer, size_t buffer_size,
                        const char *format, ...);
extern int settings_delete(const char *name);

int bt_settings_delete(const char *subsystem, uint8_t identity,
                 const void *address)
{
    char identity_string[4];
    char settings_path[36];

    if (address != NULL) {
        const char *optional_identity = NULL;

        if (identity != 0U) {
            u8_to_dec(identity_string, sizeof(identity_string), identity);
            optional_identity = identity_string;
        }

        bt_settings_encode_key(settings_path, sizeof(settings_path), subsystem, address,
                     optional_identity);
    } else {
        int formatted = snprintk(settings_path, sizeof(settings_path),
                                     (const char *)0x000f2c6bUL, subsystem);
        if (formatted < 0) {
            return -22;
        }
    }

    return settings_delete(settings_path);
}
