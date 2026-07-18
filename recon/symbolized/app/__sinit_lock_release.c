#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00076bc0 @ 0x00076bc0
 * public-name: __sinit_lock_release
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_env_mutex                              @ 0x20003818
 */
/* __sinit_lock_release @ 0x00076bc0; raw FUN_00076bc0 */
#include <stdint.h>

extern void __retarget_lock_release_recursive(void *lock); /* FUN_00051134 */

void __sinit_lock_release(void)
{
    __retarget_lock_release_recursive((void *)((unsigned long)&g_env_mutex) /*=0x20003818*/);
}
