/* Full reconstruction FUN_0007f98a @ 0x7f98a (exact extent 14 bytes). */
#include <stdint.h>
void FUN_0007f98a(uint32_t *object)
{
    void (*callback)(uint32_t) = (void (*)(uint32_t))(uintptr_t)object[0];
    callback(object[3]);
}

