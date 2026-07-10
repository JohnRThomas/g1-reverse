#include "g1_app_symbols.h"
/* named: bt_hci_driver_close */
/* globals referenced:
//   0x20002000  g_ble_dev_state              
*/
/* Reconstructed bt_hci_driver_close @ 0x54b70  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int arm_mpu_configure_partition_region(int);
extern int FUN_0005571c(void);
extern int bt_pub_key_hci_disrupted(void);
extern int bt_conn_cleanup_all(void);
extern int atomic_or(int,int);
extern int FUN_00080e94(int,int);
extern int FUN_00080ea2(int,int,void*);
extern int atomic_and_3(int,int);
extern int memset_bytes(int,int,int);

int bt_hci_driver_close(void)
{
    int base = ((uintptr_t)&g_ble_dev_state) /*=0x20002000*/;
    int iVar2;
    if (*(volatile int*)(base + 0x168) == 0) {
        unsigned local_20, local_1c;
        iVar2 = -0x13;
        local_1c = "No HCI driver registered" /*=0xf3376*/;
        local_20 = 2;
        FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/, 0x1040, &local_20);
    } else if (*(volatile int*)(*(volatile int*)(base + 0x168) + 0x10) == 0) {
        iVar2 = -0x86;
    } else {
        iVar2 = atomic_or(base + 0xd4, 2);
        if (iVar2 << 0x1e < 0) {
            iVar2 = -0x78;
        } else {
            atomic_and_3(base + 0xd4, 0xfffffffb);
            iVar2 = (*(int(**)(void))(*(volatile int*)(base + 0x168) + 0x10))();
            if (iVar2 == 0) {
                memset_bytes(base + 0x80, 0, 0x40);
                FUN_00080e94(base + 0x68, ((uintptr_t)&rodata_f2b3a) /*=0xf2b3a*/);
                FUN_0005571c();
                bt_pub_key_hci_disrupted();
                bt_conn_cleanup_all();
                *(volatile uint16_t*)((uintptr_t)&g_bt_hci_pending_opcode) /*=0x2000ff06*/ = 0;
                arm_mpu_configure_partition_region(((uintptr_t)&rx_thread_data) /*=0x20005e30*/);
                arm_mpu_configure_partition_region(((uintptr_t)&bt_workqueue) /*=0x20005f08*/);
                atomic_and_3(base + 0xd4, 0xfffffffe);
            } else {
                unsigned local_40, local_3c; int iStack_38;
                local_3c = "HCI driver close failed (%d)" /*=0xf33b7*/;
                local_40 = 3;
                iStack_38 = iVar2;
                FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/, 0x1840, &local_40);
                atomic_or(base + 0xd4, 4);
            }
        }
    }
    return iVar2;
}

