#include "g1_app_symbols.h"
/* named: qspi_nor_acquire */
/* Reconstructed qspi_nor_acquire @ 0x60a10  (parity: 300/300 trials, PROVEN) */

extern int qspi_get_zephyr_ret_code(void);
extern void nrfx_qspi_init(int,int,int,int,int);
extern void FUN_00072880(int);
extern void audio_i2s_stop_and_reset_channels(void);
extern void audio_i2s_start_channels(int);

int qspi_nor_acquire(int param_1, int param_2, int param_3, int param_4)
{
    int iVar3 = *(volatile int*)(param_1+0x10);
    int iVar2;
    if (*(volatile char*)(iVar3+0x60) == 0) {
        audio_i2s_stop_and_reset_channels();
        volatile char *pcVar1 = (volatile char*)((uintptr_t)&g_qspi_nor_initialized) /*=0x2001d535*/;
        FUN_00072880(iVar3+0x48);
        iVar2 = 0;
        if (*pcVar1 == 0) {
            nrfx_qspi_init(*(volatile int*)(param_1+4), ((uintptr_t)&rodata_838cb) /*=0x838cb*/, iVar3, 0, param_4);
            iVar2 = qspi_get_zephyr_ret_code();
            *pcVar1 = (iVar2==0);
        }
        audio_i2s_start_channels(param_1);
    } else {
        iVar2 = 0;
    }
    return iVar2;
}

