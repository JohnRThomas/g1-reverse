#include "g1_app_symbols.h"
/* named: FUN_0004ee68 */
/* Reconstructed FUN_0004ee68 @ 0x4ee68  (parity: 300/300 trials, PROVEN) */
extern int FUN_0004ed3c(int a0, void *a1);
extern int bt_gatt_dm_attr_service_val(void);
extern int bt_gatt_dm_conn_get(int a0);
extern int bt_gatt_dm_service_get(void);
extern int bt_gatt_dm_desc_by_uuid(int a0, int a1, void *a2);
extern int bt_uuid_cmp(int a0, void *a1);

int FUN_0004ee68(int param_1, int *param_2)
{
    unsigned char buf[24];
    int *puVar1;
    int uVar9;
    int iVar3a, iVar3b, iVar3c, iVar3d, iVar3e, iVar3f, iVar4a, iVar4b;

    bt_gatt_dm_service_get();
    puVar1 = (int*)(long)bt_gatt_dm_attr_service_val();
    uVar9 = *puVar1;
    iVar3a = bt_uuid_cmp(uVar9, buf);
    if (iVar3a == 0) {
        param_2[0]=0; param_2[1]=0; param_2[2]=0; param_2[3]=0;
        *(unsigned short*)(param_2+4) = 0;
        iVar3a = FUN_0004ed3c(param_1, buf);
        if (iVar3a != 0) {
            iVar3b = bt_gatt_dm_desc_by_uuid(param_1, iVar3a, buf);
            if (iVar3b != 0) {
                *(unsigned short*)((char*)param_2+8) = *(unsigned short*)(iVar3b+4);
                iVar3c = FUN_0004ed3c(param_1, buf);
                if (iVar3c != 0) {
                    iVar4a = bt_gatt_dm_desc_by_uuid(param_1, iVar3c, buf);
                    if (iVar4a != 0) {
                        *(unsigned short*)((char*)param_2+10) = *(unsigned short*)(iVar4a+4);
                        iVar3d = bt_gatt_dm_desc_by_uuid(param_1, iVar3c, buf);
                        if (iVar3d != 0) {
                            *(unsigned short*)((char*)param_2+12) = *(unsigned short*)(iVar3d+4);
                            iVar3e = FUN_0004ed3c(param_1, buf);
                            if (iVar3e != 0) {
                                iVar4b = bt_gatt_dm_desc_by_uuid(param_1, iVar3e, buf);
                                if (iVar4b != 0) {
                                    *(unsigned short*)((char*)param_2+14) = *(unsigned short*)(iVar4b+4);
                                    iVar3f = bt_gatt_dm_desc_by_uuid(param_1, iVar3e, buf);
                                    if (iVar3f != 0) {
                                        *(unsigned short*)((char*)param_2+16) = *(unsigned short*)(iVar3f+4);
                                        uVar9 = bt_gatt_dm_conn_get(param_1);
                                        param_2[0] = uVar9;
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        uVar9 = 0xffffffea;
    } else {
        uVar9 = 0xffffff7a;
    }
    return uVar9;
}

