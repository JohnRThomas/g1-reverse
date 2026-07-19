#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_audio_codec_bus_ctx__param_0542        [param_0542; G1-original]
 * Raw function identity: 0x0007f97c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007f97c @ 0x0007f97c
 * public-name: audio_codec_reg_op_dispatch
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_reg_op_dispatch              <= FUN_0007f97c @ 0x0007f97c
 */
/* FUN_0007f97c @ 0x7f97c: indirect tail-dispatch through the object's callback slot. */
#include <stdint.h>
typedef int32_t (*callback_t)(uint32_t, uint32_t, uint32_t, uint32_t);

int32_t audio_codec_reg_op_dispatch(uint8_t *object, uint32_t arg1, uint32_t arg2,
                     uint32_t arg3)
{
    callback_t callback = *(callback_t *)(object + 4);
    return callback(*(uint32_t *)(object + 12), arg1, arg2, arg3);
}
