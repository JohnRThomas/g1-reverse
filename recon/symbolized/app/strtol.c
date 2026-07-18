#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00077b24 @ 0x00077b24
 * public-name: strtol
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* strtol @ 0x00077b24; raw FUN_00077b24 */
#include <stdint.h>

extern long FUN_00077a28(int *reent, const char *text, char **end, int base); /* _strtol_r */

long strtol(const char *text, char **end, int base)
{
    int *reent = *(int * volatile *)((unsigned long)&g_libc_heap_ctrl) /*=0x20002d20*/;
    return FUN_00077a28(reent, text, end, base);
}
