/* readable reconstruction; identity: FUN_0007f998 @ 0x0007f998
 * public-name: audio_codec_set_reg10_field2
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_set_reg10_field2             <= FUN_0007f998 @ 0x0007f998
 */
/* Reconstructed FUN_0007f998 @ 0x7f998  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007f97c(unsigned int, unsigned int, void*, unsigned int, unsigned int);
extern void FUN_0007f98a(unsigned int, unsigned int, void*, unsigned int);

void audio_codec_set_reg10_field2(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    int iVar1;
    unsigned int local_14;
    unsigned int uStack_10;
    local_14 = param_2;
    uStack_10 = param_3;
    iVar1 = FUN_0007f97c(param_1, 0x10, &local_14, 1, param_1);
    if (iVar1 == 0) {
        unsigned char b = (unsigned char)local_14;
        b = (b & 0xf3) | (unsigned char)((param_2 & 3) << 2);
        local_14 = (local_14 & 0xffffff00U) | b;
        FUN_0007f98a(param_1, 0x10, &local_14, 1);
    }
    return;
}
