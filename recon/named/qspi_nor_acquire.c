/* readable reconstruction; identity: FUN_00060a10 @ 0x00060a10
 * public-name: qspi_nor_acquire
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   qspi_get_zephyr_ret_code                 <= FUN_00060990 @ 0x00060990
 *   qspi_nor_acquire                         <= FUN_00060a10 @ 0x00060a10
 *   nrfx_qspi_init                           <= FUN_00066994 @ 0x00066994
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   audio_i2s_stop_and_reset_channels        <= FUN_00083906 @ 0x00083906
 *   audio_i2s_start_channels                 <= FUN_0008392e @ 0x0008392e
 * address symbols (name @ address):
 *   rodata_838cb                             @ 0x000838cb
 *   g_qspi_nor_initialized                   @ 0x2001d535
 */
/* Reconstructed FUN_00060a10 @ 0x60a10  (parity: 300/300 trials, PROVEN) */

extern int qspi_get_zephyr_ret_code(void);
#define nrfx_qspi_init nrfx_qspi_init
extern void nrfx_qspi_init(int,int,int,int,int);
extern void k_sem_give(int);
extern void audio_i2s_stop_and_reset_channels(void);
extern void audio_i2s_start_channels(int);

int qspi_nor_acquire(int param_1, int param_2, int param_3, int param_4)
{
    int iVar3 = *(volatile int*)(param_1+0x10);
    int iVar2;
    if (*(volatile char*)(iVar3+0x60) == 0) {
        audio_i2s_stop_and_reset_channels();
        volatile char *pcVar1 = (volatile char*)0x2001d535UL;
        k_sem_give(iVar3+0x48);
        iVar2 = 0;
        if (*pcVar1 == 0) {
            nrfx_qspi_init(*(volatile int*)(param_1+4), 0x000838cb,
                                    iVar3, 0, param_4);
            iVar2 = qspi_get_zephyr_ret_code();
            *pcVar1 = (iVar2==0);
        }
        audio_i2s_start_channels(param_1);
    } else {
        iVar2 = 0;
    }
    return iVar2;
}
