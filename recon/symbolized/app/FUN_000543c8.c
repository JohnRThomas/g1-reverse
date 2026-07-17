#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000543c8 @ 0x000543c8
 * public-name: FUN_000543c8
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_20002168                               @ 0x20002168
 */
/* Reconstructed FUN_000543c8 @ 0x543c8, exact extent 10 bytes. */
#include <stdint.h>

typedef uint32_t (*dispatch_fn_t)(void);

uint32_t FUN_000543c8(void)
{
    uintptr_t object = *(volatile uintptr_t *)((unsigned long)&g_20002168) /*=0x20002168*/;
    dispatch_fn_t dispatch = *(dispatch_fn_t volatile *)(object + 0x14u);
    return dispatch();
}
