/* named: bt_gatt_indicate */
/* globals referenced:
//   0x200020d4  g_bt_dev.ncmd_sem            [g_bt_dev (base 0x20002000) + 0xd4: semaphore gating outstanding HCI command credits, taken in bt_send/bt_hci_driver_close]
*/
/* Reconstructed bt_gatt_indicate @ 0x5b378  (parity: 300/300 trials, PROVEN) */
extern int bt_gatt_attr_get_handle(int a0);
extern int bt_gatt_foreach_attr_type(int a0,int a1,int a2,int a3,int a4,int a5,void *a6);
extern int gatt_indicate(int a0,int a1,int *a2);
extern void assert_post_action(int a0,int a1);
extern void printk(int a0,int a1,int a2,int a3);
extern int bt_uuid_cmp(int a0,void *a1);
extern int FUN_0008270c(int a0);
extern int bt_gatt_attr_value_handle(void);

int bt_gatt_indicate(int param_1,int *param_2)
{
    unsigned char local_28[2];
    unsigned short local_26;
    unsigned int *local_24;
    unsigned short local_20;
    unsigned int local_1c;
    unsigned short local_18;
    int *local_14;
    int iVar1;
    int uVar2;

    if (param_2 == (int*)0) {
        printk(0x00099cbd, 0x000f4b3d, 0x000f46b8, 0xbc4);
        printk(0x000f4a0a, 0, 0, 0);
        uVar2 = 0xbc4;
        assert_post_action(0x000f46b8, uVar2);
        return 0;
    } else {
        if ((param_2[1] != 0) || (param_2[0] != 0)) {
            iVar1 = FUN_0008270c(0x200020d4);
            if (-1 < (int)((unsigned int)iVar1 << 0x1d)) {
                return 0xfffffff5;
            }
            if ((param_1 != 0) && (*(unsigned char*)(param_1 + 0xd) != 7)) {
                return 0xffffff80;
            }
            local_24 = (unsigned int*)param_2[1];
            iVar1 = bt_gatt_attr_get_handle(param_2[1]);
            local_20 = (unsigned short)iVar1;
            if (param_2[0] == 0) {
                if (iVar1 != 0) goto LAB_0005b40a;
                return 0xfffffffe;
            } else {
                local_24 = (unsigned int*)0;
                bt_gatt_foreach_attr_type(iVar1,0xffff,param_2[0],0,1,0x000825fb,&local_24);
                if (local_24 != (unsigned int*)0) {
                    param_2[1] = (int)local_24;
LAB_0005b40a:
                    local_28[0] = 0;
                    local_26 = 0x2803;
                    iVar1 = bt_uuid_cmp(*local_24, local_28);
                    if (iVar1 == 0) {
                        if (-1 < (int)((unsigned int)(*(unsigned char*)(local_24[3] + 6)) << 0x1a)) {
                            return 0xffffffea;
                        }
                        local_20 = (unsigned short)bt_gatt_attr_value_handle();
                    }
                    if (param_1 != 0) {
                        *(unsigned char*)((int)param_2 + 0x16) = 1;
                        uVar2 = gatt_indicate(param_1, local_20, param_2);
                        return uVar2;
                    }
                    local_1c = 0xffffff80;
                    local_18 = 2;
                    local_26 = 0x2902;
                    *(unsigned char*)((int)param_2 + 0x16) = 0;
                    local_28[0] = 0;
                    local_14 = param_2;
                    bt_gatt_foreach_attr_type(local_20,0xffff,(int)local_28,0,1,0x0005b891,&local_24);
                    return local_1c;
                }
                return 0xfffffffe;
            }
        }
        printk(0x00099cbd, 0x000f4b44, 0x000f46b8, 0xbc5);
        printk(0x000f4a0a, 0, 0, 0);
        uVar2 = 0xbc5;
        assert_post_action(0x000f46b8, uVar2);
        return 0;
    }
}

