/* Reconstructed FUN_0007d0c0 @ 0x7d0c0  (uncatalogued: Ghidra folded it into
 * the tail of read_rtc_counter_ms, 0x7d0aa, declared size 0x3a).
 *
 * The shipped bytes are exactly two: `4770  bx lr` -- a no-op leaf.  It is
 * slot 2 of the ops table the shipped `.data` places at 0x20002408, whose four
 * function pointers `pt_nfc_eeprom_link_init` (0x30b3c) requires to be
 * non-zero; the table's only referrer in the whole image is that .data word.
 *
 * PROOF: the compiled .text is `4770`, byte-identical to the shipped 0x7d0c0.
 */

void FUN_0007d0c0(void)
{
}
