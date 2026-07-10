#include "g1_app_symbols.h"
/* named: ble_process_req_dispatch */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed ble_process_req_dispatch @ 0x21460  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>

extern void DEBUG_PRINT();
extern int  get_device_type();
extern int  get_device_info();
extern int  FUN_00019b2c();
extern void audio_fw_load_get_wrapper();
extern void debug_print();
extern void send_dmic_msg();
extern void build_status_notify_packet();
extern void mark_master_or_low_battery_flag();
extern void post_notification_cmd_process();
extern void FUN_00056a68();
extern void z_impl_k_timer_start();
extern void FUN_0007c176();
extern void FUN_0007c1aa();
extern void ble_flush_queued_indications();
extern void memcpy();
extern void FUN_00086c1e();
extern void memset_bytes();
extern void strcpy();
extern void ble_process_get_req();
extern void ble_process_put_req();

#define LVL_A (*(volatile int32_t*)((uintptr_t)&g_log_level) /*=0x2000230c*/)
#define LVL_B (*(volatile int32_t*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/)
#define G_20007570 (*(volatile uint32_t*)((uintptr_t)&g_dashboard_lock_ready_flags) /*=0x20007570*/)
#define G_2000756c (*(volatile uint32_t*)((uintptr_t)&g_dashboard_lock_sent_flags) /*=0x2000756c*/)
#define G_20018d9b (*(volatile uint8_t*)((uintptr_t)&g_ble_dispatch_pending_marker) /*=0x20018d9b*/)
#define G_20018d9a (*(volatile uint8_t*)((uintptr_t)&g_ble_xfer_seq_cur) /*=0x20018d9a*/)
#define G_20018d99 (*(volatile uint8_t*)((uintptr_t)&g_ble_xfer_seq_prev) /*=0x20018d99*/)

typedef void (*fp_t)(void);

