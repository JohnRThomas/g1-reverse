/* readable reconstruction; identity: FUN_00054c74 @ 0x00054c74
 * public-name: bt_set_name_internal
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strcmp                                   <= FUN_0000eefe @ 0x0000eefe
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   bt_settings_store_name                   <= FUN_00053098 @ 0x00053098
 *   bt_set_name_internal                     <= FUN_00054c74 @ 0x00054c74
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_f33d4                             @ 0x000f33d4
 *   g_ble_dev_state                          @ 0x20002000
 *   g_bt_dev_name                            @ 0x2000216c
 */
/* Reconstructed FUN_00054c74 @ 0x54c74  (parity: 300/300 trials, PROVEN) */
extern int strlen(int);
extern int strcmp(unsigned a, unsigned b);
extern void memcpy(int, int, int);
extern int bt_settings_store_name(int a, unsigned b);
extern void bt_log_forward_3arg(unsigned a, int b, void* c);
unsigned bt_set_name_internal(unsigned param_1){
    unsigned uVar1 = strlen(param_1);
    unsigned uVar3;
    if (uVar1 < 0x1d){
        int iVar2 = strcmp(0x2000216c, param_1);
        if (iVar2 != 0){
            memcpy(0x2000216c, param_1, uVar1);
            int base = 0x20002000 + 0x16c;
            *(volatile unsigned char*)(0x20002000UL + uVar1 + 0x16c) = 0;
            iVar2 = bt_settings_store_name(base, uVar1);
            if (iVar2 != 0){
                volatile unsigned local_18 = 2;
                volatile unsigned local_14 = 0xf33d4;
                (void)local_14;
                bt_log_forward_3arg(0x88138, 0x1080, (void*)&local_18);
            }
        }
        uVar3 = 0;
    } else uVar3 = 0xfffffff4;
    return uVar3;
}
