/* readable reconstruction; identity: FUN_0007fc04 @ 0x0007fc04
 * public-name: audio_codec_read_trim_word
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_reg_op_dispatch              <= FUN_0007f97c @ 0x0007f97c
 *   audio_codec_select_page                  <= FUN_0007fb20 @ 0x0007fb20
 *   audio_codec_read_trim_word               <= FUN_0007fc04 @ 0x0007fc04
 */
/* Reconstructed FUN_0007fc04 @ 0x7fc04  (parity: 300/300 trials, PROVEN) */

extern int audio_codec_select_page(unsigned int a, unsigned int b);
extern int audio_codec_reg_op_dispatch(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

int audio_codec_read_trim_word(unsigned int param_1, unsigned int param_2)
{
    int iVar1, iVar2, iVar3;
    iVar1 = audio_codec_select_page(param_1, 2);
    iVar2 = audio_codec_reg_op_dispatch(param_1, 0x46, param_2, 2);
    iVar3 = audio_codec_select_page(param_1, 0);
    return iVar3 + iVar1 + iVar2;
}
