#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_app_id_config_stream_ctx__param_0159   [param_0159; G1-original]
 * Raw function identity: 0x0007f7c8.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007f7c8 @ 0x0007f7c8
 * public-name: invoke_object_callback_864
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   invoke_object_callback_864               <= FUN_0007f7c8 @ 0x0007f7c8
 */
/* Full reconstruction FUN_0007f7c8 @ 0x7f7c8 (exact extent 10 bytes). */
#include <stdint.h>
void invoke_object_callback_864(uint8_t *object)
{
    void (*callback)(uint8_t *) = *(void (**)(uint8_t *))(object + 0x864);
    if (callback != 0) callback(object);
}
