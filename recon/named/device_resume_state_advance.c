/* readable reconstruction; identity: FUN_0007c108 @ 0x0007c108
 * public-name: device_resume_state_advance
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   legacy_adv_stop_cleanup                  <= FUN_000559fc @ 0x000559fc
 *   device_resume_state_advance              <= FUN_0007c108 @ 0x0007c108
 */
/* Reconstructed FUN_0007c108 @ 0x7c108  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern int legacy_adv_stop_cleanup(void);
int device_resume_state_advance(void)
{
    int iVar1 = get_device_info();
    if (*(volatile char*)(iVar1 + 0x1058) == 2) {
        iVar1 = legacy_adv_stop_cleanup();
        if (iVar1 != 0) {
            return iVar1;
        }
        iVar1 = get_device_info();
        *(volatile char*)(iVar1 + 0x1058) = 3;
    }
    return 0;
}