unsigned int ble_process_req_dispatch(uint8_t *param_1, uint8_t *packet, uint8_t *param_3)
{
    uint32_t command_id = *packet;
    uint32_t *puVar15;
    int32_t iVar13, iVar14;
    uint8_t bVar10, bVar3;
    uint16_t uVar2;
    uint8_t returnStatus;
    uint8_t *puVar12;

    if ((uint32_t)(command_id - 1) < 0x27u) {
        ble_process_put_req();
        return 0;
    }
    if ((uint32_t)(command_id - 0x29u) < 0x1du) {
        ble_process_get_req();
        return 0;
    }
    if ((uint32_t)(command_id - 0x47u) > 9u) {
        if (((command_id + 0xfu) & 0xffu) > 5u) {
            if (0 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
            {
                fp_t pc = *(fp_t *)(param_1 + 0xc);
                pc();
            }
            return 0;
        }
        memset_bytes();
        if (command_id == 0xf4) { ble_flush_queued_indications(); return 0; }
        if (command_id == 0xf5) { build_status_notify_packet(); return 0; }
        if (command_id == 0xf1) {
            if ((*(volatile uint8_t *)(param_3 + 2) & 0xfd) == 0xc9) { return 0; }
            if (*(volatile uint8_t *)(param_3 + 2) == 0xcc) { send_dmic_msg(); return 0; }
            if (1 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        } else if (1 < LVL_A) {
            if (LVL_B == 0) DEBUG_PRINT(); else debug_print();
        }
        strcpy();
        {
            fp_t pc = *(fp_t *)(param_1 + 0xc);
            pc();
        }
        return 0;
    }

    puVar15 = *(volatile uint32_t **)(param_1 + 0x10);
    memset_bytes();
    *puVar15 = *(volatile uint32_t *)packet;
    *(volatile uint32_t *)(param_1 + 0x14) = (uint32_t)*(volatile uint16_t *)(packet + 2) + 4;

    switch (*packet) {
    case 0x47: {
        if (1 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        {
            fp_t pc = *(fp_t *)(param_1 + 0xc);
            pc();
        }
        iVar13 = FUN_00019b2c();
        if (iVar13 == 0) { return 0; }
        if (0 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        FUN_00056a68();
        return 0;
    }
    default:
        if (1 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        strcpy();
        break;
    case 0x49:
    case 0x4d:
        goto switchD_caseD_49;
    case 0x4a:
        *puVar15 = *(volatile uint32_t *)packet;
        memcpy();
        *(volatile uint32_t *)(param_1 + 0x14) = (uint32_t)*(volatile uint16_t *)(packet + 2) + 4;
        goto switchD_caseD_49;
    case 0x4b:
        post_notification_cmd_process();
        return 0;
    case 0x4c:
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        memcpy();
switchD_caseD_49:
        audio_fw_load_get_wrapper();
        break;
    case 0x4e:
        if (*(volatile int16_t *)(packet + 2) != 0) {
            memset_bytes();
            if ((uint32_t)*(volatile uint8_t *)(param_3 + 3) ==
                (uint32_t)(uint8_t)(*(volatile uint8_t *)(param_3 + 2) - 1)) {
                returnStatus = 0xc9;
            } else {
                iVar13 = get_device_info();
                iVar13 = get_device_info();
                FUN_0007c1aa();
                FUN_0007c176();
                returnStatus = 0xcb;
            }
            FUN_00086c1e();
        }
        if (*(volatile int8_t *)(param_3 + 3) == 0) {
            iVar13 = get_device_info();
            memset_bytes();
            iVar13 = get_device_info();
            iVar14 = *(volatile int32_t *)(iVar13 + 0x100c);
            *(volatile uint8_t *)(iVar14 + 0x197) = 0;
            *(volatile uint8_t *)(iVar14 + 0x198) = 0;
            iVar13 = get_device_info();
            *(volatile uint8_t *)(*(volatile int32_t *)(iVar13 + 0x100c) + 1) =
                *(volatile uint8_t *)(param_3 + 4);
            bVar10 = *(volatile uint8_t *)(param_3 + 5);
            bVar3 = *(volatile uint8_t *)(param_3 + 6);
            iVar13 = get_device_info();
            *(volatile uint16_t *)(*(volatile int32_t *)(iVar13 + 0x100c) + 2) =
                (uint16_t)((uint16_t)bVar10 * 0x100 + (uint16_t)bVar3);
            iVar13 = get_device_info();
            *(volatile uint8_t *)(*(volatile int32_t *)(iVar13 + 0x100c) + 4) =
                *(volatile uint8_t *)(param_3 + 7);
            iVar13 = get_device_info();
            *(volatile uint8_t *)(*(volatile int32_t *)(iVar13 + 0x100c) + 5) =
                *(volatile uint8_t *)(param_3 + 8);
        }
        iVar13 = get_device_info();
        iVar13 = get_device_info();
        memcpy();
        iVar13 = get_device_info();
        *(volatile int16_t *)(*(volatile int32_t *)(iVar13 + 0x100c) + 0x197) =
            (int16_t)(*(volatile int16_t *)(*(volatile int32_t *)(iVar13 + 0x100c) + 0x197) +
                      *(volatile int16_t *)(packet + 2) - 9);
        uVar2 = *(volatile uint16_t *)(packet + 2);
        *(volatile uint16_t *)((uint8_t *)puVar15 + 2) = uVar2;
        *(volatile uint32_t *)(param_1 + 0x14) = (uint32_t)uVar2 + 4;
        if ((uint32_t)*(volatile uint8_t *)(param_3 + 3) ==
            (uint32_t)(uint8_t)(*(volatile uint8_t *)(param_3 + 2) - 1)) {
            audio_fw_load_get_wrapper();
            bVar10 = *(volatile uint8_t *)(param_3 + 4) & 0xf0;
            if (bVar10 == 0x60) {
                mark_master_or_low_battery_flag();
                iVar13 = get_device_info();
                *(volatile uint8_t *)(*(volatile int32_t *)(iVar13 + 0x100c)) = 10;
            } else {
                if (bVar10 == 0x70) {
                    iVar13 = get_device_info();
                    returnStatus = 0xf;
                    puVar12 = *(volatile uint8_t **)(iVar13 + 0x100c);
LAB_00021706:
                    *puVar12 = returnStatus;
                    iVar13 = get_device_info();
                    returnStatus = 0;
                } else {
                    iVar13 = get_device_info();
                    bVar10 = *(volatile uint8_t *)(param_3 + 4) & 0xf0;
                    if (*(volatile int8_t *)(*(volatile int32_t *)(iVar13 + 0x100c)) == 6) {
                        if (bVar10 == 0x40) goto LAB_0002175e;
                    } else if (bVar10 != 0x30) {
                        if (bVar10 == 0x40) {
LAB_0002175e:
                            iVar13 = get_device_info();
                            *(volatile uint8_t *)(*(volatile int32_t *)(iVar13 + 0x100c)) = 8;
                            iVar13 = get_device_info();
                            *(volatile uint8_t *)(iVar13 + 0xdb) = 8;
                        } else {
                            iVar13 = get_device_info();
                            if (6 < *(volatile uint8_t *)(*(volatile int32_t *)(iVar13 + 0x100c))) {
                                bVar10 = *(volatile uint8_t *)(param_3 + 4) & 0xf0;
                                if (bVar10 == 0x40) goto LAB_0002175e;
                                if (bVar10 == 0x50) {
                                    iVar13 = get_device_info();
                                    returnStatus = 9;
                                    puVar12 = *(volatile uint8_t **)(iVar13 + 0x100c);
                                    goto LAB_00021706;
                                }
                            }
                        }
                        goto LAB_000216b4;
                    }
                    iVar13 = get_device_info();
                    *(volatile uint8_t *)(*(volatile int32_t *)(iVar13 + 0x100c)) = 7;
                    iVar13 = get_device_info();
                    returnStatus = 0x10;
                }
                *(volatile uint8_t *)(iVar13 + 0xdb) = returnStatus;
            }
        }
LAB_000216b4:
        iVar13 = get_device_type();
        bVar10 = *(volatile uint8_t *)(param_3 + 3);
        bVar3 = *(volatile uint8_t *)(param_3 + 2);
        if (iVar13 == 1) {
            if ((uint32_t)bVar10 == (uint32_t)(uint8_t)(bVar3 - 1)) {
                G_20018d9b = 0x4e;
                G_20018d9a = bVar3;
                G_20018d99 = bVar10;
                FUN_0007c176();
                return 0;
            }
        } else if ((uint32_t)bVar10 == (uint32_t)(uint8_t)(bVar3 - 1)) {
            FUN_0007c176();
        }
        break;
    case 0x4f:
        *puVar15 = *(volatile uint32_t *)packet;
        memcpy();
        audio_fw_load_get_wrapper();
        break;
    case 0x50:
        if (*(volatile int16_t *)(param_3 + 1) == *(volatile int16_t *)(packet + 2)) {
            int8_t cVar1;
            volatile int8_t *pcVar8;
            int32_t iVar13x;
            if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
            cVar1 = *(volatile int8_t *)(param_3 + 4);
            pcVar8 = (volatile int8_t *)(intptr_t)get_device_info();
            if (*pcVar8 == 1) {
                if (cVar1 == 1) {
                    if ((int32_t)(G_20007570 << 0x1e) < 0) { return 0; }
                    if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
                    G_20007570 = G_20007570 | 2;
                    {
                        uint32_t tmp = G_2000756c;
                        G_2000756c = tmp & 0xfffffffdu;
                    }
                    z_impl_k_timer_start();
                    return 0;
                }
                if (LVL_A < 1) { return 0; }
                iVar13x = LVL_B;
            } else {
                if (LVL_A < 1) { return 0; }
                iVar13x = LVL_B;
            }
            if (iVar13x != 0) { debug_print(); return 0; }
            DEBUG_PRINT();
            return 0;
        }
        if (LVL_A < 2) { return 0; }
        if (LVL_B != 0) { debug_print(); return 0; }
        DEBUG_PRINT();
        return 0;
    }

    {
        fp_t pc = *(fp_t *)(param_1 + 0xc);
        pc();
    }
    return 0;
}

