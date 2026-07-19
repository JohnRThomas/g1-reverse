#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_device_info_persist_store__param_0044  [param_0044; G1-original]
 * Raw function identity: 0x00023230.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00023230 @ 0x00023230
 * public-name: device_info_register_persistent_fields
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   device_info_register_persistent_fields   <= FUN_00023230 @ 0x00023230
 * address symbols (name @ address):
 *   rodata_9e1de                             @ 0x0009e1de
 *   rodata_9e201                             @ 0x0009e201
 *   rodata_9e20e                             @ 0x0009e20e
 *   rodata_9e21f                             @ 0x0009e21f
 *   rodata_9e230                             @ 0x0009e230
 *   rodata_9e23c                             @ 0x0009e23c
 *   rodata_9e259                             @ 0x0009e259
 */
/* Reconstructed FUN_00023230 @ 0x23230. */
#include <stdint.h>

typedef uint32_t (*emit_fn)(uint32_t format, ...);

uint32_t device_info_register_persistent_fields(uint8_t *state, uint32_t unused_2,
                      uint32_t unused_3, uint32_t first_extra)
{
    emit_fn emit;
    (void)unused_2;
    (void)unused_3;

    emit = *(emit_fn *)(state + 0x1040);
    emit(((unsigned long)&rodata_9e1de) /*=0x9e1de*/, *(uint32_t *)(state + 0xfec), 0x6a,
         (uint32_t)(uintptr_t)emit, first_extra);
    emit = *(emit_fn *)(state + 0x1040);
    emit(((unsigned long)&rodata_9e201) /*=0x9e201*/, *(uint32_t *)(state + 0xff0), 7);
    emit = *(emit_fn *)(state + 0x1040);
    emit(((unsigned long)&rodata_9e21f) /*=0x9e21f*/, state + 0xed5, 1);
    emit = *(emit_fn *)(state + 0x1040);
    emit(((unsigned long)&rodata_9e230) /*=0x9e230*/, state + 0xf60, 1);
    emit = *(emit_fn *)(state + 0x1040);
    emit(((unsigned long)&rodata_9e23c) /*=0x9e23c*/, state + 0xfea, 1);
    emit = *(emit_fn *)(state + 0x1040);
    emit(((unsigned long)&rodata_9e259) /*=0x9e259*/, state + 0xef4, 1);
    emit = *(emit_fn *)(state + 0x1040);
    emit(((unsigned long)&rodata_9e20e) /*=0x9e20e*/, state + 0x1050, 4);
    return 0;
}
