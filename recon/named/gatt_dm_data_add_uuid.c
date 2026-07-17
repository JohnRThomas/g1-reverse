/* readable reconstruction; identity: FUN_0004ea28 @ 0x0004ea28
 * public-name: gatt_dm_data_add_uuid
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_dm_attr_alloc                       <= FUN_0004e8e8 @ 0x0004e8e8
 *   gatt_dm_data_add_uuid                    <= FUN_0004ea28 @ 0x0004ea28
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_88130                             @ 0x00088130
 *   rodata_f1270                             @ 0x000f1270
 *   rodata_f1284                             @ 0x000f1284
 */
/* Reconstructed FUN_0004ea28 @ 0x4ea28  (parity: 300/300 trials, PROVEN) */

extern void memcpy(int,void*,int);
extern int gatt_dm_attr_alloc(void);
extern int FUN_0004e98c(int);
extern void FUN_0007f406(int,int,void*);

int gatt_dm_data_add_uuid(unsigned char *param_1)
{
    int local_18;
    int local_14;
    int uVar1, iVar2;
    local_14 = 0x000f1270;
    if (param_1 != 0) {
        uVar1 = FUN_0004e98c(*param_1);
        iVar2 = gatt_dm_attr_alloc();
        local_14 = 0x000f1284;
        if (iVar2 != 0) {
            memcpy(iVar2, param_1, uVar1);
            return iVar2;
        }
    }
    local_18 = 2;
    FUN_0007f406(0x00088130, 0x1040, &local_18);
    return 0;
}
