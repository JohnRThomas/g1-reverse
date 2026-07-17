#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007fc72 @ 0x0007fc72
 * public-name: audio_codec_set_gain_ch0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_read_trim_word               <= FUN_0007fc04 @ 0x0007fc04
 *   audio_codec_read_gain_step_mode          <= FUN_0007fc2c @ 0x0007fc2c
 *   audio_codec_set_gain_ch0                 <= FUN_0007fc72 @ 0x0007fc72
 */
/* Reconstructed FUN_0007fc72 @ 0x7fc72  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0007f97c(uint32_t,int,void*,int);
extern int FUN_0007f98a(uint32_t,int,void*,int);
extern int audio_codec_read_trim_word(uint32_t,void*);
extern int audio_codec_read_gain_step_mode(uint32_t,void*);
int audio_codec_set_gain_ch0(uint32_t param_1, uint32_t param_2){
    uint32_t local_18 = param_1;
    uint32_t local_14 = param_2;
    int iVar1 = audio_codec_read_trim_word(param_1, &local_14);
    if(iVar1==0){
        if((local_14 & 0xffff) != 0){
            iVar1 = audio_codec_read_gain_step_mode(param_1, (uint8_t*)&local_18 + 3);
            if(iVar1!=0) return iVar1;
            switch(local_18 >> 0x18){
            case 0: if(param_2==0) param_2=1; break;
            case 1: if(param_2<2) param_2=2; break;
            case 2: if(param_2<3) param_2=3; break;
            case 3: if(param_2<4) param_2=4; break;
            }
        }
        int iVar2 = FUN_0007f97c(param_1, 0x10, &local_18, 1);
        local_18 = (local_18 & ~0xffu) | ((local_18 & 0xf) | ((param_2 & 0xf)<<4));
        iVar1 = FUN_0007f98a(param_1, 0x10, &local_18, 1);
        iVar1 = iVar1 + iVar2;
    }
    return iVar1;
}
