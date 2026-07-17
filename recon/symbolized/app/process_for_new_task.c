#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002c99c @ 0x0002c99c
 * public-name: process_for_new_task
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   check_charging_and_touch_flags           <= FUN_00026c28 @ 0x00026c28
 *   trigger_screen_state_change              <= FUN_0002bc2c @ 0x0002bc2c
 *   now_has_persist_task                     <= FUN_0002be64 @ 0x0002be64
 *   update_temp_task_status                  <= FUN_0002bffc @ 0x0002bffc
 *   update_persist_task_status_to_idle       <= FUN_0002c0e8 @ 0x0002c0e8
 *   update_persist_task_status_to_wait_blow_head <= FUN_0002c180 @ 0x0002c180
 *   check_pending_messages_flag              <= FUN_0002c1fc @ 0x0002c1fc
 *   sync_message_signal_to_slave             <= FUN_0002c224 @ 0x0002c224
 *   wait_touch_key_release_or_timeout        <= FUN_0002c2b0 @ 0x0002c2b0
 *   process_for_new_message_come_on          <= FUN_0002c498 @ 0x0002c498
 *   process_for_message_show                 <= FUN_0002c714 @ 0x0002c714
 *   check_ancs_inbox_flag_change             <= FUN_0002eb40 @ 0x0002eb40
 *   mark_master_or_low_battery_flag          <= FUN_0002efc0 @ 0x0002efc0
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   msg_content_used_count                   <= FUN_00033cdc @ 0x00033cdc
 *   msg_content_recalc_unread                <= FUN_00033cf8 @ 0x00033cf8
 *   clear_timeout_message                    <= FUN_00033d58 @ 0x00033d58
 *   push_message_3439c                       <= FUN_0003439c @ 0x0003439c
 *   is_msg_expiration                        <= FUN_0003444c @ 0x0003444c
 *   set_new_message_pending_flag             <= FUN_00036030 @ 0x00036030
 *   clear_notification_display_buffer        <= FUN_0003cf34 @ 0x0003cf34
 *   reset_esb_sync_state                     <= FUN_0007ce60 @ 0x0007ce60
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_a0a47                             @ 0x000a0a47
 *   rodata_a0a61                             @ 0x000a0a61
 *   rodata_a2733                             @ 0x000a2733
 *   rodata_a2768                             @ 0x000a2768
 *   rodata_a2831                             @ 0x000a2831
 *   rodata_a291d                             @ 0x000a291d
 *   rodata_a294a                             @ 0x000a294a
 *   rodata_a2a21                             @ 0x000a2a21
 *   rodata_a2a32                             @ 0x000a2a32
 *   rodata_a2ad4                             @ 0x000a2ad4
 *   rodata_a2ba7                             @ 0x000a2ba7
 *   rodata_a2c70                             @ 0x000a2c70
 *   rodata_a2ce2                             @ 0x000a2ce2
 *   rodata_a2cfc                             @ 0x000a2cfc
 *   rodata_a2d5a                             @ 0x000a2d5a
 *   rodata_a2de3                             @ 0x000a2de3
 *   rodata_a2e5b                             @ 0x000a2e5b
 *   rodata_a2e7c                             @ 0x000a2e7c
 *   rodata_a2f08                             @ 0x000a2f08
 *   rodata_a2f7e                             @ 0x000a2f7e
 *   rodata_a2f9c                             @ 0x000a2f9c
 *   rodata_a3071                             @ 0x000a3071
 *   rodata_a30e5                             @ 0x000a30e5
 *   rodata_a3104                             @ 0x000a3104
 *   rodata_a318d                             @ 0x000a318d
 *   rodata_a3201                             @ 0x000a3201
 *   rodata_a3215                             @ 0x000a3215
 *   rodata_a3244                             @ 0x000a3244
 *   rodata_a32df                             @ 0x000a32df
 *   rodata_a32ef                             @ 0x000a32ef
 *   rodata_a3305                             @ 0x000a3305
 *   rodata_a3311                             @ 0x000a3311
 *   rodata_a3325                             @ 0x000a3325
 *   rodata_a339b                             @ 0x000a339b
 *   rodata_a33aa                             @ 0x000a33aa
 *   rodata_a33bf                             @ 0x000a33bf
 *   rodata_a33de                             @ 0x000a33de
 *   rodata_a3456                             @ 0x000a3456
 *   rodata_a3468                             @ 0x000a3468
 *   rodata_a3480                             @ 0x000a3480
 *   rodata_a34a2                             @ 0x000a34a2
 *   rodata_a35cd                             @ 0x000a35cd
 *   rodata_a35df                             @ 0x000a35df
 *   rodata_a35f7                             @ 0x000a35f7
 *   rodata_a3619                             @ 0x000a3619
 *   rodata_a3758                             @ 0x000a3758
 *   rodata_a37f6                             @ 0x000a37f6
 *   rodata_a383d                             @ 0x000a383d
 *   rodata_a3886                             @ 0x000a3886
 *   rodata_a38be                             @ 0x000a38be
 *   rodata_a38dd                             @ 0x000a38dd
 *   rodata_a38f9                             @ 0x000a38f9
 *   rodata_a3930                             @ 0x000a3930
 *   rodata_a394b                             @ 0x000a394b
 *   rodata_a3967                             @ 0x000a3967
 *   rodata_a3982                             @ 0x000a3982
 *   rodata_a39a0                             @ 0x000a39a0
 *   rodata_a39bb                             @ 0x000a39bb
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_20007b38                               @ 0x20007b38
 *   g_pending_message_flag                   @ 0x20018d9e
 *   g_esb_notify_slave_role_guard            @ 0x20018d9f
 */
/* Reconstructed process_for_new_task @ 0x2c99c  (parity: 295/300 trials, PROVEN) */
typedef unsigned char      u8;
typedef unsigned int       u32;
typedef unsigned long long u64;

