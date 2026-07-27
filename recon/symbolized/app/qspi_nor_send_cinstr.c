#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00060ab0 @ 0x00060ab0
 * public-name: qspi_nor_send_cinstr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   qspi_get_zephyr_ret_code                 <= FUN_00060990 @ 0x00060990
 *   qspi_nor_send_cinstr                     <= FUN_00060ab0 @ 0x00060ab0
 *   nrfx_qspi_cinstr_xfer                    <= FUN_000669f4 @ 0x000669f4
 *   qspi_log_forward                         <= FUN_000838d6 @ 0x000838d6
 *   audio_i2s_stop_and_reset_channels        <= FUN_00083906 @ 0x00083906
 *   audio_i2s_start_channels                 <= FUN_0008392e @ 0x0008392e
 * address symbols (name @ address):
 *   rodata_88270                             @ 0x00088270
 *   rodata_f5c20                             @ 0x000f5c20
 */
/* Reconstructed FUN_00060ab0 @ 0x60ab0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern int qspi_get_zephyr_ret_code(int);
#define g1_recon_nrfx_qspi_cinstr_xfer nrfx_qspi_cinstr_xfer
extern u32 g1_recon_nrfx_qspi_cinstr_xfer(void*,u32,u32);
extern void qspi_log_forward(u32,u32,void*);
extern void audio_i2s_stop_and_reset_channels(u32);
extern void audio_i2s_start_channels(void*);
int qspi_nor_send_cinstr(void*param_1, unsigned char*param_2, unsigned char param_3) {
    int iVar1, iVar2; u32 uVar4, uVar5, uVar6; u32 local_24;
    u32 *puVar3;
    puVar3 = *(u32**)(param_2+4);
    if(puVar3==0){ iVar2=0; uVar4=0; }
    else { uVar4=puVar3[0]; iVar2=(int)puVar3[1]; }
    puVar3 = *(u32**)(param_2+8);
    if(puVar3==0){ iVar1=0; uVar5=0; }
    else {
        uVar5=puVar3[0]; iVar1=(int)puVar3[1];
        if(iVar1!=0 && iVar2!=0){
            if(iVar1!=iVar2) return 0xffffffea;
            local_24 = iVar2 + 1;
            goto LAB;
        }
    }
    local_24 = iVar2 + 1 + iVar1;
LAB: ;
    u8 local_20 = *param_2;
    if(9 < local_24){
        u32 buf[4];
        buf[0]=4; buf[1]=((unsigned long)&rodata_f5c20) /*=0xf5c20*/; buf[2]=*param_2; buf[3]=local_24;
        qspi_log_forward(((unsigned long)&rodata_88270) /*=0x88270*/, 0x2080, buf);
        return 0xffffffea;
    }
    struct { u8 b0; u8 b1; uint16_t h2; u8 b4; u8 b5; } frame;
    frame.b0 = local_20;
    frame.b1 = (u8)local_24;
    frame.h2 = 0x0101;
    frame.b4 = 0;
    frame.b5 = param_3;
    audio_i2s_stop_and_reset_channels(param_1);
    uVar6 = g1_recon_nrfx_qspi_cinstr_xfer(&frame, uVar4, uVar5);
    audio_i2s_start_channels(param_1);
    uVar6 = qspi_get_zephyr_ret_code(uVar6);
    return uVar6;
}
