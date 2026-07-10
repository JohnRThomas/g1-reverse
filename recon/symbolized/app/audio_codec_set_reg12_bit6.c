#include "g1_app_symbols.h"
/* named: audio_codec_set_reg12_bit6 */
/* Reconstructed audio_codec_set_reg12_bit6 @ 0x7f9f4  (parity: 300/300 trials, PROVEN) */

extern int audio_codec_bus_read_trampoline(unsigned int, unsigned int, void*, unsigned int, unsigned int);
extern void audio_codec_bus_write_trampoline(unsigned int, unsigned int, void*, unsigned int);

void audio_codec_set_reg12_bit6(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    int iVar1;
    unsigned int local_14;
    unsigned int uStack_10;
    local_14 = param_2;
    uStack_10 = param_3;
    iVar1 = audio_codec_bus_read_trampoline(param_1, 0x12, &local_14, 1, param_1);
    if (iVar1 == 0) {
        unsigned char b = (unsigned char)local_14;
        b = (b & 0xbf) | (unsigned char)((param_2 & 1) << 6);
        local_14 = (local_14 & 0xffffff00U) | b;
        audio_codec_bus_write_trampoline(param_1, 0x12, &local_14, 1);
    }
    return;
}

