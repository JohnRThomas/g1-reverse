#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008705a @ 0x0008705a
 * public-name: strncpy_zero_pad
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strncpy_zero_pad                         <= FUN_0008705a @ 0x0008705a
 */
/* Reconstructed FUN_0008705a @ 0x8705a. */
#include <stdint.h>

/* Bounded string copy with zero-fill, matching strncpy semantics. */
void strncpy_zero_pad(char *dst, const char *src, uint32_t count)
{
    while (count != 0) {
        char ch = *src++;
        --count;
        *dst++ = ch;
        if (ch == '\0')
            break;
    }

    while (count != 0) {
        *dst++ = '\0';
        --count;
    }
}
