#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_param_0299_driver_data_collision__param_0299 [param_0299; G1-original]
 * Raw function identity: 0x00060b48.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00060b48 @ 0x00060b48
 * public-name: qspi_nor_pm_action
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   qspi_nor_acquire                         <= FUN_00060a10 @ 0x00060a10
 *   qspi_nor_suspend_bus                     <= FUN_00060a5c @ 0x00060a5c
 *   qspi_nor_send_cinstr                     <= FUN_00060ab0 @ 0x00060ab0
 *   qspi_nor_pm_action                       <= FUN_00060b48 @ 0x00060b48
 *   nrfx_qspi_init                           <= FUN_00066994 @ 0x00066994
 *   nrfx_qspi_mem_busy_check                 <= FUN_00066ae0 @ 0x00066ae0
 *   nrfx_qspi_uninit                         <= FUN_00066b24 @ 0x00066b24
 *   audio_hw_lock_is_busy                    <= FUN_0007ef2e @ 0x0007ef2e
 *   qspi_pinctrl_apply_state                 <= FUN_000838dc @ 0x000838dc
 *   audio_apply_config_cmd_0xab              <= FUN_0008397e @ 0x0008397e
 *   delay_scaled_busy_wait                   <= FUN_00086384 @ 0x00086384
 * address symbols (name @ address):
 *   rodata_838cb                             @ 0x000838cb
 */
/* Reconstructed FUN_00060b48 @ 0x60b48  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern int qspi_nor_acquire(int);
extern void qspi_nor_suspend_bus(unsigned char*);
extern int qspi_nor_send_cinstr(int,void*,int,int,int);
#define g1_recon_nrfx_qspi_init nrfx_qspi_init
extern int g1_recon_nrfx_qspi_init(int,int,int);
#define g1_recon_nrfx_qspi_mem_busy_check nrfx_qspi_mem_busy_check
extern int g1_recon_nrfx_qspi_mem_busy_check(void);
extern void nrfx_qspi_uninit(void);
extern int audio_hw_lock_is_busy(unsigned long);
extern int qspi_pinctrl_apply_state(int,int);
extern int audio_apply_config_cmd_0xab(unsigned int);
extern void delay_scaled_busy_wait(int);

uint qspi_nor_pm_action(int param_1, int param_2, unsigned param_3, unsigned param_4){
    int iVar5 = *(int*)(param_1+0x10);
    int iVar4 = *(int*)(param_1+4);
    int iVar3 = param_1;
    volatile int local[3];
    int iVar1 = audio_hw_lock_is_busy(param_1);
    if (iVar1 == 0){
        uint uVar2;
        if (param_2 != 0){
            if (param_2 != 1) return 0xffffff7a;
            uVar2 = qspi_pinctrl_apply_state(*(int*)(iVar4+0x34), 0);
            if ((int)uVar2 < 0) return uVar2;
            iVar3 = g1_recon_nrfx_qspi_init(iVar4, ((unsigned long)&rodata_838cb) /*=0x838cb*/, iVar5);
            if (iVar3 != 0x0bad0000) return 0xfffffffb;
            uVar2 = audio_apply_config_cmd_0xab(param_1);
            if ((int)uVar2 < 0) return uVar2;
            qspi_nor_suspend_bus(param_1);
            return 0;
        }
        uVar2 = qspi_nor_acquire(param_1);
        if ((int)uVar2 < 0) return uVar2;
        uVar2 = *(uint8_t*)(iVar5+0x60);
        if (uVar2==0){
            iVar1 = g1_recon_nrfx_qspi_mem_busy_check();
            if (iVar1 == 0x0bad0000){
                local[0]=0xb9; local[1]=uVar2; local[2]=uVar2;
                uVar2 = qspi_nor_send_cinstr(param_1, (void*)local, 0, 0xb9, iVar3);
                if ((int)uVar2 < 0) return uVar2;
                delay_scaled_busy_wait(10);
                nrfx_qspi_uninit();
                uVar2 = qspi_pinctrl_apply_state(*(int*)(iVar4+0x34), 1);
                return uVar2 & ((int)uVar2 >> 0x1f);
            }
        }
    }
    return 0xfffffff0;
}
