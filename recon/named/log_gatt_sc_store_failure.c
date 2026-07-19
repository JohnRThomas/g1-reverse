/* readable reconstruction; identity: FUN_0005a0e8 @ 0x0005a0e8
 * public-name: log_gatt_sc_store_failure
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sc_store_to_settings                     <= FUN_00053008 @ 0x00053008
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f47d7                             @ 0x000f47d7
 */
/* Reconstructed log_gatt_sc_store_failure @ 0x5a0e8
 * Raw identity: FUN_0005a0e8.
 * Executable extent is [0x5a0e8, 0x5a120); the two following words are the
 * owned format/module literals, and FUN_0005a128 begins at 0x5a128.
 */
#include <stdint.h>

extern int sc_store_to_settings(unsigned type, const void *identity,
                        const void *range, unsigned count);

struct log_record {
    uint32_t argument_count;
    const char *format;
    int error;
};

extern void log_msg_create_3arg(uint32_t module, uint32_t level,
                         const struct log_record *record);

void log_gatt_sc_store_failure(const unsigned char *entry)
{
    int error = sc_store_to_settings(entry[0], entry + 1, entry + 8, 4);

    if (error != 0) {
        struct log_record record;

        record.argument_count = 3;
        record.format = (const char *)(uintptr_t)0x000f47d7;
        record.error = error;
        log_msg_create_3arg(0x00088128, 0x1840, &record);
    }
}