/* callees (opaque oracles) -> single index-keyed oracle */
extern int g_oracle(void);
#define DEBUG_PRINT(...) g_oracle()
#define get_device_info(...) g_oracle()
#define debug_print(...) g_oracle()
#define FUN_00023eec(...) g_oracle()
#define check_charging_and_touch_flags(...) g_oracle()
#define trigger_screen_state_change(...) g_oracle()
#define now_has_persist_task(...) g_oracle()
#define update_temp_task_status(...) g_oracle()
#define update_persist_task_status_to_idle(...) g_oracle()
#define update_persist_task_status_to_wait_blow_head(...) g_oracle()
#define check_pending_messages_flag(...) g_oracle()
#define FUN_0002c214(...) g_oracle()
#define sync_message_signal_to_slave(...) g_oracle()
#define wait_touch_key_release_or_timeout(...) g_oracle()
#define process_for_new_message_come_on(...) g_oracle()
#define process_for_message_show(...) g_oracle()
#define check_ancs_inbox_flag_change(...) g_oracle()
#define mark_master_or_low_battery_flag(...) g_oracle()
#define is_battery_critical(...) g_oracle()
#define msg_content_used_count(...) g_oracle()
#define msg_content_recalc_unread(...) g_oracle()
#define clear_timeout_message(...) g_oracle()
#define push_message_3439c(...) g_oracle()
#define FUN_00034410(...) g_oracle()
#define FUN_0003443c(...) g_oracle()
#define is_msg_expiration(...) g_oracle()
#define FUN_00034808(...) g_oracle()
#define set_new_message_pending_flag(...) g_oracle()
#define clear_notification_display_buffer(...) g_oracle()
#define FUN_00072880(...) g_oracle()
#define FUN_0007c132(...) g_oracle()
#define reset_esb_sync_state(...) g_oracle()
#define memset_bytes(...) g_oracle()
#define send_event_status(...) g_oracle()
#define sync_to_slave(...) g_oracle()
#define thunk_FUN_00074844(...) g_oracle()
#define update_persist_task_status(...) g_oracle()

/* dereferenced RAM globals (exact literal addresses from the literal pool) */
#define G_18d9f  (*(volatile u8 *)((unsigned long)&g_esb_notify_slave_role_guard) /*=0x20018d9f*/)   /* byte store */
#define G_18d9e  (*(volatile char *)((unsigned long)&g_pending_message_flag) /*=0x20018d9e*/) /* byte read  */
#define V230C    (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/)  /* verbose level */
#define V7554    (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)  /* mode flag     */
#define P7B38    ((volatile u32 *)((unsigned long)&g_20007b38) /*=0x20007b38*/)   /* atomic flags  */

