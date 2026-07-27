#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000778d4 @ 0x000778d4
 * public-name: puts
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* app-core puts @ 0x000778d4.
 * Instructions end at 0x778de and the literal pool ends at 0x778e4;
 * 0x778e4 begins a separate wrapper. Raw backmap: FUN_000778d4. */
#include <stdint.h>
extern int _puts_r(struct _reent *, const char *); /* FUN_00077820@0x00077820 */
int puts(const char *text){
    void *reent = *(void * volatile *)((unsigned long)&g_libc_heap_ctrl) /*=0x20002d20*/;
    return _puts_r(reent, text);
}
