#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000778d4 @ 0x000778d4
 * public-name: FUN_000778d4
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* Reconstructed FUN_000778d4 @ 0x778d4.
 * Instructions end at 0x778de and the literal pool ends at 0x778e4;
 * 0x778e4 begins a separate wrapper. */
#include <stdint.h>
extern int FUN_00077820(int context, int value);
int FUN_000778d4(int param_1){
    int r0 = *(volatile int*)((unsigned long)&g_libc_heap_ctrl) /*=0x20002d20*/;
    return FUN_00077820(r0, param_1);
}