int process_for_new_task(char *param_1, u8 *param_2)
{
    u8  bVar1;
    volatile int *piVar2;
    volatile u32 *puVar3;
    volatile int *piVar4,*piVar5,*piVar6,*piVar7,*piVar8,*piVar9,*piVar10;
    u8  uVar11;
    char cVar12;
    int iVar13;
    u32 uVar14, uVar15;
    u8 *puVar16;
    u32 uVar17;
    int iVar18;
    u32 uVar19;
    char *pcVar20;
    u32 *puVar21;
    u64 uVar22;
    int local_2c[2];
    int sel;

    iVar18 = 0;
    local_2c[0] = 0;
LAB_0002c9b6:
    memset_bytes(param_1 + 0xef, 0);
    clear_timeout_message(0);
    if (*param_1 == '\x01') {
        wait_touch_key_release_or_timeout(0);
    }
    if (param_1[0xd5] != '\x04') {
        G_18d9f = 0;
    }
    piVar10 = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    piVar9  = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    piVar8  = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    piVar7  = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    piVar6  = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    piVar5  = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    piVar4  = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    piVar2  = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;

    sel = (u8)param_1[0xd5];
    if      (sel == 0)    goto CASE0;
    else if (sel == 1)    goto CASE1;
    else if (sel == 2)    goto CASE2;
    else if (sel == 4)    goto CASE4;
    else if (sel == 5)    goto CASE5;
    else if (sel == 6)    goto CASE6;
    else if (sel == 7)    goto CASE7;
    else if (sel == 8)    goto CASE8;
    else if (sel == 9)    goto CASE9;
    else if (sel == 10)   goto CASE10;
    else if (sel == 11)   goto CASE11;
    else if (sel == 12)   goto CASE12;
    else if (sel == 14)   goto CASE14;
    else if (sel == 15)   goto CASE15;
    else if (sel == 16)   goto CASE16;
    else if (sel == 17)   goto CASE17;
    else goto CASE_DEFAULT;

CASE0:
    if (2 < V230C) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    puVar21 = *(u32 **)(param_1 + 0x1054);
    reset_esb_sync_state(1);
    iVar18 = now_has_persist_task(param_1, param_1[0xd5]);
    if (iVar18 == 0) {
        if (*param_2 != 2) {
            trigger_screen_state_change(0, param_1, 0);
            pcVar20 = (char *)get_device_info(0);
            if ((*pcVar20 == '\x02') && (iVar18 = get_device_info(0), *(int *)(iVar18 + 0x40) == 0)) {
                iVar18 = get_device_info(0);
                FUN_00072880(iVar18 + 0x38);
            }
        }
        param_1[0xd5] = '\0';
        puVar16 = *(u8 **)(param_1 + 0x1054);
        *puVar16 = 0;
        puVar16[1] = 0;
        puVar16[2] = 0;
        puVar16[3] = 0;
        *(u8 *)(*(int *)(param_1 + 0x1054) + 4) = 1;
        iVar18 = is_msg_expiration(0);
        if (iVar18 == 1) {
            cVar12 = '\x05';
        } else {
            iVar18 = get_device_info(0);
            cVar12 = *(char *)(iVar18 + 0xdd);
            if (cVar12 != '\0') cVar12 = '\x06';
        }
        FUN_0003443c(cVar12);
        FUN_0002c214(0);
        if (*param_2 != 2) {
            iVar18 = 100;
            do {
                if (param_1[0xfe6] == '\x01') break;
                thunk_FUN_00074844(0x148, 0);
                iVar18 = iVar18 + -1;
            } while (iVar18 != 0);
        }
        if (1 < *piVar10) {
            if (V7554 == 0) DEBUG_PRINT(0);
            else            debug_print(0);
        }
    }
    G_18d9f = 0;                       /* *DAT_0002e0fc = 0 (same addr, byte) */
    if (2 < *piVar10) {
        if (V7554 == 0) { iVar18 = get_device_info(0); DEBUG_PRINT(0); }
        else            { iVar18 = get_device_info(0); debug_print(0); }
    }
    puVar3 = P7B38;
    piVar2 = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uVar19 = 0;
LAB_0002df4c:
    if ((param_1[1] == '\x01') || (iVar18 = get_device_info(0), *(char *)(iVar18 + 1) == '\b')) {
LAB_0002e012:
        iVar13 = local_2c[0];
        if (*param_1 == '\x01') {
            (*(void (**)(void *, int))(param_2 + 0x98))(param_2, 0x26);
            iVar13 = local_2c[0];
        }
        goto LAB_0002ce1c;
    }
    cVar12 = (char)check_ancs_inbox_flag_change(0);
    if (cVar12 != '\0') goto LAB_0002df66;
    if ((param_1[0xfea] != '\f') || (**(int **)(param_1 + 0x1054) == 7)) {
        uVar22 = (u64)(unsigned)now_has_persist_task(param_1, param_1[0xd5]);
        uVar14 = 0;
        iVar18 = (int)uVar22;
        if (iVar18 == 1) {
            param_1[0xd5] = (char)*puVar21;
LAB_0002e00e:
            trigger_screen_state_change(uVar14, param_1, 1);
            goto LAB_0002e012;
        }
        iVar18 = is_battery_critical(iVar18, (int)(uVar22 >> 0x20), iVar18);
        if (iVar18 != 1) {
            if (((*(char *)(*(int *)(param_1 + 0x1014) + 1) == '\0') &&
                 (iVar18 = FUN_0007c132(0), iVar18 != 0)) &&
                (iVar18 = get_device_info(0), *(char *)(*(int *)(iVar18 + 0x1010) + 1) == '\0')) {
                if (((*param_2 == 2) && (iVar18 = FUN_00023eec(0), iVar18 == 0)) ||
                    (((int)(*puVar3 << 0x1e) < 0 && (iVar18 = FUN_00023eec(0), iVar18 == 1)))) {
                    if ((int)(*puVar3 << 0x1e) < 0) {
                        *puVar3 = *puVar3 & 0xfffffffd;
                    }
                    iVar18 = FUN_00034808(0);
                    if (iVar18 == 0) {
                        update_temp_task_status(param_1, 6, 2);
                        uVar14 = ((unsigned long)&rodata_a2733) /*=0xa2733*/;
                        goto LAB_0002cd8c;
                    }
                    set_new_message_pending_flag(0);
                    if (*param_1 == '\x01') {
                        sync_message_signal_to_slave(1);
                        clear_timeout_message(0);
                        check_pending_messages_flag(0);
                        push_message_3439c(0);
                        update_temp_task_status(param_1, 4, 2);
                        trigger_screen_state_change(((unsigned long)&rodata_a0a61) /*=0xa0a61*/, param_1, 1);
                    } else if (param_1[0xd5] != '\x04') {
                        goto LAB_0002e084;
                    }
                    if (*piVar10 < 1) goto LAB_0002cf58;
                    iVar18 = V7554;
                    uVar14 = 0xa37a8;
                    goto LAB_0002e184;
                }
LAB_0002e084:
                iVar18 = FUN_00034410(0);
                if (iVar18 == 1) {
                    if (param_1[0x108f] == '\0') {
                        if (*param_1 == '\x01') {
                            sync_message_signal_to_slave(0);
                            update_temp_task_status(param_1, 5, 2);
                            trigger_screen_state_change(((unsigned long)&rodata_a0a47) /*=0xa0a47*/, param_1, 1);
                            if (*piVar10 < 1) goto LAB_0002cf58;
                            iVar18 = V7554;
                            uVar14 = ((unsigned long)&rodata_a2831) /*=0xa2831*/;
                            goto LAB_0002e184;
                        }
                        if (param_1[0xd5] != '\x05') goto LAB_0002e040;
                        if (0 < *piVar10) {
                            iVar18 = V7554;
                            uVar14 = 0xa37c8;
LAB_0002e184:
                            if (iVar18 == 0) DEBUG_PRINT(uVar14);
                            else             debug_print(0);
                        }
                        goto LAB_0002cf58;
                    }
                    set_new_message_pending_flag(0);
                    if (*param_1 == '\x01') {
                        sync_message_signal_to_slave(1);
                        clear_timeout_message(0);
                        check_pending_messages_flag(0);
                        push_message_3439c(0);
                        update_temp_task_status(param_1, 4, 2);
                        uVar14 = ((unsigned long)&rodata_a0a61) /*=0xa0a61*/;
                        goto LAB_0002cd8c;
                    }
                    if (param_1[0xd5] == '\x04') goto LAB_0002ccda;
                }
                if ((param_1[0x108f] != '\0') && (uVar14 = ((unsigned long)&rodata_a37f6) /*=0xa37f6*/, param_1[0xd5] == '\x04'))
                    goto LAB_0002e00e;
            } else {
                uVar19 = uVar19 + 1;
                if (((uVar19 & 0x1f) == 0) && (0 < *piVar10)) {
                    if (V7554 == 0) DEBUG_PRINT(0);
                    else            debug_print(0);
                }
            }
        }
    }
LAB_0002e040:
    uVar19 = uVar19 + 1;
    if (*param_1 == '\x01') {
        (*(void (**)(void *, int))(param_2 + 0x98))(param_2, 0x50);
    }
LAB_0002df66:
    thunk_FUN_00074844(0x667, 0);
    goto LAB_0002df4c;

CASE1:
    if (2 < V230C) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    trigger_screen_state_change(((unsigned long)&rodata_a383d) /*=0xa383d*/, param_1, 0);
    while ((*param_2 != 1 && (iVar18 = FUN_00023eec(0), iVar18 != 1))) {
        if (((char)((int *)*(int **)(param_1 + 0x1054))[1] == '\x02') &&
            (**(int **)(param_1 + 0x1054) == 0x10)) {
            param_1[0xd5] = '\x10';
            trigger_screen_state_change(((unsigned long)&rodata_a3758) /*=0xa3758*/, param_1, 1);
            iVar13 = local_2c[0];
            goto LAB_0002ce1c;
        }
        thunk_FUN_00074844(0x667, 0);
    }
    uVar17 = 0;
LAB_0002cb9a:
    param_1[0xd5] = (char)uVar17;
    goto LAB_0002cf58;

CASE2:
    if (2 < V230C) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    piVar2 = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uVar19 = 0;
    while (1) {
        if ((*(char *)(*(int *)(param_1 + 0xff0) + 5) == '\0') || (param_1[0xfea] != '\n')) {
            if (2 < *piVar4) {
                if (V7554 == 0) DEBUG_PRINT(0);
                else            debug_print(0);
            }
            sync_to_slave(param_1, 8, 0);
            if (*param_2 == 2) update_persist_task_status_to_wait_blow_head(0);
            else               update_persist_task_status_to_idle(param_1);
            iVar13 = ((unsigned long)&rodata_a2ce2) /*=0xa2ce2*/;
            if (*param_1 == '\x01') {
                thunk_FUN_00074844(0x4000, 0);
                iVar13 = ((unsigned long)&rodata_a2ce2) /*=0xa2ce2*/;
            }
            goto LAB_0002ce1c;
        }
        if ((param_1[1] == '\x01') || (iVar18 = get_device_info(0), *(char *)(iVar18 + 1) == '\b')) {
            if (2 < *piVar4) {
                if (V7554 == 0) DEBUG_PRINT(0);
                else            debug_print(0);
            }
            update_persist_task_status_to_idle(param_1);
            iVar13 = ((unsigned long)&rodata_a2cfc) /*=0xa2cfc*/;
            goto LAB_0002ce1c;
        }
        iVar18 = **(int **)(param_1 + 0xff0);
        if (iVar18 == 0) {
            *(u8 *)(*(int *)(param_1 + 0xff0) + 5) = 0;
            if (2 < *piVar4) {
                if (V7554 == 0) DEBUG_PRINT(0);
                else            debug_print(0);
            }
            local_2c[0] = ((unsigned long)&rodata_a2d5a) /*=0xa2d5a*/;
            update_persist_task_status(param_1, **(u32 **)(param_1 + 0x1054), 1);
            iVar13 = local_2c[0];
            goto LAB_0002ce1c;
        }
        if (*param_2 == 2) break;
        uVar19 = uVar19 + 1;
        if (((uVar19 & 0xf) == 0) && (2 < *piVar4)) {
            if (*piVar2 == 0) DEBUG_PRINT(0);
            else              debug_print(0);
        }
        if (param_1[0xd5] == '\x01') {
            iVar13 = ((unsigned long)&rodata_a2ad4) /*=0xa2ad4*/;
            if (*piVar4 < 3) goto LAB_0002ce1c;
            uVar19 = (u8)param_1[0xd5];
            iVar18 = V7554;
            uVar14 = ((unsigned long)&rodata_a2de3) /*=0xa2de3*/;
            uVar15 = ((unsigned long)&rodata_a39a0) /*=0xa39a0*/;
            goto LAB_0002cbe8;
        }
        thunk_FUN_00074844(0x667, 0);
    }
    if (param_1[0xdd] == '\0') {
        update_temp_task_status(param_1, 6);
    } else {
        update_temp_task_status(param_1, 4);
        check_pending_messages_flag(0);
    }
    if (2 < *piVar4) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    update_persist_task_status(param_1, **(u32 **)(param_1 + 0x1054), 3);
    goto LAB_0002cf58;

CASE_DEFAULT:
    thunk_FUN_00074844(0x8000, 0);
    goto LAB_0002ca3c;

CASE4:
    if (2 < V230C) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    iVar18 = process_for_message_show(param_1, param_1 + 0xd4, param_2, local_2c);
    goto LAB_0002ca34;

CASE5:
    if (2 < V230C) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    iVar18 = process_for_new_message_come_on(param_1, param_1 + 0xd4, param_2, local_2c);
LAB_0002ca34:
    iVar13 = local_2c[0];
    if (iVar18 == 10) goto LAB_0002ce1c;
LAB_0002ca3c:
    iVar13 = local_2c[0];
    if (iVar18 != 0xb) goto LAB_0002ce1c;
    goto LAB_0002cf58;

CASE6:
    if (2 < V230C) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    pcVar20 = (char *)&G_18d9e;
    puVar3 = P7B38;
    uVar19 = 0;
    param_1[0xdc] = '\0';
    while (1) {
        if ((param_1[1] == '\x01') || (iVar18 = get_device_info(0), *(char *)(iVar18 + 1) == '\b')) {
            if (2 < *piVar2) {
                if (V7554 == 0) DEBUG_PRINT(0);
                else            debug_print(0);
            }
            update_persist_task_status_to_idle(param_1);
            iVar13 = ((unsigned long)&rodata_a2ad4) /*=0xa2ad4*/;
            goto LAB_0002ce1c;
        }
        if ((((*param_2 == 1) && (iVar18 = FUN_00023eec(0), iVar18 == 0)) ||
             (((int)(*puVar3 << 0x1e) < 0 && (iVar18 = FUN_00023eec(0), iVar18 == 1)))) ||
            (((int)(*puVar3 << 0x1e) < 0 && (iVar18 = FUN_00023eec(0), iVar18 == 2)))) {
            if ((int)(*puVar3 << 0x1e) < 0) {
                *puVar3 = *puVar3 & 0xfffffffd;
            }
            iVar18 = now_has_persist_task(param_1, param_1[0xd5]);
            if (iVar18 != 1) {
                sync_to_slave(param_1, 8, 0);
                update_persist_task_status_to_idle(param_1);
                iVar13 = ((unsigned long)&rodata_a2ad4) /*=0xa2ad4*/;
                if (*piVar2 < 3) goto LAB_0002ce1c;
                uVar19 = (u8)param_1[0xd5];
                iVar18 = V7554;
                uVar14 = ((unsigned long)&rodata_a291d) /*=0xa291d*/;
                uVar15 = ((unsigned long)&rodata_a39bb) /*=0xa39bb*/;
                goto LAB_0002cbe8;
            }
            if (2 < *piVar2) {
                if (V7554 == 0) DEBUG_PRINT(0);
                else            debug_print(0);
            }
            uVar17 = **(u32 **)(param_1 + 0x1054) & 0xff;
            goto LAB_0002cb9a;
        }
        iVar18 = now_has_persist_task(param_1, param_1[0xd5]);
        if (iVar18 == 1) {
            if (2 < *piVar2) {
                if (V7554 == 0) DEBUG_PRINT(0);
                else            debug_print(0);
            }
            uVar17 = *(u32 *)(param_1 + 0xdf);
            if (uVar17 == 0xb) goto LAB_0002cb9a;
            if      (uVar17 == 7)  { uVar17 = 7;    goto LAB_0002cb9a; }
            else if (uVar17 == 8)  { uVar17 = 8;    goto LAB_0002cb9a; }
            else if (uVar17 == 9)  { uVar17 = 9;    goto LAB_0002cb9a; }
            else if (uVar17 == 10) { uVar17 = 10;   goto LAB_0002cb9a; }
            else if (uVar17 == 0xc){ uVar17 = 0xc;  goto LAB_0002cb9a; }
            else if (uVar17 == 0xe){ uVar17 = 0xe;  goto LAB_0002cb9a; }
            else if (uVar17 == 0xf){ uVar17 = 0xf;  goto LAB_0002cb9a; }
            else if (uVar17 == 0x10){uVar17 = 0x10; goto LAB_0002cb9a; }
            else if (uVar17 == 0x11){uVar17 = 0x11; goto LAB_0002cb9a; }
            else { param_1[0xdc] = param_1[0xdc] + '\x01'; }
        }
        if (param_1[0xd5] == '\x01') {
            iVar13 = ((unsigned long)&rodata_a2ad4) /*=0xa2ad4*/;
            if (*piVar2 < 3) goto LAB_0002ce1c;
            uVar19 = (u8)param_1[0xd5];
            iVar18 = V7554;
            uVar14 = 0xa2b59;
            uVar15 = ((unsigned long)&rodata_a39bb) /*=0xa39bb*/;
            goto LAB_0002cbe8;
        }
        if ((param_1[0x108f] != '\0') && (iVar18 = FUN_00034410(0), iVar18 == 1)) {
            set_new_message_pending_flag(0);
            if (*param_1 == '\x01') {
                sync_message_signal_to_slave(1);
                clear_timeout_message(0);
                check_pending_messages_flag(0);
                push_message_3439c(0);
                update_temp_task_status(param_1, 4, 2);
                uVar14 = ((unsigned long)&rodata_a0a61) /*=0xa0a61*/;
                goto LAB_0002cd8c;
            }
            if (param_1[0xd5] == '\x04') goto LAB_0002ccda;
        }
        if (param_1[0xd5] == '\x04') {
            if (*param_1 == '\x02') {
                thunk_FUN_00074844(0x1334, 0);
            }
            iVar18 = V7554;
            uVar14 = 0xa2bc0;
            goto LAB_0002cd00;
        }
        if (param_1[0xfe6] == '\x01') {
            uVar14 = 0x667;
            goto LAB_0002cd18;
        }
        uVar19 = uVar19 + 1;
        if (((uVar19 & 0xf) == 0) && (2 < *piVar2)) {
            if (V7554 == 0) DEBUG_PRINT(0);
            else            debug_print(0);
        }
        if ((*pcVar20 != '\0') && (iVar18 = msg_content_used_count(0), iVar18 != 0)) break;
        get_device_info(0);
        thunk_FUN_00074844(0x667, 0);
    }
    set_new_message_pending_flag(0);
    FUN_0003443c(6);
    update_temp_task_status(param_1, 4, 2);
    uVar14 = ((unsigned long)&rodata_a2c70) /*=0xa2c70*/;
LAB_0002cd8c:
    trigger_screen_state_change(uVar14, param_1, 1);
    goto LAB_0002cf58;

CASE7:
    if (2 < V230C) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    uVar15 = ((unsigned long)&rodata_a3325) /*=0xa3325*/;
    uVar14 = ((unsigned long)&rodata_a38f9) /*=0xa38f9*/;
    piVar2 = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uVar19 = 0;
    goto LAB_0002d6ce;

CASE8:
    if (2 < V230C) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    param_1[0xb0d] = '\0';
    iVar18 = get_device_info(0);
    uVar11 = (u8)msg_content_recalc_unread(0);
    *(u8 *)(iVar18 + 0xdd) = uVar11;
    while ((*param_2 != 1 || (param_1[0xfea] != '\n'))) {
        thunk_FUN_00074844(0x667, 0);
    }
    if (2 < *piVar7) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    sync_to_slave(param_1, 8, 0);
    update_persist_task_status_to_idle(param_1);
    local_2c[0] = ((unsigned long)&rodata_a3311) /*=0xa3311*/;
    goto LAB_0002d118;

CASE9:
    if (2 < V230C) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    uVar15 = ((unsigned long)&rodata_a2f08) /*=0xa2f08*/;
    uVar14 = ((unsigned long)&rodata_a3982) /*=0xa3982*/;
    piVar2 = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uVar19 = 0;
    iVar18 = *(int *)(param_1 + 0xffc);
    goto LAB_0002d03e;

CASE10:
    if (2 < V230C) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    uVar15 = ((unsigned long)&rodata_a318d) /*=0xa318d*/;
    uVar14 = ((unsigned long)&rodata_a394b) /*=0xa394b*/;
    piVar2 = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uVar19 = 0;
    pcVar20 = *(char **)(param_1 + 0x1000);
    goto LAB_0002d37c;

CASE11:
    if (2 < V230C) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    uVar15 = ((unsigned long)&rodata_a3244) /*=0xa3244*/;
    uVar14 = 0xa3590;
    piVar2 = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uVar19 = 0;
    goto LAB_0002d4ce;

CASE12:
    if (2 < V230C) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    uVar15 = ((unsigned long)&rodata_a3071) /*=0xa3071*/;
    uVar14 = ((unsigned long)&rodata_a3967) /*=0xa3967*/;
    piVar2 = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uVar19 = 0;
    goto LAB_0002d1b4;

CASE14:
    if (2 < V230C) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    uVar15 = ((unsigned long)&rodata_a33de) /*=0xa33de*/;
    uVar14 = ((unsigned long)&rodata_a38dd) /*=0xa38dd*/;
    piVar2 = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uVar19 = 0;
    goto LAB_0002d7ee;

CASE15:
    if (2 < V230C) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    uVar15 = ((unsigned long)&rodata_a34a2) /*=0xa34a2*/;
    uVar14 = ((unsigned long)&rodata_a38be) /*=0xa38be*/;
    piVar2 = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uVar19 = 0;
    goto LAB_0002d998;

CASE16:
    if (2 < V230C) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    piVar2 = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uVar19 = 0;
    goto LAB_0002dac0;

CASE17:
    if (2 < V230C) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    uVar15 = ((unsigned long)&rodata_a3619) /*=0xa3619*/;
    uVar14 = ((unsigned long)&rodata_a3886) /*=0xa3886*/;
    piVar2 = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uVar19 = 0;
    goto LAB_0002dd2a;

LAB_0002cf58:
    iVar18 = 0xb;
    goto LAB_0002c9b6;

LAB_0002dd2a:
    if ((param_1[1] == '\x01') || (iVar18 = get_device_info(0), *(char *)(iVar18 + 1) == '\b'))
        goto LAB_0002dd30;
    if (**(char **)(param_1 + 0x101c) == '\0') {
        local_2c[0] = ((unsigned long)&rodata_a35df) /*=0xa35df*/;
        if (*param_2 != 2) {
            if (*piVar9 < 3) goto LAB_0002d2da;
            uVar19 = (u8)param_1[0xd5];
            iVar18 = V7554;
            uVar14 = ((unsigned long)&rodata_a3886) /*=0xa3886*/;
            goto LAB_0002d5b8;
        }
        sync_to_slave(param_1, 8, 0);
        if (*piVar9 < 3) goto LAB_0002d9fc;
        bVar1 = param_1[0xd5];
        iVar18 = V7554;
        uVar14 = ((unsigned long)&rodata_a3886) /*=0xa3886*/;
        goto LAB_0002d9f0;
    }
    if (param_1[0xd5] == '\x01') {
        iVar13 = ((unsigned long)&rodata_a35f7) /*=0xa35f7*/;
        if (2 < *piVar9) {
            if (V7554 == 0) { DEBUG_PRINT(0); iVar13 = ((unsigned long)&rodata_a35f7) /*=0xa35f7*/; }
            else            { debug_print(0); iVar13 = ((unsigned long)&rodata_a35f7) /*=0xa35f7*/; }
        }
        goto LAB_0002ce1c;
    }
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar9)) {
        if (*piVar2 == 0) DEBUG_PRINT(0);
        else              debug_print(0);
    }
    thunk_FUN_00074844(0x667, 0);
    goto LAB_0002dd2a;
