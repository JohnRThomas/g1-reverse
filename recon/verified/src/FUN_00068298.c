/* Reconstructed FUN_00068298 @ 0x68298
 * CFG_VERIFY_CALL_ARITIES=1
 * Readable identity: metal_sys_init (libmetal Zephyr system backend).
 * Raw/address backmap: metal_sys_init <= FUN_00068298 @ 0x00068298.
 */

#include <stdint.h>

extern int FUN_00068170(void *bus); /* metal_bus_register */

int FUN_00068298(const void *params)
{
    (void)params;
    (void)FUN_00068170((void *)0x20002c3cUL);
    return 0;
}
