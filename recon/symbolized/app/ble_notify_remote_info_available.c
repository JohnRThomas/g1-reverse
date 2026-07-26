#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00056da8 @ 0x00056da8
 * public-name: ble_notify_remote_info_available
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_notify_remote_info_available         <= FUN_00056da8 @ 0x00056da8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   gatt_process_listener_notifications      <= FUN_000819ea @ 0x000819ea
 * address symbols (name @ address):
 *   rodata_87fec                             @ 0x00087fec
 *   rodata_88058                             @ 0x00088058
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0d20                             @ 0x000f0d20   [INLINED -- G6 literal batch]
 *   rodata_f3a5d                             @ 0x000f3a5d
 *   rodata_f3a8d                             @ 0x000f3a8d   [INLINED -- G6 literal batch]
 *   g_ble_conn_cb_list_head                  @ 0x2000ad1c
 */
/* Reconstructed FUN_00056da8 @ 0x56da8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void gatt_process_listener_notifications(void);
extern void printk(unsigned,...);
extern void assert_post_action(unsigned,unsigned);
typedef void (*fp)(int,...);
void ble_notify_remote_info_available(int param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    *(unsigned char*)(param_1 + 10) = *(unsigned char*)(param_1 + 9);
    gatt_process_listener_notifications();
    int iVar3 = *(volatile int*)((unsigned long)&g_ble_conn_cb_list_head) /*=0x2000ad1c*/;
    while (iVar3 != 0){
        fp pcVar2 = *(fp*)(iVar3 + 0x14);
        if (pcVar2 != 0){
            pcVar2(param_1, *(unsigned char*)(param_1+9), param_3, pcVar2, param_4);
        }
        iVar3 = *(int*)(iVar3 + 0x20);
    }
    unsigned uVar4 = ((unsigned long)&rodata_87fec) /*=0x87fec*/;
    unsigned uVar1 = ((unsigned long)&rodata_88058) /*=0x88058*/;
    while (1){
        if (uVar1 < uVar4){
            printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"cb <= _bt_conn_cb_list_end") /*=0xf3a8d*/, ((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/, 0x8ca);
            printk(((unsigned long)"\tunexpected list end location\n") /*=0xf0d20*/);
            assert_post_action(((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/, 0x8ca);
        }
        if (uVar1 <= uVar4) break;
        if (*(fp*)(uVar4 + 0x14) != 0){
            (*(fp*)(uVar4 + 0x14))(param_1, *(unsigned char*)(param_1+9), param_3);
        }
        uVar4 = uVar4 + 0x24;
    }
}
