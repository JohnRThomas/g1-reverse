#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_audio_codec_bus_ctx__param_0542        [param_0542; G1-original]
 * Raw function identity: 0x0007f98a.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007f98a @ 0x0007f98a
 * public-name: audio_codec_bus_write
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_bus_write                    <= FUN_0007f98a @ 0x0007f98a
 */
/* Full reconstruction FUN_0007f98a @ 0x7f98a (exact extent 14 bytes). */
#include <stdint.h>
void audio_codec_bus_write(uint32_t *object, uint32_t r1, uint32_t r2, uint32_t r3)
{
    void (*callback)(uint32_t, uint32_t, uint32_t, uint32_t) =
        (void (*)(uint32_t, uint32_t, uint32_t, uint32_t))(uintptr_t)object[0];
    callback(object[3], r1, r2, r3);
}
