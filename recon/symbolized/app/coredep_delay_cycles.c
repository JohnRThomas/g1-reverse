#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00088840 @ 0x00088840
 * public-name: coredep_delay_cycles
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   coredep_delay_cycles                     <= FUN_00088840 @ 0x00088840
 */
/* Full reconstruction FUN_00088840 @ 0x88840 (exact 6-byte extent).
 *
 * P4 iteration 15.  Ghidra never catalogued this leaf: its only reference in
 * the whole image is the literal 0x00088841 in FUN_0004c254
 * (`delay_busy_wait_usec`), which loads it, ORs in the Thumb bit and `bx`es
 * to it.  The shipped bytes are
 *     3803    subs r0, r0, #3
 *     d8fd    bhi  .-2
 *     4770    bx   lr
 * i.e. nrfx's `nrfx_coredep_delay_us` three-cycle busy-wait kernel; the caller
 * has already converted microseconds to CPU cycles.
 *
 * Expressed as inline asm because the loop's exit condition is the unsigned
 * BHI on the SUBS flags, which C's `while (n > 3)` does not reproduce for the
 * wrap-around case, and because this must stay exactly three instructions.
 * `__asm__` (not bare `asm`) keeps it valid under the application build's
 * -std=c99.
 */

void coredep_delay_cycles(unsigned int cycles)
{
	__asm__ volatile("1:\tsubs\t%0, %0, #3\n\t"
			 "bhi\t1b"
			 : "+r"(cycles)
			 :
			 : "cc");
}
