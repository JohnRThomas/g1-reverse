#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000510fc @ 0x000510fc
 * public-name: g1_recon_retarget_lock_acquire_recursive
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_recon_retarget_lock_acquire_recursive <= FUN_000510fc @ 0x000510fc
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f22d5                             @ 0x000f22d5   [INLINED -- G6 literal batch]
 *   rodata_f23d4                             @ 0x000f23d4
 */
/* Retained asserting recursive-lock acquire hook @ 0x000510fc.
 * Raw/address back-map: FUN_000510fc / 0x000510fc.
 * Private namespace target: g1_recon_retarget_lock_acquire_recursive.
 */
#include <stdint.h>

typedef struct {
    int64_t ticks;
} g1_k_timeout_t;

extern __attribute__((noreturn)) void assert_post_action(uint32_t, uint32_t);
extern void printk(uint32_t, uint32_t, uint32_t, uint32_t);
extern int k_mutex_lock(uintptr_t lock, g1_k_timeout_t timeout);

#define g1_recon_retarget_lock_acquire_recursive g1_recon_retarget_lock_acquire_recursive
void g1_recon_retarget_lock_acquire_recursive(uintptr_t lock)
{
    if (lock == 0u) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f23d4) /*=0xf23d4*/, ((unsigned long)"WEST_TOPDIR/zephyr/lib/libc/newlib/libc-hooks.c") /*=0xf22d5*/, 0x1a6u);
        assert_post_action(((unsigned long)"WEST_TOPDIR/zephyr/lib/libc/newlib/libc-hooks.c") /*=0xf22d5*/, 0x1a6u);
    }
    (void)k_mutex_lock(lock, (g1_k_timeout_t){ .ticks = -1 });
}
