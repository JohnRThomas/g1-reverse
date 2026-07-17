/* readable reconstruction; identity: FUN_0007dada @ 0x0007dada
 * public-name: clear_app_switch_pending_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   get_current_burial_point_type            <= FUN_0007dac0 @ 0x0007dac0
 *   clear_app_switch_pending_flag            <= FUN_0007dada @ 0x0007dada
 */
/* Reconstructed FUN_0007dada @ 0x7dada  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern unsigned int get_current_burial_point_type(void);

void clear_app_switch_pending_flag(void)
{
    int iVar1;
    unsigned int uVar2;
    iVar1 = get_device_info();
    if ((*(volatile unsigned char*)(iVar1 + 0x10ac) != 0) && ((uVar2 = get_current_burial_point_type()), uVar2 < 7)) {
        iVar1 = get_device_info();
        *(volatile unsigned char*)(iVar1 + 0x10ac) = 0;
    }
}