LAB_0002dd30:
    if (2 < *piVar9) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    update_persist_task_status_to_idle(param_1);
    iVar13 = ((unsigned long)&rodata_a35cd) /*=0xa35cd*/;
    goto LAB_0002ce1c;

LAB_0002dac0:
    if (param_1[0xfea] == '\f') goto code_r0x0002dac8;
    if ((param_1[1] == '\x01') || (iVar18 = get_device_info(0), *(char *)(iVar18 + 1) == '\b')) {
        if (2 < *piVar8) {
            bVar1 = param_1[0xd5];
            iVar18 = V7554;
            uVar14 = ((unsigned long)&rodata_a2768) /*=0xa2768*/;
LAB_0002dc06:
            if (iVar18 == 0) DEBUG_PRINT(uVar14, bVar1);
            else             debug_print(0);
        }
        goto LAB_0002db7c;
    }
    iVar18 = check_charging_and_touch_flags(0);
    if (((iVar18 == 0) && (iVar18 = get_device_info(0), 1 < **(u8 **)(iVar18 + 0x100c))) &&
        (iVar18 = get_device_info(0), **(u8 **)(iVar18 + 0x100c) < 10)) {
        iVar18 = get_device_info(0);
        **(u8 **)(iVar18 + 0x100c) = 10;
    }
    if (((*(char *)(*(int *)(param_1 + 0x100c) + 7) == '\0') ||
         (iVar18 = get_device_info(0), **(char **)(iVar18 + 0x100c) == '\0')) ||
        (((**(char **)(param_1 + 0x100c) == '\b' || (**(char **)(param_1 + 0x100c) == '\v')) &&
          (param_1[0xdb] == '\0')))) {
        if (*param_1 == '\x01') {
            send_event_status(0);
        }
        if (*param_2 == 2) {
            sync_to_slave(param_1, 8, 0);
            if (2 < *piVar8) {
                bVar1 = param_1[0xd5];
                iVar18 = V7554;
                uVar14 = ((unsigned long)&rodata_a3215) /*=0xa3215*/;
                goto LAB_0002dc06;
            }
        } else {
            if (2 < *piVar8) {
                if (V7554 == 0) DEBUG_PRINT(0);
                else            debug_print(0);
            }
            sync_to_slave(param_1, 8, 0);
        }
        goto LAB_0002db7c;
    }
    if (param_1[0xd5] == '\x01') {
        if (2 < *piVar8) {
            if (V7554 == 0) DEBUG_PRINT(0);
            else            debug_print(0);
        }
        reset_esb_sync_state(1);
        iVar13 = ((unsigned long)&rodata_a2a32) /*=0xa2a32*/;
        goto LAB_0002ce1c;
    }
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar8)) {
        if (*piVar2 == 0) DEBUG_PRINT(0);
        else              debug_print(0);
    }
    if ((*param_1 == '\x01') &&
        (((**(u8 **)(param_1 + 0x100c) - 7 < 2 || (**(u8 **)(param_1 + 0x100c) == 0xb)) &&
          ((uVar19 * 0xcccccccdu >> 2 | uVar19 * 0xcccccccdu << 30) <= 0xcccccccu)))) {
        param_1[0xdb] = param_1[0xdb] + -1;
    }
    thunk_FUN_00074844(0x667, 0);
    goto LAB_0002dac0;

