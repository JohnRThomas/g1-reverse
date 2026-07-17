/* readable reconstruction; identity: FUN_00060dd0 @ 0x00060dd0
 * public-name: qspi_nor_erase
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   qspi_get_zephyr_ret_code                 <= FUN_00060990 @ 0x00060990
 *   qspi_nor_log_erase_range_error           <= FUN_000609c4 @ 0x000609c4
 *   qspi_nor_acquire                         <= FUN_00060a10 @ 0x00060a10
 *   qspi_nor_erase                           <= FUN_00060dd0 @ 0x00060dd0
 *   nrfx_qspi_read                           <= FUN_00066bc4 @ 0x00066bc4
 *   audio_stream_stop_and_wait               <= FUN_000838fa @ 0x000838fa
 *   audio_i2s_stop_and_reset_channels        <= FUN_00083906 @ 0x00083906
 *   audio_i2s_start_channels                 <= FUN_0008392e @ 0x0008392e
 *   qspi_nor_write_protection_set            <= FUN_00083954 @ 0x00083954
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 *   rodata_88270                             @ 0x00088270
 *   rodata_f5c9c                             @ 0x000f5c9c
 *   rodata_f5cba                             @ 0x000f5cba
 */
/* Reconstructed FUN_00060dd0 @ 0x60dd0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int qspi_get_zephyr_ret_code(int);
extern int qspi_nor_log_erase_range_error(int,int);
extern int FUN_000609f4(int,int);
extern int qspi_nor_acquire(void);
extern int FUN_00060a5c(int);
extern int nrfx_qspi_read(int,int);
extern int FUN_00072880(int);
extern int FUN_000838d6(int,int,void*);
extern int audio_stream_stop_and_wait(int);
extern int audio_i2s_stop_and_reset_channels(int);
extern int audio_i2s_start_channels(int);
extern int qspi_nor_write_protection_set(int,int);
extern int FUN_0008520c(void);

int qspi_nor_erase(int param_1, unsigned int param_2, unsigned int param_3, int param_4)
{
    int iVar1, iVar2, iVar3;
    unsigned int uVar4;
    int local_38, local_34;
    unsigned int uStack_30, local_2c;
    int uStack_28;

    iVar3 = *(int *)(param_1 + 4);
    uStack_28 = param_4;
    (void)uStack_28;
    if (((int)param_2 < 0) || (*(unsigned int *)(iVar3 + 0x2c) < param_2 + param_3)) {
        iVar3 = qspi_nor_log_erase_range_error(param_2, param_3);
        return iVar3;
    }
    if ((param_3 == 0) || (((param_3 | param_2) & 0xfff) != 0)) {
        return -0x16;
    }
    iVar1 = qspi_nor_acquire();
    if (iVar1 == 0) {
        audio_stream_stop_and_wait(*(int *)(param_1 + 0x10));
        iVar1 = qspi_nor_write_protection_set(param_1, 0);
        if (iVar1 == 0) {
            audio_i2s_stop_and_reset_channels(param_1);
            do {
                if (*(unsigned int *)(iVar3 + 0x2c) != param_3) {
                    if (0xffff < param_3) {
                        if ((param_2 & 0xffff) != 0) goto LAB_00060e9a;
                        iVar2 = nrfx_qspi_read(1, param_2);
                        uVar4 = 0x10000;
                        goto LAB_00060e40;
                    }
                    if (0xfff < param_3) {
LAB_00060e9a:
                        if ((param_2 & 0xfff) == 0) {
                            iVar2 = nrfx_qspi_read(0, param_2);
                            uVar4 = 0x1000;
                            goto LAB_00060e40;
                        }
                    }
                    local_34 = 0x000f5c9c;
                    local_38 = 4;
                    uStack_30 = param_2;
                    local_2c = param_3;
                    FUN_000838d6(0x00088270, 0x2040, &local_38);
                    FUN_000609f4(*(int *)(param_1 + 0x10), 0x0bad0004);
                    iVar2 = 0x0bad0004;
LAB_00060eda:
                    local_34 = 0x000f5cba;
                    local_38 = 4;
                    uStack_30 = param_2;
                    local_2c = param_3;
                    FUN_000838d6(0x00088270, 0x2040, &local_38);
                    iVar1 = qspi_get_zephyr_ret_code(iVar2);
                    break;
                }
                iVar2 = FUN_0008520c();
                uVar4 = param_3;
LAB_00060e40:
                FUN_000609f4(*(int *)(param_1 + 0x10), iVar2);
                if (iVar2 != 0x0bad0000) goto LAB_00060eda;
                param_3 = param_3 - uVar4;
                param_2 = param_2 + uVar4;
            } while (param_3 != 0);
            audio_i2s_start_channels(param_1);
            iVar3 = qspi_nor_write_protection_set(param_1, 1);
            if (iVar1 == 0) {
                iVar1 = iVar3;
            }
        }
        FUN_00072880(*(int *)(param_1 + 0x10));
    }
    FUN_00060a5c(param_1);
    return iVar1;
}
