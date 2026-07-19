/* readable reconstruction; identity: FUN_00060f20 @ 0x00060f20
 * public-name: qspi_nor_write
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   qspi_get_zephyr_ret_code                 <= FUN_00060990 @ 0x00060990
 *   qspi_nor_lock_if_magic                   <= FUN_000609f4 @ 0x000609f4
 *   qspi_nor_acquire                         <= FUN_00060a10 @ 0x00060a10
 *   qspi_nor_suspend_bus                     <= FUN_00060a5c @ 0x00060a5c
 *   qspi_nor_write                           <= FUN_00060f20 @ 0x00060f20
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   qspi_log_forward                         <= FUN_000838d6 @ 0x000838d6
 *   audio_stream_stop_and_wait               <= FUN_000838fa @ 0x000838fa
 *   audio_i2s_stop_and_reset_channels        <= FUN_00083906 @ 0x00083906
 *   audio_i2s_start_channels                 <= FUN_0008392e @ 0x0008392e
 *   qspi_nor_write_protection_set            <= FUN_00083954 @ 0x00083954
 *   nrfx_qspi_write                          <= FUN_00085200 @ 0x00085200
 *   nrfx_qspi_read                           <= FUN_00085206 @ 0x00085206
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_88270                             @ 0x00088270
 *   rodata_f5cd8                             @ 0x000f5cd8
 *   g_sram_base_word                         @ 0x20000000
 */
/* Reconstructed FUN_00060f20 @ 0x60f20  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int qspi_get_zephyr_ret_code(int,...);
extern int qspi_nor_lock_if_magic(int,...);
extern int qspi_nor_acquire(int,...);
extern int qspi_nor_suspend_bus(int,...);
extern int k_sem_give(int,...);
extern int qspi_log_forward(int,...);
extern int audio_stream_stop_and_wait(int,...);
extern int audio_i2s_stop_and_reset_channels(int,...);
extern int audio_i2s_start_channels(int,...);
extern int qspi_nor_write_protection_set(int,...);
extern int nrfx_qspi_write(int,...);
extern int nrfx_qspi_read(int,...);
extern int memcpy(int,...);

int qspi_nor_write(int param_1, unsigned param_2, unsigned char *param_3, unsigned param_4)
{
    int iVar1, iVar2;
    unsigned uVar3;
    unsigned local_48, local_44, uStack_40, local_3c;
    unsigned char auStack_38[20];

    if (param_3 == 0 || param_4 == 0 || (4 < param_4 && (param_4 & 3) != 0) || (param_2 & 3) != 0)
        return -0x16;
    if ((int)param_2 < 0 || *(unsigned*)(*(int*)(param_1+4)+0x2c) < param_2 + param_4) {
        local_44 = 0x000f5cd8;
        local_48 = 4;
        uStack_40 = param_2;
        local_3c = param_4;
        qspi_log_forward(0x00088270, 0x2040, &local_48);
        return -0x16;
    }
    iVar1 = qspi_nor_acquire(param_1);
    if (iVar1 != 0) goto LAB_00061054;
    audio_stream_stop_and_wait(*(unsigned*)(param_1+0x10));
    iVar2 = qspi_nor_write_protection_set(param_1, 0);
    audio_i2s_stop_and_reset_channels(param_1);
    iVar1 = 0x0bad0000;
    if (iVar2 == 0) {
        if (param_4 < 4) {
            iVar2 = nrfx_qspi_read((int)auStack_38, 4, param_2);
            qspi_nor_lock_if_magic(*(unsigned*)(param_1+0x10), iVar2);
            if (iVar2 == 0x0bad0000) {
                memcpy((int)auStack_38, param_3, param_4);
                param_4 = 4;
                param_3 = auStack_38;
LAB_00060fd6:
                iVar2 = nrfx_qspi_write((int)param_3, param_4, param_2);
                qspi_nor_lock_if_magic(*(unsigned*)(param_1+0x10), iVar2);
            }
        } else {
            if (((unsigned)param_3 & 0xe0000000) == 0x20000000 && ((unsigned)param_3 & 3) == 0)
                goto LAB_00060fd6;
            do {
                uVar3 = param_4;
                if (0xf < param_4) uVar3 = 0x10;
                memcpy((int)auStack_38, param_3, uVar3);
                iVar2 = nrfx_qspi_write((int)auStack_38, uVar3, param_2);
                qspi_nor_lock_if_magic(*(unsigned*)(param_1+0x10), iVar2);
                if (iVar2 != iVar1) break;
                param_4 -= uVar3;
                param_3 += uVar3;
                param_2 += uVar3;
            } while (param_4 != 0);
        }
    }
    audio_i2s_start_channels(param_1);
    iVar1 = qspi_nor_write_protection_set(param_1, 1);
    k_sem_give(*(unsigned*)(param_1+0x10));
    if (iVar2 == 0) iVar2 = iVar1;
    iVar1 = qspi_get_zephyr_ret_code(iVar2);
LAB_00061054:
    qspi_nor_suspend_bus(param_1);
    return iVar1;
}
