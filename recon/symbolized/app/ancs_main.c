#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00019950 @ 0x00019950
 * public-name: ancs_main
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   ancs_c_init                              <= FUN_0001905c @ 0x0001905c
 *   ancs_discover_params_reset               <= FUN_000191d8 @ 0x000191d8
 *   bt_start                                 <= FUN_00019308 @ 0x00019308
 *   start_ancs_work_thread                   <= FUN_000198cc @ 0x000198cc
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   sys_reboot                               <= FUN_0004c0a8 @ 0x0004c0a8
 *   bt_send                                  <= FUN_00054a44 @ 0x00054a44
 *   bt_hci_driver_close                      <= FUN_00054b70 @ 0x00054b70
 *   bt_conn_auth_info_cb_register            <= FUN_00057330 @ 0x00057330
 *   bt_gatt_cb_register                      <= FUN_0005a9d8 @ 0x0005a9d8
 *   bt_foreach_bond                          <= FUN_0005e6d4 @ 0x0005e6d4
 *   settings_load                            <= FUN_0007f192 @ 0x0007f192
 * address symbols (name @ address):
 *   g_log_level                              @ 0x2000230c
 *   g_ancs_active_conn                       @ 0x20006ab8
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed ancs_main @ 0x19950  (parity: 300/300 trials, PROVEN) */
extern int DEBUG_PRINT(int a, ...);
extern int get_device_info(int a, ...);
extern int debug_print(int a, ...);
extern int FUN_0007c0a8(int a, ...);
extern int bt_send(int a, ...);
extern int bt_hci_driver_close(int a, ...);
extern int bt_foreach_bond(int a, ...);
extern int settings_load(int a, ...);
extern int ancs_c_init(int a, ...);
extern int ancs_discover_params_reset(int a, ...);
extern int FUN_000572fc(int a, ...);
extern int bt_conn_auth_info_cb_register(int a, ...);
extern int bt_gatt_cb_register(int a, ...);
extern int FUN_000181f0(int a, ...);
extern int bt_start(int a, ...);
extern int start_ancs_work_thread(int a, ...);
extern int sys_reboot(int a, ...);

unsigned int ancs_main(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int *piVar1;
    int iVar2;
    unsigned int uVar3;
    int iVar4;
    int iVar5;

    piVar1 = (int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
    *(volatile unsigned int*)((unsigned long)&g_ancs_active_conn) /*=0x20006ab8*/ = (unsigned int)param_1;
    if (0 < *piVar1) {
        if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT(0,0,param_3,0,param_4);
        } else {
            debug_print(0);
        }
    }
    uVar3 = 0;
    iVar5 = 0x32;
    iVar4 = 5;
    do {
        for (;;) {
            iVar2 = get_device_info(0);
            if (*(volatile char*)(iVar2 + 0x1058) != 0) break;
            if (iVar5 == 0) break;
            FUN_0007c0a8(100);
            iVar5 = iVar5 - 1;
        }
        iVar2 = bt_send(0);
        if (iVar2 == 0) break;
        bt_hci_driver_close(0);
        DEBUG_PRINT(uVar3, iVar2, iVar4);
        iVar4 = iVar4 - 1;
        FUN_0007c0a8(1000);
    } while (iVar4 != 0);
    bt_foreach_bond(0, 0);
    settings_load(0);
    iVar4 = ancs_c_init(param_1 + 0x34);
    uVar3 = 0;
    if (iVar4 == 0) goto LAB_00019a16;
    do {
        DEBUG_PRINT(uVar3, iVar4);
        for (;;) {
            DEBUG_PRINT(0,0);
            FUN_0007c0a8(1000);
            if (0 < *piVar1) {
                if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    DEBUG_PRINT(0,0);
                } else {
                    debug_print(0);
                }
            }
            FUN_0007c0a8(500);
            sys_reboot(1);
LAB_00019a16:
            iVar4 = ancs_discover_params_reset(0);
            uVar3 = 0;
            if (iVar4 != 0) break;
            iVar4 = FUN_000572fc(0);
            uVar3 = 0;
            if (iVar4 != 0) goto LAB_00019a2c;
            iVar4 = bt_conn_auth_info_cb_register(0);
            uVar3 = 0;
            if (iVar4 != 0) goto LAB_00019a2c;
            bt_gatt_cb_register(0);
            iVar4 = FUN_000181f0(0);
            uVar3 = 0;
            if (iVar4 != 0) goto LAB_00019a2c;
            iVar4 = bt_start(0);
            if (iVar4 == 0) {
                start_ancs_work_thread(param_1);
                return 0;
            }
            DEBUG_PRINT(0,0,iVar4);
            continue;
LAB_00019a2c:
            DEBUG_PRINT(uVar3);
        }
    } while (1);
    return iVar4;
}
