/* readable reconstruction; identity: FUN_0002efa8 @ 0x0002efa8
 * public-name: get_low_battery_flag_if_master
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   get_low_battery_flag_if_master           <= FUN_0002efa8 @ 0x0002efa8
 * address symbols (name @ address):
 *   g_low_battery_sync_flag                  @ 0x2000302f
 */
/* Reconstructed FUN_0002efa8 @ 0x2efa8  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);

unsigned char get_low_battery_flag_if_master(void)
{
    unsigned char *pcVar2 = get_device_info();
    unsigned char uVar1;
    if (*pcVar2 == 1) {
        uVar1 = *(volatile unsigned char*)0x2000302fUL;
    } else {
        uVar1 = 0;
    }
    return uVar1;
}
