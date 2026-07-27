#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007fa7a @ 0x0007fa7a
 * public-name: audio_codec_set_reg16_bit7
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_reg_op_dispatch              <= FUN_0007f97c @ 0x0007f97c
 *   audio_codec_bus_write                    <= FUN_0007f98a @ 0x0007f98a
 *   audio_codec_set_reg16_bit7               <= FUN_0007fa7a @ 0x0007fa7a
 */
/* Reconstructed FUN_0007fa7a @ 0x7fa7a  (parity: 300/300 trials, PROVEN) */

extern int audio_codec_reg_op_dispatch(unsigned int, unsigned int, void*, unsigned int, unsigned int);
extern void audio_codec_bus_write(unsigned long*, unsigned long, unsigned long, unsigned long);

void audio_codec_set_reg16_bit7(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    int iVar1;
    unsigned int local_14;
    unsigned int uStack_10;
    local_14 = param_2;
    uStack_10 = param_3;
    iVar1 = audio_codec_reg_op_dispatch(param_1, 0x16, &local_14, 1, param_1);
    if (iVar1 == 0) {
        unsigned char b = (unsigned char)local_14;
        b = (b & 0x7f) | (unsigned char)((param_2 & 1) << 7);
        local_14 = (local_14 & 0xffffff00U) | b;
        audio_codec_bus_write(param_1, 0x16, &local_14, 1);
    }
    return;
}
