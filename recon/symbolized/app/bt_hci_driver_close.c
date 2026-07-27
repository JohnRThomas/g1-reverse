#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00054b70 @ 0x00054b70
 * public-name: bt_hci_driver_close
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arm_mpu_configure_partition_region       <= FUN_00050b8c @ 0x00050b8c
 *   bt_hci_driver_close                      <= FUN_00054b70 @ 0x00054b70
 *   clear_legacy_adv_state                   <= FUN_0005571c @ 0x0005571c
 *   bt_pub_key_hci_disrupted                 <= FUN_00055e1c @ 0x00055e1c
 *   bt_conn_cleanup_all                      <= FUN_00056990 @ 0x00056990
 *   atomic_or                                <= FUN_00080e6a @ 0x00080e6a
 *   bt_addr_le_copy_80e94                    <= FUN_00080e94 @ 0x00080e94
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 *   atomic_and_3                             <= FUN_00080ea8 @ 0x00080ea8
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_f2b3a                             @ 0x000f2b3a
 *   rodata_f3376                             @ 0x000f3376
 *   rodata_f33b7                             @ 0x000f33b7
 *   g_ble_dev_state                          @ 0x20002000
 *   rx_thread_data                           @ 0x20005e30
 *   bt_workqueue                             @ 0x20005f08
 *   g_bt_hci_pending_opcode                  @ 0x2000ff06
 */
/* Reconstructed FUN_00054b70 @ 0x54b70  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void arm_mpu_configure_partition_region(int);
extern int clear_legacy_adv_state(void);
extern int bt_pub_key_hci_disrupted(void);
extern int bt_conn_cleanup_all(void);
extern int atomic_or(volatile long*, long);
extern int bt_addr_le_copy_80e94(int,int);
extern int bt_log_forward_3arg(int,int,void*);
extern void atomic_and_3(void*, unsigned long);
extern void memset_bytes(void*, int, int);

int bt_hci_driver_close(void)
{
    int base = ((unsigned long)&g_ble_dev_state) /*=0x20002000*/;
    int iVar2;
    if (*(volatile int*)(base + 0x168) == 0) {
        unsigned local_20, local_1c;
        iVar2 = -0x13;
        local_1c = ((unsigned long)&rodata_f3376) /*=0xf3376*/;
        local_20 = 2;
        bt_log_forward_3arg(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1040, &local_20);
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
                bt_addr_le_copy_80e94(base + 0x68, ((unsigned long)&rodata_f2b3a) /*=0xf2b3a*/);
                clear_legacy_adv_state();
                bt_pub_key_hci_disrupted();
                bt_conn_cleanup_all();
                *(volatile uint16_t*)((unsigned long)&g_bt_hci_pending_opcode) /*=0x2000ff06*/ = 0;
                arm_mpu_configure_partition_region(((unsigned long)&rx_thread_data) /*=0x20005e30*/);
                arm_mpu_configure_partition_region(((unsigned long)&bt_workqueue) /*=0x20005f08*/);
                atomic_and_3(base + 0xd4, 0xfffffffe);
            } else {
                unsigned local_40, local_3c; int iStack_38;
                local_3c = ((unsigned long)&rodata_f33b7) /*=0xf33b7*/;
                local_40 = 3;
                iStack_38 = iVar2;
                bt_log_forward_3arg(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1840, &local_40);
                atomic_or(base + 0xd4, 4);
            }
        }
    }
    return iVar2;
}
