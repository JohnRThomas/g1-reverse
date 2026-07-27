/* Reconstructed local_store_write @ 0x22168 */

#include <stdint.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_0004e374(const char *key, const void *value, uint32_t length);
extern void FUN_00086c78(void *destination, int value, uint32_t length);
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

    FUN_00086c78(key + 28, 0, 100);
    FUN_00086fbe(key, key_suffix, sizeof(key));

    int result = FUN_0004e374(key, value, length);
    uint32_t format;
    if (result == 0) {
        if (*(volatile int32_t *)0x2000230cUL < 3) {
            return 0;
        }
        format = 0x0009e187UL;
    } else {
        if (*(volatile int32_t *)0x2000230cUL < 1) {
            return 0;
        }
        format = 0x0009e161UL;
    }

    if (*(volatile uint32_t *)0x20007554UL == 0) {
        DEBUG_PRINT(format, 0x0009e553UL, key_suffix, length);
    } else {
        FUN_00019c70(format, 0x0009e553UL, key_suffix, length);
    }
    return 0;
}
