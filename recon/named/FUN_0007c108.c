/* readable reconstruction; identity: FUN_0007c108 @ 0x0007c108
 * public-name: FUN_0007c108
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 */
/* Reconstructed FUN_0007c108 @ 0x7c108  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern int FUN_000559fc(void);
int FUN_0007c108(void)
{
    int iVar1 = get_device_info();
    if (*(volatile char*)(iVar1 + 0x1058) == 2) {
        iVar1 = FUN_000559fc();
        if (iVar1 != 0) {
            return iVar1;
        }
        iVar1 = get_device_info();
        *(volatile char*)(iVar1 + 0x1058) = 3;
    }
    return 0;
}
