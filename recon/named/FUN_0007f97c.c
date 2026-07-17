/* readable reconstruction; identity: FUN_0007f97c @ 0x0007f97c
 * public-name: FUN_0007f97c
 * durable-map: recon/catalogs/function_names_app.json
 */
/* FUN_0007f97c @ 0x7f97c: indirect tail-dispatch through the object's callback slot. */
#include <stdint.h>
typedef int32_t (*callback_t)(uint32_t, uint32_t, uint32_t, uint32_t);

int32_t FUN_0007f97c(uint8_t *object, uint32_t arg1, uint32_t arg2,
                     uint32_t arg3)
{
    callback_t callback = *(callback_t *)(object + 4);
    return callback(*(uint32_t *)(object + 12), arg1, arg2, arg3);
}
