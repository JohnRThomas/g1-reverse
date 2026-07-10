/* named: audio_apply_config_cmd_0xab */
/* Reconstructed audio_apply_config_cmd_0xab @ 0x8397e  (parity: 300/300 trials, PROVEN) */

extern int qspi_nor_send_cinstr(unsigned int a, void *b, unsigned int c, unsigned int d, unsigned int e);
extern void delay_scaled_busy_wait(unsigned int a);

int audio_apply_config_cmd_0xab(unsigned int param_1)
{
    int iVar1;
    unsigned int local_14;
    unsigned int uStack_10;
    unsigned int local_c;
    uStack_10 = 0;
    local_c = 0;
    local_14 = 0xab;
    iVar1 = qspi_nor_send_cinstr(param_1, &local_14, 0, 0xab, param_1);
    if (-1 < iVar1) {
        delay_scaled_busy_wait(0x23);
        iVar1 = 0;
    }
    return iVar1;
}

