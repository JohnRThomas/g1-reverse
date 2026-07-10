/* named: qspi_nor_configure */
/* globals referenced:
//   0x500055b8  NRF_I2S0_CONFIG_CHANNELS     
*/
/* Reconstructed qspi_nor_configure @ 0x60c00  (parity: 300/300 trials, PROVEN) */
extern int FUN_0005010c(int,...);
extern int qspi_get_zephyr_ret_code(int,...);
extern int qspi_nor_acquire(int,...);
extern int FUN_00060a5c(int,...);
extern int qspi_nor_send_cinstr(int,...);
extern int nrfx_qspi_init(int,...);
extern int FUN_000838d6(int,...);
extern int pinctrl_apply_state.constprop.0(int,...);
extern int audio_apply_config_cmd_0xab(int,...);
extern int qspi_rdsr(int,...);
extern int memcmp(int,...);

int qspi_nor_configure(int param_1)
{
    int iVar1, iVar4;
    unsigned uVar5;

    iVar1 = pinctrl_apply_state.constprop.0(0);
    if (iVar1 < 0) return iVar1;
    FUN_0005010c(0);
    iVar4 = *(int *)(param_1 + 4);
    *(volatile int *)0x500055b8UL = 0;
    nrfx_qspi_init(0);
    *(volatile int *)0x500055b8UL = 2;
    iVar1 = qspi_get_zephyr_ret_code(0);
    if (iVar1 < 0) return iVar1;
    iVar1 = audio_apply_config_cmd_0xab(0);
    if (iVar1 < 0) return iVar1;

    if (((unsigned)*(unsigned char *)(iVar4 + 0x1d) - 2u) < 2u) uVar5 = 1;
    else if (((unsigned)*(unsigned char *)(iVar4 + 0x1c) - 3u) < 2u) uVar5 = 1;
    else uVar5 = 0;

    iVar1 = qspi_rdsr(0);
    if (iVar1 < 0) { FUN_000838d6(0); return iVar1; }

    if (uVar5 != ((unsigned)(iVar1 << 25) >> 31)) {
        iVar1 = qspi_nor_send_cinstr(0);
        if (iVar1 != 0) {
            if (iVar1 >= 0) return iVar1;
            FUN_000838d6(0);
            return iVar1;
        }
        do {
            iVar1 = qspi_rdsr(0);
            if (iVar1 < 0) { FUN_000838d6(0); return iVar1; }
        } while (iVar1 & 1);
    }

    FUN_00060a5c(0);
    iVar1 = qspi_nor_acquire(0);
    if (iVar1 == 0) {
        iVar1 = qspi_nor_send_cinstr(0);
        FUN_00060a5c(0);
        if (iVar1 == 0) {
            iVar4 = *(int *)(param_1 + 4);
            iVar1 = memcmp(0);
            if (iVar1 == 0) return 0;
            FUN_000838d6(0);
        }
    } else {
        FUN_00060a5c(0);
    }
    return -0x13;
}

