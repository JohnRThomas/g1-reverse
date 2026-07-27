/* readable reconstruction; identity: FUN_0008397e @ 0x0008397e
 * public-name: audio_apply_config_cmd_0xab
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   qspi_nor_send_cinstr                     <= FUN_00060ab0 @ 0x00060ab0
 *   audio_apply_config_cmd_0xab              <= FUN_0008397e @ 0x0008397e
 *   delay_scaled_busy_wait                   <= FUN_00086384 @ 0x00086384
 */
/* Reconstructed FUN_0008397e @ 0x8397e  (parity: 300/300 trials, PROVEN) */

extern int qspi_nor_send_cinstr(void*, unsigned char*, unsigned char);
extern void delay_scaled_busy_wait(int);

int audio_apply_config_cmd_0xab(unsigned int param_1)
{
    int iVar1;
    struct {
        unsigned int opcode;
        unsigned int first;
        unsigned int second;
    } request = { 0xab, 0, 0 };
    iVar1 = qspi_nor_send_cinstr(param_1, &request, 0);
    if (-1 < iVar1) {
        delay_scaled_busy_wait(0x23);
        iVar1 = 0;
    }
    return iVar1;
}
