/* Full reconstruction FUN_0007f7c8 @ 0x7f7c8 (exact extent 10 bytes). */
#include <stdint.h>
void FUN_0007f7c8(uint8_t *object)
{
    void (*callback)(uint8_t *) = *(void (**)(uint8_t *))(object + 0x864);
    if (callback != 0) callback(object);
}