LAB_0002d998:
    if ((param_1[1] == '\x01') || (iVar18 = get_device_info(0), *(char *)(iVar18 + 1) == '\b'))
        goto LAB_0002d99e;
    if (**(char **)(param_1 + 0x1018) == '\0') {
        local_2c[0] = ((unsigned long)&rodata_a3468) /*=0xa3468*/;
        if (*param_2 == 2) {
            sync_to_slave(param_1, 8, 0);
            if (2 < *piVar8) {
                bVar1 = param_1[0xd5];
                iVar18 = V7554;
                uVar14 = ((unsigned long)&rodata_a38be) /*=0xa38be*/;
LAB_0002d9f0:
                if (iVar18 == 0) DEBUG_PRINT(uVar14, bVar1);
                else             debug_print(0);
            }
            goto LAB_0002d9fc;
        }
        if (*piVar8 < 3) goto LAB_0002d2da;
        uVar19 = (u8)param_1[0xd5];
        iVar18 = V7554;
        uVar14 = ((unsigned long)&rodata_a38be) /*=0xa38be*/;
        goto LAB_0002d5b8;
    }
    if (param_1[0xd5] == '\x01') {
        iVar13 = ((unsigned long)&rodata_a3480) /*=0xa3480*/;
        if (2 < *piVar8) {
            if (V7554 == 0) { DEBUG_PRINT(0); iVar13 = ((unsigned long)&rodata_a3480) /*=0xa3480*/; }
            else            { debug_print(0); iVar13 = ((unsigned long)&rodata_a3480) /*=0xa3480*/; }
        }
        goto LAB_0002ce1c;
    }
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar8)) {
        if (*piVar2 == 0) DEBUG_PRINT(0);
        else              debug_print(0);
    }
    thunk_FUN_00074844(0x667, 0);
    goto LAB_0002d998;
