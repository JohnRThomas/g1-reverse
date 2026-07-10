/* named: audio_codec_set_dual_reg14_reg15 */
/* Reconstructed audio_codec_set_dual_reg14_reg15 @ 0x7fa22  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int audio_codec_bus_read_trampoline(unsigned param_1, int, void*, int);
extern int audio_codec_bus_write_trampoline(unsigned param_1, int, void*, int);
void audio_codec_set_dual_reg14_reg15(unsigned param_1, unsigned param_2, unsigned param_3){
    unsigned local_18 = param_1;
    unsigned local_14 = param_2;
    unsigned uStack_10 = param_3;
    (void)uStack_10;
    int iVar1 = audio_codec_bus_read_trampoline(param_1, 0x14, &local_18, 1);
    if (iVar1 != 0) return;
    { unsigned char *p = (unsigned char*)&local_18;
      *p = (*p & 0x7f) | (((param_2 >> 1) & 1) << 7); }
    iVar1 = audio_codec_bus_write_trampoline(param_1, 0x14, &local_18, 1);
    if (iVar1 != 0) return;
    iVar1 = audio_codec_bus_read_trampoline(param_1, 0x15, &local_14, 1);
    if (iVar1 != 0) return;
    { unsigned char *p = (unsigned char*)&local_14;
      *p = (*p & 0xef) | ((param_2 & 1) << 4); }
    audio_codec_bus_write_trampoline(param_1, 0x15, &local_14, 1);
}

