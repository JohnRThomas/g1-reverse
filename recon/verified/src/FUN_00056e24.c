/* Reconstructed FUN_00056e24 @ 0x00056e24 (bt_conn_cb_register).
 * Exact configured Zephyr conn.c owner; extent 0x0a.
 */
#include <stdint.h>
void FUN_00056e24(uint8_t *callback)
{
    uintptr_t previous = *(volatile uintptr_t *)0x2000ad1cU;
    *(volatile uintptr_t *)0x2000ad1cU = (uintptr_t)callback;
    *(uintptr_t *)(callback + 0x20) = previous;
}
