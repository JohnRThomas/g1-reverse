#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00035744 @ 0x00035744
 * public-name: dump_whitelist_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dump_whitelist_init                      <= FUN_00035744 @ 0x00035744
 * address symbols (name @ address):
 *   rodata_a8a05                             @ 0x000a8a05   [INLINED -- G6 literal batch]
 *   g_app_whitelist_buffer                   @ 0x2001a22c
 */
/* Reconstructed FUN_00035744 @ 0x35744.
 * Readable identity: dump_whitelist_init.
 * Exact standalone extent: 0x28 bytes; literal pool begins at 0x3576c.
 */

#include <stdint.h>
#include "../../headers/g1_log.h"

extern void *memset_bytes(void *destination, int value, uint32_t length);
extern int load_whitelist(void);
extern void revalidate_whitelist_json(void);

void dump_whitelist_init(void)
{
    memset_bytes((void *)((unsigned long)g_app_whitelist_buffer) /*=0x2001a22c*/, 0, 0x15e2U);
    log_message(((unsigned long)"MAX_WHITE_LIST_BUF_LEN is %d \n") /*=0xa8a05*/, 0x15e3U);
    if (load_whitelist() == 0) {
        revalidate_whitelist_json();
    }
}
