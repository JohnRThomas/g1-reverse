/* named: audio_codec_read_trim_word */
/* Reconstructed audio_codec_read_trim_word @ 0x7fc04  (parity: 300/300 trials, PROVEN) */

extern int audio_codec_select_page(unsigned int a, unsigned int b);
extern int audio_codec_bus_read_trampoline(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

int audio_codec_read_trim_word(unsigned int param_1, unsigned int param_2)
{
    int iVar1, iVar2, iVar3;
    iVar1 = audio_codec_select_page(param_1, 2);
    iVar2 = audio_codec_bus_read_trampoline(param_1, 0x46, param_2, 2);
    iVar3 = audio_codec_select_page(param_1, 0);
    return iVar3 + iVar1 + iVar2;
}

