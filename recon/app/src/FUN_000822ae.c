/* Optional object callback FUN_000822ae @ 0x822ae (14-byte extent). */
#include <stdint.h>
typedef void (*callback_t)(uint8_t *object, uint8_t **holder, uint32_t context);
void FUN_000822ae(uint32_t unused, uint8_t **holder, uint32_t context)
{
    uint8_t *object = *holder;
    callback_t callback = *(callback_t *)(*(uint8_t **)(object + 0x0c) + 0x18);
    if (callback != 0)
        callback(object + 8, holder, context);
}
