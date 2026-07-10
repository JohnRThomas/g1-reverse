/* named: bt_gatt_dm_attr_service_val */
/* Reconstructed bt_gatt_dm_attr_service_val @ 0x7f460  (parity: 300/300 trials, PROVEN) */

extern int bt_uuid_cmp(void*, int);

int bt_gatt_dm_attr_service_val(int *param_1, int param_2, int param_3)
{
    int iVar2;
    unsigned char b0; unsigned short h1;
    struct { unsigned char b0; unsigned char b1; unsigned short h1; } local;
    local.b0 = 0;
    local.h1 = 0x2800;
    iVar2 = bt_uuid_cmp(&local, *param_1);
    if (iVar2 != 0) {
        struct { unsigned char b0; unsigned char b1; unsigned short h1; } local2;
        local2.b0 = 0;
        local2.h1 = 0x2801;
        iVar2 = bt_uuid_cmp(&local2, *param_1);
        if (iVar2 != 0) return 0;
    }
    return *param_1 - 8;
}

