/* readable reconstruction; identity: FUN_0004c254 @ 0x0004c254
 * public-name: delay_busy_wait_usec
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   delay_busy_wait_usec                     <= FUN_0004c254 @ 0x0004c254
 * address symbols (name @ address):
 *   g_20002bb8                               @ 0x20002bb8
 */
/* Reconstructed FUN_0004c254 @ 0x4c254
 * CFG_VERIFY_CALL_ARITIES=1
 * Readable identity: delay_scaled_busy_wait.
 * Raw/address backmap: delay_scaled_busy_wait <= FUN_0004c254 @ 0x0004c254.
 */

#include <stdint.h>

typedef void (*busy_wait_fn_t)(uint32_t cycles);

void delay_busy_wait_usec(uint32_t usec)
{
    volatile uint32_t *const cycles_per_second =
        (volatile uint32_t *)0x20002bb8UL;
    /* P4 iteration 15: the literal 0x00088841 was a RAW ORIGINAL-IMAGE Thumb
     * address (the uncatalogued 6-byte busy-wait kernel `subs r0,#3 ; bhi ; bx lr`
     * at 0x88840, reached from nowhere else in the image).  Our build puts
     * unrelated rodata there, so the `bx` executed data.  MEASURED (iteration 15,
     * g1-i15d, 0.15 s): main -> jdb_panel_init -> panel_init ->
     * projector_reset_sequence -> delay_ms -> delay_scaled_busy_wait ->
     * delay_busy_wait_usec -> pc 0x88840 -> "Attempt to execute undefined
     * instruction" -> ZEPHYR FATAL ERROR 36 -> reset.  Same sub-class as
     * iteration 14 section 14.3: a hardcoded numeric literal that no PROVIDE can
     * reach, so the consumer has to NAME the symbol. */
    busy_wait_fn_t const busy_wait = (busy_wait_fn_t)ADDR_coredep_delay_cycles_THUMB;

    if (usec != 0U) {
        busy_wait(usec * (*cycles_per_second / 1000000U));
    }
}
