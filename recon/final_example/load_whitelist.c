#include "g1_app_symbols.h"
#include <stdint.h>

/* load_whitelist @ 0x34b34
 *
 * Read the BLE whitelist blob from its flash-settings partition into the RAM
 * working buffer. On success (flash read OK and the entry-count byte is in
 * range) the blob is copied to g_app_whitelist_buffer and 0 is returned.
 * Otherwise the error is logged and 0xffffffff is returned.
 *
 * Reconstructed and parity-proven byte-identical to the original (300/300
 * trials). Symbolized: absolute addresses replaced with named symbols; local
 * temporaries retyped for warning-clean compilation. Structure is unchanged
 * from the proven form so the emitted code still byte-matches the image.
 */

extern void         memset_bytes(void *dst, int val, int n);
extern unsigned int flash_settings_read(uint32_t flash_off, void *dst, int n);
extern void        *memcpy(void *dst, const void *src, unsigned int n);
extern void         debug_print(const char *fmt, const char *func, int line, unsigned int arg);
extern void         DEBUG_PRINT(const char *fmt, const char *func, int line, unsigned int arg);

#define WHITELIST_BLOB_SIZE    0x15e2
#define WHITELIST_MAX_ENTRIES  0x65      /* 101 */

unsigned int load_whitelist(void)
{
    unsigned char buf[WHITELIST_BLOB_SIZE];
    unsigned int  arg;          /* was uVar1: flash-read status, then reused as entry count */
    const char   *fmt;          /* was uVar2 */
    int           line;         /* was uVar3 */

    memset_bytes(buf, 0, WHITELIST_BLOB_SIZE);

    arg = flash_settings_read(FLASH_ADDR_APP_WHITELIST, buf, WHITELIST_BLOB_SIZE);
    if (arg == 0) {
        arg = (unsigned int)buf[1];                 /* entry count */
        if (arg < WHITELIST_MAX_ENTRIES) {
            memcpy(g_app_whitelist_buffer, buf, WHITELIST_BLOB_SIZE);
            return 0;
        }
        if (g_log_use_alt_sink != 0) {
            line = 0x36;
            fmt  = "[%s-%d] error,appCounts is %d \n";
            debug_print(fmt, "load_whitelist", line, arg);
            return 0xffffffff;
        }
        line = 0x36;
        fmt  = "[%s-%d] error,appCounts is %d \n";
    } else {
        if (g_log_use_alt_sink != 0) {
            line = 0x30;
            fmt  = "[%s-%d] flash_settings_read error,ret is %d \n";
            debug_print(fmt, "load_whitelist", line, arg);
            return 0xffffffff;
        }
        line = 0x30;
        fmt  = "[%s-%d] flash_settings_read error,ret is %d \n";
    }
    DEBUG_PRINT(fmt, "load_whitelist", line, arg);
    return 0xffffffff;
}
