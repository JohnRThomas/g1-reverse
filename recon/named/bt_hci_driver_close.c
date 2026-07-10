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
    int base = 0x20002000;
    int iVar2;
    if (*(volatile int*)(base + 0x168) == 0) {
        unsigned local_20, local_1c;
        iVar2 = -0x13;
        local_1c = 0x000f3376;
        local_20 = 2;
        FUN_00080ea2(0x00088138, 0x1040, &local_20);
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
                FUN_00080e94(base + 0x68, 0x000f2b3a);
                FUN_0005571c();
                bt_pub_key_hci_disrupted();
                bt_conn_cleanup_all();
                *(volatile uint16_t*)0x2000ff06UL = 0;
                arm_mpu_configure_partition_region(0x20005e30);
                arm_mpu_configure_partition_region(0x20005f08);
                atomic_and_3(base + 0xd4, 0xfffffffe);
            } else {
                unsigned local_40, local_3c; int iStack_38;
                local_3c = 0x000f33b7;
                local_40 = 3;
                iStack_38 = iVar2;
                FUN_00080ea2(0x00088138, 0x1840, &local_40);
                atomic_or(base + 0xd4, 4);
            }
        }
    }
    return iVar2;
}

