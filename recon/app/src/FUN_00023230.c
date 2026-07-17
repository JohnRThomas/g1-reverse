/* Reconstructed FUN_00023230 @ 0x23230. */
#include <stdint.h>

typedef uint32_t (*emit_fn)(uint32_t format, ...);

uint32_t FUN_00023230(uint8_t *state, uint32_t unused_2,
                      uint32_t unused_3, uint32_t first_extra)
{
    emit_fn emit;
    (void)unused_2;
    (void)unused_3;

    emit = *(emit_fn *)(state + 0x1040);
    emit(0x0009e1de, *(uint32_t *)(state + 0xfec), 0x6a,
         (uint32_t)(uintptr_t)emit, first_extra);
    emit = *(emit_fn *)(state + 0x1040);
    emit(0x0009e201, *(uint32_t *)(state + 0xff0), 7);
    emit = *(emit_fn *)(state + 0x1040);
    emit(0x0009e21f, state + 0xed5, 1);
    emit = *(emit_fn *)(state + 0x1040);
    emit(0x0009e230, state + 0xf60, 1);
    emit = *(emit_fn *)(state + 0x1040);
    emit(0x0009e23c, state + 0xfea, 1);
    emit = *(emit_fn *)(state + 0x1040);
    emit(0x0009e259, state + 0xef4, 1);
    emit = *(emit_fn *)(state + 0x1040);
    emit(0x0009e20e, state + 0x1050, 4);
    return 0;
}
