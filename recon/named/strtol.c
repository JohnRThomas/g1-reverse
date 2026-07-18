/* readable reconstruction; identity: FUN_00077b24 @ 0x00077b24
 * public-name: strtol
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* strtol @ 0x00077b24; raw FUN_00077b24 */
#include <stdint.h>

extern long strtol_reentrant(void *reent, const char *text, char **end, int base); /* FUN_00077a28 */

long strtol(const char *text, char **end, int base)
{
    void *reent = *(void * volatile *)0x20002d20u;
    return strtol_reentrant(reent, text, end, base);
}
