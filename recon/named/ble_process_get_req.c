/* named: ble_process_get_req */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20018462  g_ui_mode_flag               
*/
/* Reconstructed ble_process_get_req @ 0x1a064  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <stddef.h>

extern void DEBUG_PRINT();
extern int  get_device_type();
extern int  get_device_info();
extern void audio_fw_load_get_wrapper();
extern void debug_print();
extern void get_notification_counts_cmd_process();
extern void send_whitelist_json_chunked();
extern void SendSystemLanguageInfoToSlave();
extern void debug_print_hex_dump();
extern int  is_system_idle_ready();
extern void memcpy();
extern void FUN_00086c1e();
extern void memset_bytes();
extern void strcpy();

#define LVL_A (*(volatile int32_t*)0x2000230cUL)
#define LVL_B (*(volatile int32_t*)0x20007554UL)
#define G_20018462 (*(volatile uint8_t*)0x20018462UL)

typedef void (*fp_t)(void);

void ble_process_get_req(uint8_t *param_1, uint8_t *packet, uint8_t *param_3)
{
    uint8_t switchval;
    int32_t iVar9;
    uint8_t uVar1;

    memset_bytes();
    *(*(volatile uint32_t **)(param_1 + 0x10)) = *(volatile uint32_t *)packet;
    *(volatile uint32_t *)(param_1 + 0x14) = (uint32_t)*(volatile uint16_t *)(packet + 2);
    switchval = *packet;

    switch (switchval) {
    case 0x29:
        audio_fw_load_get_wrapper();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        break;
    case 0x2a:
        audio_fw_load_get_wrapper();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        break;
    case 0x2b:
        audio_fw_load_get_wrapper();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        break;
    case 0x2c:
        if (*(volatile int8_t *)(param_3 + 1) == 1) {
            *(volatile uint8_t *)(param_1 + 0x8ec) = 0;
        } else if (*(volatile int8_t *)(param_3 + 1) == 2) {
            *(volatile uint8_t *)(param_1 + 0x8ec) = 1;
        }
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        audio_fw_load_get_wrapper();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        break;
    case 0x2d:
        audio_fw_load_get_wrapper();
        debug_print_hex_dump();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        break;
    case 0x2e:
        send_whitelist_json_chunked();
        return;
    case 0x32:
        audio_fw_load_get_wrapper();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        break;
    case 0x33:
        audio_fw_load_get_wrapper();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        break;
    case 0x34:
        audio_fw_load_get_wrapper();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        break;
    case 0x35:
        audio_fw_load_get_wrapper();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        break;
    case 0x36:
        get_notification_counts_cmd_process();
        return;
    case 0x37:
        audio_fw_load_get_wrapper();
        break;
    case 0x38:
        if (0 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        break;
    case 0x39:
        if (*(volatile int16_t *)(param_3 + 1) == *(volatile int16_t *)(packet + 2)) {
            memset_bytes();
            iVar9 = is_system_idle_ready();
            if (iVar9 == 0) {
                if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
            } else {
                if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
            }
        } else {
            if (0 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
            memset_bytes();
        }
        break;
    case 0x3a:
        if (0 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        break;
    case 0x3b:
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        break;
    case 0x3c:
        if (0 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        break;
    case 0x3d: {
        int16_t uVar16 = *(volatile int16_t *)(param_3 + 1);
        int16_t uVar13 = *(volatile int16_t *)(packet + 2);
        if (uVar16 != uVar13) {
            if (LVL_A < 2) { return; }
            if (LVL_B != 0) { debug_print(); return; }
            DEBUG_PRINT();
            return;
        }
        uVar1 = *(volatile uint8_t *)(param_3 + 5);
        memset_bytes();
        FUN_00086c1e();
        iVar9 = get_device_type();
        G_20018462 = uVar1;
        if (iVar9 == 1) { SendSystemLanguageInfoToSlave(); }
        break;
    }
    case 0x3e:
        if (0 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        iVar9 = get_device_info();
        memcpy();
        memcpy();
        break;
    default:
        if (1 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else debug_print(); }
        strcpy();
        break;
    }

    {
        fp_t pcVar14 = *(fp_t *)(param_1 + 0xc);
        pcVar14();
    }
}