LAB_0002d99e:
    if (2 < *piVar8) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    update_persist_task_status_to_idle(param_1);
    iVar13 = ((unsigned long)&rodata_a3456) /*=0xa3456*/;
    goto LAB_0002ce1c;

LAB_0002d7ee:
    if ((param_1[1] == '\x01') || (iVar18 = get_device_info(0), *(char *)(iVar18 + 1) == '\b'))
        goto LAB_0002d7f4;
    if (**(char **)(param_1 + 0x1014) == '\0') {
        local_2c[0] = ((unsigned long)&rodata_a33aa) /*=0xa33aa*/;
        if (*param_2 == 2) {
            sync_to_slave(param_1, 8, 0);
            if (2 < *piVar7) {
                if (V7554 == 0) DEBUG_PRINT(0);
                else            debug_print(0);
            }
        } else {
            if (2 < *piVar7) {
                if (V7554 == 0) DEBUG_PRINT(0);
                else            debug_print(0);
            }
            sync_to_slave(param_1, 8, 0);
        }
        update_persist_task_status_to_idle(param_1);
        iVar13 = local_2c[0];
        if (*param_1 != '\x01') goto LAB_0002ce1c;
        uVar14 = 0xccd;
        goto LAB_0002cd18;
    }
    if (param_1[0xd5] == '\x01') {
        iVar13 = ((unsigned long)&rodata_a33bf) /*=0xa33bf*/;
        if (2 < *piVar7) {
            if (V7554 == 0) { DEBUG_PRINT(0); iVar13 = ((unsigned long)&rodata_a33bf) /*=0xa33bf*/; }
            else            { debug_print(0); iVar13 = ((unsigned long)&rodata_a33bf) /*=0xa33bf*/; }
        }
        goto LAB_0002ce1c;
    }
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar7)) {
        if (*piVar2 == 0) DEBUG_PRINT(0);
        else              debug_print(0);
    }
    thunk_FUN_00074844(0x667, 0);
    goto LAB_0002d7ee;
