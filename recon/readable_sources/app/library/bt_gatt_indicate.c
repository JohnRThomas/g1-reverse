#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_bt_conn__param_0248                    [param_0248; library]
 *   param_2          => struct g1_layout_bt_gatt_indicate_params__param_0257    [param_0257; library]
 *   local_28         => struct g1_layout_bt_gatt_indicate_locals__stack_1224    [stack_1224; G1-original]
 * Raw function identity: 0x0005b378.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0005b378 @ 0x0005b378
 * public-name: bt_gatt_indicate
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_attr_get_handle                  <= FUN_0005a9f4 @ 0x0005a9f4
 *   bt_gatt_foreach_attr_type                <= FUN_0005aa84 @ 0x0005aa84
 *   gatt_indicate                            <= FUN_0005b270 @ 0x0005b270
 *   bt_gatt_indicate                         <= FUN_0005b378 @ 0x0005b378
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_uuid_cmp                              <= FUN_00080d3e @ 0x00080d3e
 *   read_struct_first_word                   <= FUN_0008270c @ 0x0008270c
 *   bt_gatt_attr_value_handle                <= FUN_00082c0e @ 0x00082c0e
 * address symbols (name @ address):
 *   ADDR_gatt_send_ccc_update_THUMB          @ 0x0005b891
 *   rodata_825fb                             @ 0x000825fb
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f46b8                             @ 0x000f46b8
 *   rodata_f4a0a                             @ 0x000f4a0a
 *   rodata_f4b3d                             @ 0x000f4b3d
 *   rodata_f4b44                             @ 0x000f4b44
 *   g_ble_dev_ncmd_sem                       @ 0x200020d4
 */
/* Reconstructed FUN_0005b378 @ 0x5b378  (parity: 300/300 trials, PROVEN) */
extern int bt_gatt_attr_get_handle(int a0);
extern int bt_gatt_foreach_attr_type(int a0,int a1,int a2,int a3,int a4,int a5,void *a6);
extern int gatt_indicate(int a0,int a1,int *a2);
extern void assert_post_action(int a0,int a1);
extern void printk(int a0,int a1,int a2,int a3);
extern int bt_uuid_cmp(int a0,void *a1);
extern int read_struct_first_word(int a0);
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
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f4b3d) /*=0xf4b3d*/, ((unsigned long)&rodata_f46b8) /*=0xf46b8*/, 0xbc4);
        printk(((unsigned long)&rodata_f4a0a) /*=0xf4a0a*/, 0, 0, 0);
        uVar2 = 0xbc4;
        assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/, uVar2);
        return 0;
    } else {
        if ((param_2[1] != 0) || (param_2[0] != 0)) {
            iVar1 = read_struct_first_word(((unsigned long)&g_ble_dev_ncmd_sem) /*=0x200020d4*/);
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
                if (iVar1 != 0) goto control_label_0005b40a;
                return 0xfffffffe;
            } else {
                local_24 = (unsigned int*)0;
                bt_gatt_foreach_attr_type(iVar1,0xffff,param_2[0],0,1,((unsigned long)&rodata_825fb) /*=0x825fb*/,&local_24);
                if (local_24 != (unsigned int*)0) {
                    param_2[1] = (int)local_24;
control_label_0005b40a:
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
                    bt_gatt_foreach_attr_type(local_20,0xffff,(int)local_28,0,1,ADDR_gatt_send_ccc_update_THUMB /*=0x5b891*/,&local_24);
                    return local_1c;
                }
                return 0xfffffffe;
            }
        }
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f4b44) /*=0xf4b44*/, ((unsigned long)&rodata_f46b8) /*=0xf46b8*/, 0xbc5);
        printk(((unsigned long)&rodata_f4a0a) /*=0xf4a0a*/, 0, 0, 0);
        uVar2 = 0xbc5;
        assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/, uVar2);
        return 0;
    }
}
