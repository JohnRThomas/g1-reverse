/* readable reconstruction; identity: FUN_00052edc @ 0x00052edc
 * public-name: bt_settings_subsys_init_check
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   settings_subsys_init                     <= FUN_0004e744 @ 0x0004e744
 *   bt_settings_subsys_init_check            <= FUN_00052edc @ 0x00052edc
 * address symbols (name @ address):
 *   rodata_88178                             @ 0x00088178
 *   rodata_f2c46                             @ 0x000f2c46
 */
/* Reconstructed FUN_00052edc @ 0x52edc  (parity: 300/300 trials, PROVEN) */

extern int settings_subsys_init(void);
extern void z_log_msg_runtime_create(unsigned int a, unsigned int b, void *c, unsigned int d);

int bt_settings_subsys_init_check(void)
{
    int iVar1 = settings_subsys_init();
    if (iVar1 != 0) {
        struct { unsigned int f0; unsigned int f1; unsigned int f2; } s;
        s.f0 = 3;
        s.f1 = 0x000f2c46UL;
        s.f2 = iVar1;
        z_log_msg_runtime_create(0x00088178UL, 0x1840, &s, 0);
    }
    return iVar1;
}
