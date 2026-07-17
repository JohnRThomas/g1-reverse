/* Reconstructed FUN_00052fbc @ 0x52fbc
 * Readable identity: bt_settings_delete (NCS 2.5.1 Bluetooth settings ABI).
 * Raw/address backmap: bt_settings_delete <= FUN_00052fbc @ 0x00052fbc.
 */

#include <stddef.h>
#include <stdint.h>

extern void FUN_0007dc4a(char *buffer, size_t buffer_size, uint8_t value);
extern void FUN_00052e7c(char *path, size_t path_size, const char *subsystem,
                         const void *address, const char *key);
extern int FUN_0007ddbe(char *buffer, size_t buffer_size,
                        const char *format, ...);
extern int FUN_0007f198(const char *name);

int FUN_00052fbc(const char *subsystem, uint8_t identity,
                 const void *address)
{
    char identity_string[4];
    char settings_path[36];

    if (address != NULL) {
        const char *optional_identity = NULL;

        if (identity != 0U) {
            FUN_0007dc4a(identity_string, sizeof(identity_string), identity);
            optional_identity = identity_string;
        }

        FUN_00052e7c(settings_path, sizeof(settings_path), subsystem, address,
                     optional_identity);
    } else {
        int formatted = FUN_0007ddbe(settings_path, sizeof(settings_path),
                                     (const char *)0x000f2c6bUL, subsystem);
        if (formatted < 0) {
            return -22;
        }
    }

    return FUN_0007f198(settings_path);
}