LAB_0002d7f4:
    if (2 < *piVar7) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    update_persist_task_status_to_idle(param_1);
    iVar13 = ((unsigned long)&rodata_a339b) /*=0xa339b*/;
    goto LAB_0002ce1c;

LAB_0002d1b4:
    if ((param_1[1] == '\x01') || (iVar18 = get_device_info(0), *(char *)(iVar18 + 1) == '\b'))
        goto LAB_0002d1ba;
    if (**(char **)(param_1 + 0x1020) == '\0') {
        local_2c[0] = ((unsigned long)&rodata_a2f9c) /*=0xa2f9c*/;
        if (*param_2 != 2) {
            if (2 < *piVar5) {
                if (V7554 == 0) DEBUG_PRINT(0);
                else            debug_print(0);
            }
            goto LAB_0002d2da;
        }
        if (2 < *piVar5) {
            if (V7554 == 0) DEBUG_PRINT(0);
            else            debug_print(0);
        }
        sync_to_slave(param_1, 8, 0);
        if (*param_2 == 2) update_persist_task_status_to_wait_blow_head(0);
        else               update_persist_task_status_to_idle(param_1);
        trigger_screen_state_change(((unsigned long)&rodata_a2733) /*=0xa2733*/, param_1, 1);
        goto LAB_0002d118;
    }
    if (param_1[0xd5] == '\x01') {
        iVar13 = ((unsigned long)&rodata_a2ad4) /*=0xa2ad4*/;
        if (*piVar5 < 3) goto LAB_0002ce1c;
        uVar19 = (u8)param_1[0xd5];
        iVar18 = V7554;
        uVar14 = ((unsigned long)&rodata_a2de3) /*=0xa2de3*/;
        uVar15 = ((unsigned long)&rodata_a3967) /*=0xa3967*/;
        goto LAB_0002cbe8;
    }
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar5)) {
        if (*piVar2 == 0) DEBUG_PRINT(0);
        else              debug_print(0);
    }
    thunk_FUN_00074844(0x667, 0);
    goto LAB_0002d1b4;
LAB_0002d1ba:
    if (2 < *piVar5) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    update_persist_task_status_to_idle(param_1);
    iVar13 = ((unsigned long)&rodata_a2f7e) /*=0xa2f7e*/;
    goto LAB_0002ce1c;

LAB_0002d4ce:
    if ((param_1[1] == '\x01') || (iVar18 = get_device_info(0), *(char *)(iVar18 + 1) == '\b'))
        goto LAB_0002d4d4;
    if ((*(char *)(*(int *)(param_1 + 0x1004) + 6) == '\0') &&
        (*(char *)(*(int *)(param_1 + 0x1008) + 6) == '\0')) {
        local_2c[0] = ((unsigned long)&rodata_a3201) /*=0xa3201*/;
        if (*param_2 != 2) {
            if (2 < *piVar6) {
                uVar19 = (u8)param_1[0xd5];
                iVar18 = V7554;
                uVar14 = ((unsigned long)&rodata_a3930) /*=0xa3930*/;
LAB_0002d5b8:
                if (iVar18 == 0) DEBUG_PRINT(uVar14, uVar19);
                else             debug_print(0);
            }
            goto LAB_0002d2da;
        }
        sync_to_slave(param_1, 8, 0);
        if (2 < *piVar6) {
            if (V7554 == 0) DEBUG_PRINT(0);
            else            debug_print(0);
        }
        goto LAB_0002d0b4;
    }
    if (param_1[0xd5] == '\x01') {
        iVar13 = ((unsigned long)&rodata_a2ad4) /*=0xa2ad4*/;
        if (*piVar6 < 3) goto LAB_0002ce1c;
        uVar19 = (u8)param_1[0xd5];
        iVar18 = V7554;
        uVar14 = ((unsigned long)&rodata_a2de3) /*=0xa2de3*/;
        uVar15 = ((unsigned long)&rodata_a3930) /*=0xa3930*/;
        goto LAB_0002cbe8;
    }
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar6)) {
        if (*piVar2 == 0) DEBUG_PRINT(0);
        else              debug_print(0);
    }
    thunk_FUN_00074844(0x667, 0);
    goto LAB_0002d4ce;
LAB_0002d4d4:
    if (2 < *piVar6) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    update_persist_task_status_to_idle(param_1);
    iVar13 = ((unsigned long)&rodata_a3201) /*=0xa3201*/;
    goto LAB_0002ce1c;

LAB_0002d37c:
    if ((param_1[1] != '\x01') && (iVar18 = get_device_info(0), *(char *)(iVar18 + 1) != '\b')) {
        if (*pcVar20 != '\0') {
            if (param_1[0xd5] != '\x01') goto LAB_0002d46a;
            iVar13 = ((unsigned long)&rodata_a2ad4) /*=0xa2ad4*/;
            if (*piVar6 < 3) goto LAB_0002ce1c;
            uVar19 = (u8)param_1[0xd5];
            iVar18 = V7554;
            uVar14 = ((unsigned long)&rodata_a2de3) /*=0xa2de3*/;
            uVar15 = ((unsigned long)&rodata_a394b) /*=0xa394b*/;
            goto LAB_0002cbe8;
        }
        local_2c[0] = ((unsigned long)&rodata_a3104) /*=0xa3104*/;
        if (*param_2 != 2) {
            if (2 < *piVar6) {
                if (V7554 == 0) DEBUG_PRINT(0);
                else            debug_print(0);
            }
LAB_0002d2da:
            sync_to_slave(param_1, 8, 0);
LAB_0002d9fc:
            update_persist_task_status_to_idle(param_1);
            goto LAB_0002d118;
        }
        if (2 < *piVar6) {
            if (V7554 == 0) DEBUG_PRINT(0);
            else            debug_print(0);
        }
        sync_to_slave(param_1, 8, 0);
        update_persist_task_status_to_idle(param_1);
        trigger_screen_state_change(((unsigned long)&rodata_a2733) /*=0xa2733*/, param_1, 1);
        goto LAB_0002d3ec;
    }
    goto LAB_0002d382;
LAB_0002d46a:
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar6)) {
        if (*piVar2 == 0) DEBUG_PRINT(0);
        else              debug_print(0);
    }
    thunk_FUN_00074844(0x667, 0);
    goto LAB_0002d37c;
LAB_0002d382:
    if (2 < *piVar6) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    update_persist_task_status_to_idle(param_1);
    iVar13 = ((unsigned long)&rodata_a30e5) /*=0xa30e5*/;
    goto LAB_0002ce1c;

