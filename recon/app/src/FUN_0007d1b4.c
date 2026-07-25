/* Reconstructed FUN_0007d1b4 @ 0x7d1b4  (uncatalogued: Ghidra folded it into the
 * tail of k_msleep_ticks32768_c (0x7d194)).
 *
 * Handler slot of `g_screen_render_table` (shipped `.data` at 0x20002430, the
 * 16-byte-stride screen table `panel_render_screen_dispatch` indexes) for
 * screen id 4.  That table word is the only referrer in the whole image.
 *
 * The shipped bytes are exactly four: `2000  movs r0, #0` / `4770  bx lr`.
 * PROOF: the compiled .text is `20004770`, byte-identical to the shipped
 * 0x7d1b4.
 */

int FUN_0007d1b4(void)
{
  return 0;
}
