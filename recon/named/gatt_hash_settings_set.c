/* readable reconstruction; identity: FUN_0005a28c @ 0x0005a28c
 * public-name: gatt_hash_settings_set
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_hash_settings_set                   <= FUN_0005a28c @ 0x0005a28c
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f4783                             @ 0x000f4783
 *   g_20006390                               @ 0x20006390
 */
/* Reconstructed FUN_0005a28c @ 0x5a28c  (parity: 300/300 trials, PROVEN) */

extern void log_msg_create_3arg(unsigned int a, unsigned int b, void *c);
typedef int (*fn_t)(unsigned int, unsigned int, unsigned int);

int gatt_hash_settings_set(unsigned int param_1, unsigned int param_2, fn_t param_3, unsigned int param_4)
{
    int iVar1;
    unsigned int local_20;
    unsigned int local_1c;
    int iStack_18;

    iVar1 = param_3(param_4, 0x20006390UL, 0x10);
    if (iVar1 < 0) {
        local_1c = 0x000f4783UL;
        local_20 = 3;
        iStack_18 = iVar1;
        log_msg_create_3arg(0x00088128UL, 0x1840, &local_20);
        return iVar1;
    } else {
        return 0;
    }
}
