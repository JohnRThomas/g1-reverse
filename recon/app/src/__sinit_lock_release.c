/* __sinit_lock_release @ 0x00076bc0; raw FUN_00076bc0 */
#include <stdint.h>

extern void __retarget_lock_release_recursive(void *lock); /* FUN_00051134 */

void __sinit_lock_release(void)
{
    __retarget_lock_release_recursive((void *)0x20003818u);
}
