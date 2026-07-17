#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086c1e @ 0x00086c1e
 * public-name: FUN_00086c1e
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 */
/* Reconstructed FUN_00086c1e @ 0x86c1e. */

#include <stdint.h>

extern void FUN_00051164(void) __attribute__((noreturn));
extern void memcpy(void *destination, const void *source,
                         unsigned int length);

void FUN_00086c1e(void *destination, const void *source,
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
        FUN_00051164();
    }

    memcpy(dst, src, length);
}
