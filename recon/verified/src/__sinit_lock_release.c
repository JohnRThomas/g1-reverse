/* __sinit_lock_release @ 0x00076bc0; raw FUN_00076bc0 */
#include <stdint.h>

#define g1_recon_retarget_lock_release_recursive FUN_00051134
extern void g1_recon_retarget_lock_release_recursive(void *lock); /* FUN_00051134@0x00051134 */

void __sinit_lock_release(void)
{
    g1_recon_retarget_lock_release_recursive((void *)0x20003818u);
}