LAB_0002d03e:
    if ((param_1[1] == '\x01') || (iVar13 = get_device_info(0), *(char *)(iVar13 + 1) == '\b'))
        goto LAB_0002d044;
    if (*(char *)(iVar18 + 1) == '\0') {
        local_2c[0] = ((unsigned long)&rodata_a2e7c) /*=0xa2e7c*/;
        mark_master_or_low_battery_flag(0);
        if (*param_2 == 2) {
            trigger_screen_state_change(((unsigned long)&rodata_a2733) /*=0xa2733*/, param_1, 1);
            clear_notification_display_buffer(0);
            if (2 < *piVar5) {
                if (V7554 == 0) DEBUG_PRINT(0);
                else            debug_print(0);
            }
            sync_to_slave(param_1, 8, 0);
LAB_0002d0b4:
            update_persist_task_status_to_idle(param_1);
LAB_0002d3ec:
            if (*param_1 == '\x01') {
                thunk_FUN_00074844(0x4000, 0);
            }
            uVar14 = 0x2667;
        } else {
            if (2 < *piVar5) {
                if (V7554 == 0) DEBUG_PRINT(0);
                else            debug_print(0);
            }
            sync_to_slave(param_1, 8, 0);
            update_persist_task_status_to_idle(param_1);
            clear_notification_display_buffer(0);
LAB_0002d118:
            iVar13 = local_2c[0];
            if (*param_1 != '\x01') goto LAB_0002ce1c;
            uVar14 = 0x4000;
        }
LAB_0002cd18:
        thunk_FUN_00074844(uVar14, 0);
        iVar13 = local_2c[0];
        goto LAB_0002ce1c;
    }
    if (param_1[0xd5] == '\x01') {
        iVar13 = ((unsigned long)&rodata_a2ad4) /*=0xa2ad4*/;
        if (2 < *piVar5) {
            uVar19 = (u8)param_1[0xd5];
            iVar18 = V7554;
            uVar14 = ((unsigned long)&rodata_a2de3) /*=0xa2de3*/;
            uVar15 = ((unsigned long)&rodata_a3982) /*=0xa3982*/;
LAB_0002cbe8:
            if (iVar18 == 0) { DEBUG_PRINT(uVar14, uVar15, uVar19); iVar13 = ((unsigned long)&rodata_a2ad4) /*=0xa2ad4*/; }
            else             { debug_print(0);                      iVar13 = ((unsigned long)&rodata_a2ad4) /*=0xa2ad4*/; }
        }
        goto LAB_0002ce1c;
    }
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar5)) {
        if (*piVar2 == 0) DEBUG_PRINT(0);
        else              debug_print(0);
    }
    thunk_FUN_00074844(0x667, 0);
    goto LAB_0002d03e;
LAB_0002d044:
    if (2 < *piVar5) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    update_persist_task_status_to_idle(param_1);
    iVar13 = ((unsigned long)&rodata_a2e5b) /*=0xa2e5b*/;
    goto LAB_0002ce1c;

LAB_0002d6ce:
    if ((param_1[1] == '\x01') || (iVar18 = get_device_info(0), *(char *)(iVar18 + 1) == '\b'))
        goto LAB_0002d6d4;
    if (**(char **)(param_1 + 0x1010) == '\0') {
        local_2c[0] = ((unsigned long)&rodata_a32ef) /*=0xa32ef*/;
        if (*param_2 == 2) {
            if (2 < *piVar7) {
                bVar1 = param_1[0xd5];
                iVar18 = V7554;
                uVar14 = ((unsigned long)&rodata_a3215) /*=0xa3215*/;
LAB_0002d71c:
                if (iVar18 == 0) DEBUG_PRINT(uVar14, bVar1);
                else             debug_print(0);
            }
        } else if (2 < *piVar7) {
            bVar1 = param_1[0xd5];
            iVar18 = V7554;
            uVar14 = ((unsigned long)&rodata_a294a) /*=0xa294a*/;
            goto LAB_0002d71c;
        }
        update_persist_task_status_to_idle(param_1);
        iVar13 = local_2c[0];
        goto LAB_0002ce1c;
    }
    if (param_1[0xd5] == '\x01') {
        iVar13 = ((unsigned long)&rodata_a3305) /*=0xa3305*/;
        if (2 < *piVar7) {
            if (V7554 == 0) { DEBUG_PRINT(0); iVar13 = ((unsigned long)&rodata_a3305) /*=0xa3305*/; }
            else            { debug_print(0); iVar13 = ((unsigned long)&rodata_a3305) /*=0xa3305*/; }
        }
        goto LAB_0002ce1c;
    }
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar7)) {
        if (*piVar2 == 0) DEBUG_PRINT(0);
        else              debug_print(0);
    }
    thunk_FUN_00074844(0x667, 0);
    goto LAB_0002d6ce;
LAB_0002d6d4:
    if (2 < *piVar7) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    update_persist_task_status_to_idle(param_1);
    iVar13 = ((unsigned long)&rodata_a32df) /*=0xa32df*/;
    goto LAB_0002ce1c;

LAB_0002ccda:
    iVar18 = V7554;
    uVar14 = ((unsigned long)&rodata_a2ba7) /*=0xa2ba7*/;
LAB_0002cd00:
    if (iVar18 == 0) DEBUG_PRINT(uVar14);
    else             debug_print(0);
    goto LAB_0002cf58;

code_r0x0002dac8:
    if (2 < *piVar8) {
        if (V7554 == 0) DEBUG_PRINT(0);
        else            debug_print(0);
    }
    sync_to_slave(param_1, 8, 0);
    if (*param_2 == 2) {
        update_persist_task_status_to_wait_blow_head(0);
    } else {
LAB_0002db7c:
        update_persist_task_status_to_idle(param_1);
    }
    reset_esb_sync_state(1);
    iVar13 = ((unsigned long)&rodata_a2a21) /*=0xa2a21*/;
LAB_0002ce1c:
    local_2c[0] = iVar13;
    iVar18 = local_2c[0];
    if (local_2c[0] != 0) {
        if (2 < V230C) {
            if (V7554 == 0) DEBUG_PRINT(0);
            else            debug_print(0);
        }
        trigger_screen_state_change(iVar18, param_1, 0);
        iVar18 = FUN_00034410(0);
        if (iVar18 == 1) {
            iVar18 = is_msg_expiration(0);
            if (iVar18 == 1) {
                cVar12 = '\x05';
            } else {
                iVar18 = get_device_info(0);
                cVar12 = *(char *)(iVar18 + 0xdd);
                if (cVar12 != '\0') cVar12 = '\x06';
            }
            FUN_0003443c(cVar12);
        }
    }
    return 0;
}
