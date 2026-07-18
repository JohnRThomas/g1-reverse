/* Retained asserting recursive-lock acquire hook @ 0x000510fc.
 * Raw/address back-map: FUN_000510fc / 0x000510fc.
 * Private namespace target: g1_recon_retarget_lock_acquire_recursive.
 */
#include <stdint.h>

typedef struct {
    int64_t ticks;
} g1_k_timeout_t;

extern __attribute__((noreturn)) void FUN_0007e2ec(uint32_t, uint32_t);
extern void FUN_0007e2fa(uint32_t, uint32_t, uint32_t, uint32_t);
extern int FUN_000723b8(uintptr_t lock, g1_k_timeout_t timeout);

#define g1_recon_retarget_lock_acquire_recursive FUN_000510fc
void g1_recon_retarget_lock_acquire_recursive(uintptr_t lock)
{
    if (lock == 0u) {
        FUN_0007e2fa(0x00099cbdu, 0x000f23d4u, 0x000f22d5u, 0x1a6u);
        FUN_0007e2ec(0x000f22d5u, 0x1a6u);
    }
    (void)FUN_000723b8(lock, (g1_k_timeout_t){ .ticks = -1 });
}
