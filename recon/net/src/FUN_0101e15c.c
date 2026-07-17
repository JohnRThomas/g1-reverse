/* apply_active_handle_context_update @ 0x0101e15c (CFG parity: 5/5, PROVEN)
 * Raw provenance: FUN_0101e15c is the four-byte Thumb tail branch
 * `b.w 0x0101e0a4`.  Exact ownership is [0x0101e15c,0x0101e160);
 * FUN_0101e160 begins the next independent push-prologue function.
 *
 * The sole direct owner is apply_handle_byte_update/FUN_0102946c, which has
 * already resolved the typed entry and its active context.  This veneer
 * preserves all three AAPCS arguments and the transition helper's result.
 */
#include <stdint.h>

extern unsigned FUN_0101e0a4(uint8_t *context, uint8_t *entry,
                             uint8_t value);

/* Readable identities retain reversible raw symbols without an asm body. */
#define apply_context_state_transition FUN_0101e0a4
#define apply_active_handle_context_update FUN_0101e15c

unsigned apply_active_handle_context_update(uint8_t *context,
                                            uint8_t *entry,
                                            uint8_t value)
{
    return apply_context_state_transition(context, entry, value);
}
