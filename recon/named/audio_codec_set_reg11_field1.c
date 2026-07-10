/* named: audio_codec_set_reg11_field1 */
/* Reconstructed audio_codec_set_reg11_field1 @ 0x7f9c6  (parity: 300/300 trials, PROVEN) */

extern int audio_codec_bus_read_trampoline(unsigned int, unsigned int, void*, unsigned int, unsigned int);
extern void audio_codec_bus_write_trampoline(unsigned int, unsigned int, void*, unsigned int);

void audio_codec_set_reg11_field1(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    int iVar1;
    unsigned int local_14;
    unsigned int uStack_10;
    local_14 = param_2;
    uStack_10 = param_3;
    iVar1 = audio_codec_bus_read_trampoline(param_1, 0x11, &local_14, 1, param_1);
    if (iVar1 == 0) {
        unsigned char b = (unsigned char)local_14;
        b = (b & 0xf1) | (unsigned char)((param_2 & 7) << 1);
        local_14 = (local_14 & 0xffffff00U) | b;
        audio_codec_bus_write_trampoline(param_1, 0x11, &local_14, 1);
    }
    return;
}

