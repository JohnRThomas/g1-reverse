/* Reconstructed FUN_00035744 @ 0x35744.
 * Readable identity: dump_whitelist_init.
 * Exact standalone extent: 0x28 bytes; literal pool begins at 0x3576c.
 */

#include <stdint.h>

extern void *memset_bytes(void *destination, int value, uint32_t length);
extern void log_message(unsigned long, ...);
extern unsigned int load_whitelist(void);
extern void revalidate_whitelist_json(void);

void FUN_00035744(void)
{
    memset_bytes((void *)0x2001a22cUL, 0, 0x15e2U);
    log_message(0x000a8a05UL, 0x15e3U);
    if (load_whitelist() == 0) {
        revalidate_whitelist_json();
    }
}
