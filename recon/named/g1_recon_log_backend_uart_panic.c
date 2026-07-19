/* readable reconstruction; identity: FUN_0004def8 @ 0x0004def8
 * public-name: g1_recon_log_backend_uart_panic
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   onoff_transition_invoke                  <= FUN_0004dfb8 @ 0x0004dfb8
 *   log_output_flush                         <= FUN_0007eece @ 0x0007eece
 *   audio_hw_lock_get_status_byte            <= FUN_0007ef1c @ 0x0007ef1c
 * address symbols (name @ address):
 *   rodata_87bc0                             @ 0x00087bc0
 *   rodata_8ad08                             @ 0x0008ad08
 *   log_output_flush_done                    @ 0x2001d44e
 */
/* Reconstructed g1_recon_log_backend_uart_panic @ 0x4def8.
 * Raw/address back-map: g1_recon_log_backend_uart_panic <= FUN_0004def8 @ 0x0004def8.
 */

extern int audio_hw_lock_get_status_byte(unsigned int, void*, unsigned int, unsigned int, unsigned int);
extern void onoff_transition_invoke(unsigned int);
extern void log_output_flush(unsigned int);

void g1_recon_log_backend_uart_panic(unsigned int param_1, unsigned int param_2,
                                     unsigned int param_3, unsigned int param_4)
{
    int iVar2;
    unsigned int uStack_c = param_2;
    unsigned int uStack_8 = param_3;
    iVar2 = audio_hw_lock_get_status_byte(0x87bc0U, (char*)&uStack_c + 3, param_3, param_4, param_1);
    if (iVar2 == 0 && *((unsigned char*)&uStack_c + 3) == 1) {
        onoff_transition_invoke(0x87bc0U);
    }
    unsigned int uVar1 = 0x8ad08U;
    *(volatile unsigned char*)0x2001d44eUL = 1;
    log_output_flush(uVar1);
    return;
}
