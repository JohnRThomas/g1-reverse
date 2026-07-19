/* readable reconstruction; identity: FUN_00087080 @ 0x00087080
 * public-name: checked_strncpy_zero_pad
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fortify_chk_fail                         <= FUN_00051164 @ 0x00051164
 *   strncpy_zero_pad                         <= FUN_0008705a @ 0x0008705a
 *   checked_strncpy_zero_pad                 <= FUN_00087080 @ 0x00087080
 */
/* Reconstructed FUN_00087080 @ 0x87080. */

#include <stdint.h>

extern void fortify_chk_fail(void) __attribute__((noreturn));
extern void strncpy_zero_pad(void *destination, const void *source,
                         unsigned int length);

void checked_strncpy_zero_pad(void *destination, const void *source,
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

    strncpy_zero_pad(dst, src, length);
}
