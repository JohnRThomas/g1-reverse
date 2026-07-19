/* readable reconstruction; identity: FUN_0007fb20 @ 0x0007fb20
 * public-name: audio_codec_select_page
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_bus_write                    <= FUN_0007f98a @ 0x0007f98a
 *   audio_codec_select_page                  <= FUN_0007fb20 @ 0x0007fb20
 */
/* Reconstructed FUN_0007fb20 @ 0x7fb20  (parity: 300/300 trials, PROVEN) */

extern int audio_codec_bus_write(unsigned int, unsigned int, void *, unsigned int, unsigned int);

void audio_codec_select_page(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned char local_c;
  volatile unsigned int uStack_8;
  uStack_8 = param_3;
  local_c = (unsigned char)((param_2 & 3) << 6);
  audio_codec_bus_write(param_1, 1, &local_c, 1, param_1);
  return;
}
