/* Full reconstruction FUN_0007f97c @ 0x7f97c (exact extent 14 bytes). */
#include <stdint.h>
void FUN_0007f97c(uint8_t *object)
{
    void (*callback)(uint32_t) = *(void (**)(uint32_t))(object + 4);
    callback(*(uint32_t *)(object + 12));
}
