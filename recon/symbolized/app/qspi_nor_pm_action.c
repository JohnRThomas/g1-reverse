#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00060b48 @ 0x00060b48
 * public-name: qspi_nor_pm_action
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   qspi_nor_acquire                         <= FUN_00060a10 @ 0x00060a10
 *   qspi_nor_send_cinstr                     <= FUN_00060ab0 @ 0x00060ab0
 *   qspi_nor_pm_action                       <= FUN_00060b48 @ 0x00060b48
 *   nrfx_qspi_init                           <= FUN_00066994 @ 0x00066994
 *   nrfx_qspi_mem_busy_check                 <= FUN_00066ae0 @ 0x00066ae0
 *   audio_hw_lock_is_busy                    <= FUN_0007ef2e @ 0x0007ef2e
 *   audio_apply_config_cmd_0xab              <= FUN_0008397e @ 0x0008397e
 *   delay_scaled_busy_wait                   <= FUN_00086384 @ 0x00086384
 * address symbols (name @ address):
 *   rodata_838cb                             @ 0x000838cb
 */
/* Reconstructed FUN_00060b48 @ 0x60b48  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern int qspi_nor_acquire(int);
extern void FUN_00060a5c(int);
extern int qspi_nor_send_cinstr(int,void*,int,int,int);
extern int nrfx_qspi_init(int,int,int);
extern int nrfx_qspi_mem_busy_check(void);
extern void FUN_00066b24(void);
extern int audio_hw_lock_is_busy(void);
extern int FUN_000838dc(int,int);
extern int audio_apply_config_cmd_0xab(int);
extern void delay_scaled_busy_wait(int);

uint qspi_nor_pm_action(int param_1, int param_2, unsigned param_3, unsigned param_4){
    int iVar5 = *(int*)(param_1+0x10);
    int iVar4 = *(int*)(param_1+4);
    int iVar3 = param_1;
    volatile int local[3];
    int iVar1 = audio_hw_lock_is_busy();
    if (iVar1 == 0){
        uint uVar2;
        if (param_2 != 0){
            if (param_2 != 1) return 0xffffff7a;
            uVar2 = FUN_000838dc(*(int*)(iVar4+0x34), 0);
            if ((int)uVar2 < 0) return uVar2;
            iVar3 = nrfx_qspi_init(iVar4, ((unsigned long)&rodata_838cb) /*=0x838cb*/, iVar5);
            if (iVar3 != 0x0bad0000) return 0xfffffffb;
            uVar2 = audio_apply_config_cmd_0xab(param_1);
            if ((int)uVar2 < 0) return uVar2;
            FUN_00060a5c(param_1);
            return 0;
        }
        uVar2 = qspi_nor_acquire(param_1);
        if ((int)uVar2 < 0) return uVar2;
        uVar2 = *(uint8_t*)(iVar5+0x60);
        if (uVar2==0){
            iVar1 = nrfx_qspi_mem_busy_check();
            if (iVar1 == 0x0bad0000){
                local[0]=0xb9; local[1]=uVar2; local[2]=uVar2;
                uVar2 = qspi_nor_send_cinstr(param_1, (void*)local, 0, 0xb9, iVar3);
                if ((int)uVar2 < 0) return uVar2;
                delay_scaled_busy_wait(10);
                FUN_00066b24();
                uVar2 = FUN_000838dc(*(int*)(iVar4+0x34), 1);
                return uVar2 & ((int)uVar2 >> 0x1f);
            }
        }
    }
    return 0xfffffff0;
}
