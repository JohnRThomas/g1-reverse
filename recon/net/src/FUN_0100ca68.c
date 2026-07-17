/* net-core FUN_0100ca68 @ 0x100ca68  (CFG-directed candidate) */
#include <stdint.h>

/* Raw back-map: FUN_0100ca68 @ 0x0100ca68, exact extent 0x14 bytes. */
void *FUN_0100ca68(uint32_t index)
{
    volatile const uint8_t *const table_state =
        (volatile const uint8_t *)0x21000d18u;

    if (index >= table_state[1]) {
        return 0;
    }
    return (void *)(uintptr_t)(0x21000d18u + 0x82u + index * 0x10u);
}
