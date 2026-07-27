/* Retained asserting recursive-lock release hook @ 0x00051134.
 * Raw/address back-map: FUN_00051134 / 0x00051134.
 * Private namespace target: g1_recon_retarget_lock_release_recursive.
 */
#include <stdint.h>

extern __attribute__((noreturn)) void FUN_0007e2ec(uint32_t, uint32_t);
extern void FUN_0007e2fa(unsigned long, ...);
extern int FUN_00072558(uintptr_t lock);

#define g1_recon_retarget_lock_release_recursive FUN_00051134
void g1_recon_retarget_lock_release_recursive(uintptr_t lock)
{
    if (lock == 0u) {
        FUN_0007e2fa(0x00099cbdu, 0x000f23d4u, 0x000f22d5u, 0x1c2u);
        FUN_0007e2ec(0x000f22d5u, 0x1c2u);
    }
    (void)FUN_00072558(lock);
}
