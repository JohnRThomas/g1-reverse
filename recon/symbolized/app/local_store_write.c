#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00022168 @ 0x00022168
 * public-name: local_store_write
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   settings_save_one                        <= FUN_0004e374 @ 0x0004e374
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9e161                             @ 0x0009e161
 *   rodata_9e187                             @ 0x0009e187
 *   rodata_9e553                             @ 0x0009e553
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed local_store_write @ 0x22168 */

#include <stdint.h>

extern void DEBUG_PRINT(uint32_t format, uint32_t function_name,
                        const char *key_suffix, uint32_t length);
extern void debug_print(uint32_t format, uint32_t function_name,
                         const char *key_suffix, uint32_t length);
extern int settings_save_one(const char *key, const void *value, uint32_t length);
extern void memset_bytes(void *destination, int value, uint32_t length);
extern void FUN_00086fbe(char *destination, const char *source,
                         uint32_t capacity);

uint32_t local_store_write(const char *key_suffix, const void *value,
                           uint32_t length)
{
    static const char key_prefix[28] = "ar_glass_userdata_settings/";
    char key[128];

    for (uint32_t index = 0; index < sizeof(key_prefix); ++index) {
        key[index] = key_prefix[index];
    }

    memset_bytes(key + 28, 0, 100);
    FUN_00086fbe(key, key_suffix, sizeof(key));

    int result = settings_save_one(key, value, length);
    uint32_t format;
    if (result == 0) {
        if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ < 3) {
            return 0;
        }
        format = ((unsigned long)&rodata_9e187) /*=0x9e187*/;
    } else {
        if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ < 1) {
            return 0;
        }
        format = ((unsigned long)&rodata_9e161) /*=0x9e161*/;
    }

    if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
        DEBUG_PRINT(format, ((unsigned long)&rodata_9e553) /*=0x9e553*/, key_suffix, length);
    } else {
        debug_print(format, ((unsigned long)&rodata_9e553) /*=0x9e553*/, key_suffix, length);
    }
    return 0;
}
