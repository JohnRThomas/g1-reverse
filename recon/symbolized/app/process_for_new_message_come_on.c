#include "g1_app_symbols.h"
/* named: process_for_new_message_come_on */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed process_for_new_message_come_on @ 0x2c498  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned char undefined1;
extern void DEBUG_PRINT(unsigned, ...);
extern int get_device_info(void);
extern void debug_print(unsigned, ...);
extern void trigger_screen_state_change(unsigned a, byte *b, uint c);
extern void update_temp_task_status(byte *a, int b, int c);
extern void update_persist_task_status_to_idle(byte *a);
extern void update_persist_task_status_to_wait_blow_head(void);
extern void check_pending_messages_flag(void);
extern void sync_message_signal_to_slave(int a);
extern unsigned char get_message_type_param(byte a, int b, ...);
extern void clear_timeout_message(int a);
extern int get_message_entry(int a);
extern void push_message_3439c(void);
extern void FUN_0003443c(int a);
extern void set_new_message_pending_flag(void);
extern void sync_to_slave(byte *a, int b, int c);
extern void thunk_FUN_00074844(int a, int b);

undefined1 process_for_new_message_come_on(byte *param_1, int param_2, char *param_3, unsigned *param_4)
{
    volatile int *piVar1 = (volatile int *)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    volatile int *piVar2 = (volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
    undefined1 uVar3;
    int iVar4, iVar6;
    int *piVar5;
    char cVar7;
    uint uVar8, uVar9;
    int bVar10;

    uVar3 = get_message_type_param(param_1[0xfea], 0xf, param_3, param_4, param_1, param_2, param_3);
    *(volatile undefined1 *)(param_2 + 7) = uVar3;
    FUN_0003443c(2);
    iVar4 = get_device_info();
    uVar9 = 0;
    piVar5 = (int *)get_message_entry(*(volatile byte *)(iVar4 + 0xdd) - 1);
    iVar4 = *piVar5;
    do {
        if (((param_1[1] == 1) || (iVar6 = get_device_info(), *(volatile char *)(iVar6 + 1) == '\b')) ||
            (iVar6 = get_device_info(), *(volatile char *)(iVar6 + 0xfea) == '\f')) {
            if (2 < *piVar1) {
                if (*piVar2 == 0) DEBUG_PRINT(0, 0, (uint)*(volatile byte *)(param_2 + 1));
                else debug_print(0);
            }
            update_persist_task_status_to_idle(param_1);
            *param_4 = "message:imu-trigger-off-imm" /*=0xa2795*/;
            goto LAB_0002c4ec;
        }
        iVar6 = iVar4;
        if (*param_1 == 1) {
            iVar6 = get_device_info();
            piVar5 = (int *)get_message_entry(*(volatile byte *)(iVar6 + 0xdd) - 1);
            iVar6 = *piVar5;
            if (iVar6 != iVar4) {
                uVar3 = get_message_type_param(param_1[0xfea], 0xf);
                *(volatile undefined1 *)(param_2 + 7) = uVar3;
            }
        }
        if (*(volatile char *)(param_2 + 1) != '\x05') {
            if (*piVar1 < 1) return 0xb;
            if (*piVar2 != 0) { debug_print(0); return 0xb; }
            DEBUG_PRINT(0, 0, (uint)*(volatile byte *)(param_2 + 1));
            return 0xb;
        }
        if ((*param_3 == '\x02') || (param_1[0xfea] == 0xb)) {
            if (2 < *piVar1) { if (*piVar2 == 0) DEBUG_PRINT(0, 0); else debug_print(0); }
            set_new_message_pending_flag();
            if (2 < *piVar1) { if (*piVar2 == 0) DEBUG_PRINT(0, 0); else debug_print(0); }
            if (param_1[0xb0d] == 1) {
                update_temp_task_status(param_1, 8, 2);
                FUN_0003443c(4);
                return 0xb;
            }
            if ((*(volatile char *)(param_2 + 1) == '\x05') && (uVar8 = (uint)*param_1, uVar8 == 1)) {
                sync_message_signal_to_slave(1);
                clear_timeout_message(0);
                check_pending_messages_flag();
                push_message_3439c();
                update_temp_task_status(param_1, 4, 2);
                trigger_screen_state_change("IMU:wakeup:new-notification" /*=0xa0a7b*/, param_1, uVar8);
                if (*piVar1 < 1) return 0xb;
                if (*piVar2 != 0) { debug_print(0); return 0xb; }
                DEBUG_PRINT(0, 0);
                return 0xb;
            }
        }
        uVar9 = uVar9 + 1;
        if (((uVar9 & 0xf) == 0) && (2 < *piVar1)) {
            if (*piVar2 == 0) DEBUG_PRINT(0, 0, (uint)*(volatile byte *)(param_2 + 7));
            else debug_print(0);
        }
        thunk_FUN_00074844(0x667, 0);
        if (*param_1 == 1) {
            uVar8 = uVar9 * -0x33333333;
            bVar10 = (uVar8 >> 2 | uVar9 * 0x40000000) <= 0xccccccc;
            if (bVar10) uVar8 = (uint)*(volatile byte *)(param_2 + 7);
            cVar7 = (char)uVar8;
            if (bVar10) cVar7 = cVar7 + -1;
            if (bVar10) *(volatile char *)(param_2 + 7) = cVar7;
        }
        iVar4 = iVar6;
    } while (*(volatile char *)(param_2 + 7) != '\0');
    param_1[0xb0d] = 0;
    uVar3 = 0;
    if (*(volatile char *)(param_2 + 7) == '\0') {
        if (2 < *piVar1) { if (*piVar2 == 0) DEBUG_PRINT(0, 0, (uint)*(volatile byte *)(param_2 + 1)); else debug_print(0); }
        *param_4 = "new-msg-timeout-goto-idle" /*=0xa28d4*/;
        sync_to_slave(param_1, 8, 0);
        if (*param_3 == '\x02') update_persist_task_status_to_wait_blow_head();
        else update_persist_task_status_to_idle(param_1);
        FUN_0003443c(6);
LAB_0002c4ec:
        uVar3 = 10;
    }
    return uVar3;
}

