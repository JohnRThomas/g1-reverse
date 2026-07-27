/* readable reconstruction; identity: FUN_0007f97c @ 0x0007f97c
 * public-name: audio_codec_reg_op_dispatch
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_reg_op_dispatch              <= FUN_0007f97c @ 0x0007f97c
 */
/* FUN_0007f97c @ 0x7f97c: indirect tail-dispatch through the object's callback slot. */
#include <stdint.h>
typedef int32_t (*callback_t)(uint32_t, uint32_t, uint32_t, uint32_t);

int audio_codec_reg_op_dispatch(unsigned int object, unsigned int arg1, void*arg2, unsigned int arg3) {
    callback_t callback = *(callback_t *)(object + 4);
    return callback(*(uint32_t *)(object + 12), arg1, arg2, arg3);
}
