#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086c1e @ 0x00086c1e
 * public-name: safe_memcpy_checked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fortify_chk_fail                         <= FUN_00051164 @ 0x00051164
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   safe_memcpy_checked                      <= FUN_00086c1e @ 0x00086c1e
 */
/* Reconstructed FUN_00086c1e @ 0x86c1e. */

#include <stdint.h>

extern void fortify_chk_fail(void) __attribute__((noreturn));
extern void memcpy(int, int, int);

void safe_memcpy_checked(void *destination, const void *source,
                  unsigned int length, unsigned int destination_size)
{
    const unsigned char *src = source;
    unsigned char *dst = destination;
    uintptr_t src_address = (uintptr_t)src;
    uintptr_t dst_address = (uintptr_t)dst;

    if (length > destination_size ||
        (src_address <= dst_address &&
         dst_address < src_address + length) ||
        (dst_address <= src_address &&
         src_address < dst_address + length)) {
        fortify_chk_fail();
    }

    memcpy(dst, src, length);
}
