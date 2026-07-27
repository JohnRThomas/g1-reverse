#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00051134 @ 0x00051134
 * public-name: g1_recon_retarget_lock_release_recursive
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_recon_retarget_lock_release_recursive <= FUN_00051134 @ 0x00051134
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f22d5                             @ 0x000f22d5   [INLINED -- G6 literal batch]
 *   rodata_f23d4                             @ 0x000f23d4
 */
/* Retained asserting recursive-lock release hook @ 0x00051134.
 * Raw/address back-map: FUN_00051134 / 0x00051134.
 * Private namespace target: g1_recon_retarget_lock_release_recursive.
 */
#include <stdint.h>
#include "../../headers/g1_log.h"

extern __attribute__((noreturn)) void assert_post_action(uint32_t, uint32_t);
extern int k_mutex_unlock(unsigned int);

#define g1_recon_retarget_lock_release_recursive g1_recon_retarget_lock_release_recursive
void g1_recon_retarget_lock_release_recursive(unsigned long lock) {
    if (lock == 0u) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f23d4) /*=0xf23d4*/, ((unsigned long)"WEST_TOPDIR/zephyr/lib/libc/newlib/libc-hooks.c") /*=0xf22d5*/, 0x1c2u);
        assert_post_action(((unsigned long)"WEST_TOPDIR/zephyr/lib/libc/newlib/libc-hooks.c") /*=0xf22d5*/, 0x1c2u);
    }
    (void)k_mutex_unlock(lock);
}
