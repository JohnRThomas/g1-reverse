#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00076bc0 @ 0x00076bc0
 * public-name: __sinit_lock_release
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_recon_retarget_lock_release_recursive <= FUN_00051134 @ 0x00051134
 * address symbols (name @ address):
 *   g_env_mutex                              @ 0x20003818
 */
/* __sinit_lock_release @ 0x00076bc0; raw FUN_00076bc0 */
#include <stdint.h>

#define g1_recon_retarget_lock_release_recursive g1_recon_retarget_lock_release_recursive
extern void g1_recon_retarget_lock_release_recursive(unsigned long); /* FUN_00051134@0x00051134 */

void __sinit_lock_release(void)
{
    g1_recon_retarget_lock_release_recursive((void *)((unsigned long)&g_env_mutex) /*=0x20003818*/);
}
