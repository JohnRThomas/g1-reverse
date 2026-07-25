/* Reconstructed FUN_0007d244 @ 0x7d244  (uncatalogued: Ghidra folded it into the
 * tail of set_device_sync_timestamp (0x7d230)).
 *
 * Handler slot of `g_screen_render_table` (shipped `.data` at 0x20002430, the
 * 16-byte-stride screen table `panel_render_screen_dispatch` indexes) for
 * screen id 8.  That table word is the only referrer in the whole image.
 *
 * The shipped bytes are exactly four: `2000  movs r0, #0` / `4770  bx lr`.
 * PROOF: the compiled .text is `20004770`, byte-identical to the shipped
 * 0x7d244.
 */

int FUN_0007d244(void)
{
  return 0;
}
