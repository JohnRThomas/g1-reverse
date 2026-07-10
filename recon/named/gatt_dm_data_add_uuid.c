/* named: gatt_dm_data_add_uuid */
/* Reconstructed gatt_dm_data_add_uuid @ 0x4ea28  (parity: 300/300 trials, PROVEN) */

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

