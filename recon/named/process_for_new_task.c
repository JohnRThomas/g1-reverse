/* readable reconstruction; identity: FUN_0002c99c @ 0x0002c99c
 * public-name: process_for_new_task
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_ui_mode_flag2                        <= FUN_00023eec @ 0x00023eec
 *   check_charging_and_touch_flags           <= FUN_00026c28 @ 0x00026c28
 *   trigger_screen_state_change              <= FUN_0002bc2c @ 0x0002bc2c
 *   now_has_persist_task                     <= FUN_0002be64 @ 0x0002be64
 *   update_temp_task_status                  <= FUN_0002bffc @ 0x0002bffc
 *   update_persist_task_status_to_idle       <= FUN_0002c0e8 @ 0x0002c0e8
 *   update_persist_task_status_to_wait_blow_head <= FUN_0002c180 @ 0x0002c180
 *   check_pending_messages_flag              <= FUN_0002c1fc @ 0x0002c1fc
 *   clear_pending_message_flag               <= FUN_0002c214 @ 0x0002c214
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
 *   get_message_pending_state                <= FUN_00034410 @ 0x00034410
 *   set_message_pending_state                <= FUN_0003443c @ 0x0003443c
 *   is_msg_expiration                        <= FUN_0003444c @ 0x0003444c
 *   check_message_expired_or_timeout         <= FUN_00034808 @ 0x00034808
 *   set_new_message_pending_flag             <= FUN_00036030 @ 0x00036030
 *   clear_notification_display_buffer        <= FUN_0003cf34 @ 0x0003cf34
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   device_addr_is_default                   <= FUN_0007c132 @ 0x0007c132
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
 *   rodata_a2a4d                             @ 0x000a2a4d
 *   rodata_a2a7e                             @ 0x000a2a7e
 *   rodata_a2aad                             @ 0x000a2aad
 *   rodata_a2ad4                             @ 0x000a2ad4
 *   rodata_a2af2                             @ 0x000a2af2
 *   rodata_a2b22                             @ 0x000a2b22
 *   rodata_a2ba7                             @ 0x000a2ba7
 *   rodata_a2c0b                             @ 0x000a2c0b
 *   rodata_a2c70                             @ 0x000a2c70
 *   rodata_a2c85                             @ 0x000a2c85
 *   rodata_a2cb2                             @ 0x000a2cb2
 *   rodata_a2ce2                             @ 0x000a2ce2
 *   rodata_a2cfc                             @ 0x000a2cfc
 *   rodata_a2d1a                             @ 0x000a2d1a
 *   rodata_a2d5a                             @ 0x000a2d5a
 *   rodata_a2d6f                             @ 0x000a2d6f
 *   rodata_a2d97                             @ 0x000a2d97
 *   rodata_a2de3                             @ 0x000a2de3
 *   rodata_a2e31                             @ 0x000a2e31
 *   rodata_a2e5b                             @ 0x000a2e5b
 *   rodata_a2e7c                             @ 0x000a2e7c
 *   rodata_a2e93                             @ 0x000a2e93
 *   rodata_a2ed8                             @ 0x000a2ed8
 *   rodata_a2f08                             @ 0x000a2f08
 *   rodata_a2f57                             @ 0x000a2f57
 *   rodata_a2f7e                             @ 0x000a2f7e
 *   rodata_a2f9c                             @ 0x000a2f9c
 *   rodata_a2fb0                             @ 0x000a2fb0
 *   rodata_a301e                             @ 0x000a301e
 *   rodata_a3071                             @ 0x000a3071
 *   rodata_a30bd                             @ 0x000a30bd
 *   rodata_a30e5                             @ 0x000a30e5
 *   rodata_a3104                             @ 0x000a3104
 *   rodata_a3119                             @ 0x000a3119
 *   rodata_a315d                             @ 0x000a315d
 *   rodata_a318d                             @ 0x000a318d
 *   rodata_a31da                             @ 0x000a31da
 *   rodata_a3201                             @ 0x000a3201
 *   rodata_a3215                             @ 0x000a3215
 *   rodata_a3244                             @ 0x000a3244
 *   rodata_a3290                             @ 0x000a3290
 *   rodata_a32b6                             @ 0x000a32b6
 *   rodata_a32df                             @ 0x000a32df
 *   rodata_a32ef                             @ 0x000a32ef
 *   rodata_a3305                             @ 0x000a3305
 *   rodata_a3311                             @ 0x000a3311
 *   rodata_a3325                             @ 0x000a3325
 *   rodata_a3373                             @ 0x000a3373
 *   rodata_a339b                             @ 0x000a339b
 *   rodata_a33aa                             @ 0x000a33aa
 *   rodata_a33bf                             @ 0x000a33bf
 *   rodata_a33de                             @ 0x000a33de
 *   rodata_a342b                             @ 0x000a342b
 *   rodata_a3456                             @ 0x000a3456
 *   rodata_a3468                             @ 0x000a3468
 *   rodata_a3480                             @ 0x000a3480
 *   rodata_a34a2                             @ 0x000a34a2
 *   rodata_a34f2                             @ 0x000a34f2
 *   rodata_a3517                             @ 0x000a3517
 *   rodata_a3558                             @ 0x000a3558
 *   rodata_a35a2                             @ 0x000a35a2
 *   rodata_a35cd                             @ 0x000a35cd
 *   rodata_a35df                             @ 0x000a35df
 *   rodata_a35f7                             @ 0x000a35f7
 *   rodata_a3619                             @ 0x000a3619
 *   rodata_a3669                             @ 0x000a3669
 *   rodata_a3696                             @ 0x000a3696
 *   rodata_a36ff                             @ 0x000a36ff
 *   rodata_a3758                             @ 0x000a3758
 *   rodata_a3770                             @ 0x000a3770
 *   rodata_a37f6                             @ 0x000a37f6
 *   rodata_a3811                             @ 0x000a3811
 *   rodata_a383d                             @ 0x000a383d
 *   rodata_a384c                             @ 0x000a384c
 *   rodata_a3875                             @ 0x000a3875
 *   rodata_a3886                             @ 0x000a3886
 *   rodata_a38a5                             @ 0x000a38a5
 *   rodata_a38be                             @ 0x000a38be
 *   rodata_a38dd                             @ 0x000a38dd
 *   rodata_a38f9                             @ 0x000a38f9
 *   rodata_a3916                             @ 0x000a3916
 *   rodata_a3930                             @ 0x000a3930
 *   rodata_a394b                             @ 0x000a394b
 *   rodata_a3967                             @ 0x000a3967
 *   rodata_a3982                             @ 0x000a3982
 *   rodata_a39a0                             @ 0x000a39a0
 *   rodata_a39bb                             @ 0x000a39bb
 *   rodata_a3a0f                             @ 0x000a3a0f
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_20007b38                               @ 0x20007b38
 *   g_pending_message_flag                   @ 0x20018d9e
 *   g_esb_notify_slave_role_guard            @ 0x20018d9f
 */
/* Reconstructed process_for_new_task @ 0x2c99c.
 * Raw identity/back-map: FUN_0002c99c @ 0x0002c99c. */
typedef unsigned char      u8;
typedef unsigned int       u32;
typedef unsigned long long u64;

/* Every raw identity below is retained as an address back-map; semantic names
 * are used in the function body where the subsystem role is known. */
extern int log_message(u32, ...);                         /* FUN_0007dda4 */
extern int get_device_info(void);                         /* FUN_000167a8 */
extern int debug_print(u32, ...);                         /* FUN_00019c70 */
extern int get_task_signal_mode(void);                    /* FUN_00023eec */
extern int is_task_transport_blocked(void);               /* FUN_00026c28 */
extern int trigger_screen_state_change(u32, char *, int); /* FUN_0002bc2c */
extern long long now_has_persist_task(char *, int);       /* FUN_0002be64 */
extern int update_temp_task_status(char *, int, ...);     /* FUN_0002bffc */
extern int update_persist_task_status_to_idle(char *);    /* FUN_0002c0e8 */
extern int update_persist_task_status_to_wait_blow_head(void); /* FUN_0002c180 */
extern int reset_task_transition_state(void);             /* FUN_0002c1fc */
extern int publish_task_transition(void);                 /* FUN_0002c214 */
extern int sync_message_signal_to_slave(int, ...);        /* FUN_0002c224 */
extern int prepare_new_task(void);                        /* FUN_0002c2b0 */
extern int process_task_state_five(char *, char *, u8 *, int *); /* FUN_0002c498 */
extern int process_task_state_four(char *, char *, u8 *, int *); /* FUN_0002c714 */
extern int task_transition_pending(void);                 /* FUN_0002eb40 */
extern int finish_task_media(void);                       /* FUN_0002efc0 */
extern int is_battery_critical(void);                     /* FUN_00032ee4 */
extern int should_finish_task_wait(void);                 /* FUN_00033cdc */
extern int read_task_mode(void);                          /* FUN_00033cf8 */
extern int clear_timeout_message(int);                    /* FUN_00033d58 */
extern int finalize_task_transition(void);                /* FUN_0003439c */
extern int is_task_transition_ready(void);                /* FUN_00034410 */
extern int set_task_display_mode(int);                    /* FUN_0003443c */
extern int is_msg_expiration(void);                       /* FUN_0003444c */
extern int can_begin_task_transition(void);               /* FUN_00034808 */
extern int clear_active_task(void);                       /* FUN_00036030 */
extern int finish_task_audio(void);                       /* FUN_0003cf34 */
extern int submit_task_work(int work_item_address);       /* FUN_00072880 */
extern int peer_address_is_uninitialized(u32, u32);       /* FUN_0007c132 */
extern int set_task_wake_state(int);                      /* FUN_0007ce60 */
extern int memset_bytes(void *, int, u32);                /* FUN_00086c78 */
extern int send_event(int);
extern int sync_to_slave(char *, int, int);               /* FUN_00026f74 */
extern int FUN_0007ce5c(u32, u32);                        /* exact wait entry */
extern int update_persist_task_status(char *, u32, int);  /* FUN_0002bef4 */

#define log_message log_message
#define get_device_info get_device_info
#define debug_print debug_print
#define get_ui_mode_flag2 get_task_signal_mode
#define check_charging_and_touch_flags is_task_transport_blocked
#define trigger_screen_state_change trigger_screen_state_change
#define now_has_persist_task now_has_persist_task
#define update_temp_task_status update_temp_task_status
#define update_persist_task_status_to_idle update_persist_task_status_to_idle
#define update_persist_task_status_to_wait_blow_head update_persist_task_status_to_wait_blow_head
#define check_pending_messages_flag reset_task_transition_state
#define clear_pending_message_flag publish_task_transition
#define sync_message_signal_to_slave sync_message_signal_to_slave
#define wait_touch_key_release_or_timeout prepare_new_task
#define process_for_new_message_come_on process_task_state_five
#define process_for_message_show process_task_state_four
#define check_ancs_inbox_flag_change task_transition_pending
#define mark_master_or_low_battery_flag finish_task_media
#define is_battery_critical is_battery_critical
#define msg_content_used_count should_finish_task_wait
#define msg_content_recalc_unread read_task_mode
#define clear_timeout_message clear_timeout_message
#define push_message_3439c finalize_task_transition
#define get_message_pending_state is_task_transition_ready
#define set_message_pending_state set_task_display_mode
#define is_msg_expiration is_msg_expiration
#define check_message_expired_or_timeout can_begin_task_transition
#define set_new_message_pending_flag clear_active_task
#define clear_notification_display_buffer finish_task_audio
#define k_sem_give submit_task_work
#define device_addr_is_default peer_address_is_uninitialized
#define reset_esb_sync_state set_task_wake_state
#define memset_bytes memset_bytes
#define wait_for_event FUN_0007ce5c
#define task_wait_ticks FUN_0007ce5c /* FUN_0007ce5c @ 0x0007ce5c */

/* dereferenced RAM globals (exact literal addresses from the literal pool) */
#define g_esb_notify_slave_role_guard (*(volatile u8 *)0x20018d9f)
#define g_pending_message_flag        (*(volatile char *)0x20018d9e)
#define g_log_level                   (*(volatile int *)0x2000230c)
#define g_log_use_alt_sink            (*(volatile int *)0x20007554)
/* No durable semantic name exists yet for this atomic word. */
#define g_20007b38                    ((volatile u32 *)0x20007b38)

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
    memset_bytes(param_1 + 0xef, 0, 0x5dc);
    clear_timeout_message(0);
    if (*param_1 == '\x01') {
        prepare_new_task();
    }
    if (param_1[0xd5] != '\x04') {
        g_esb_notify_slave_role_guard = 0;
    }
    piVar10 = (volatile int *)0x2000230c;
    piVar9  = (volatile int *)0x2000230c;
    piVar8  = (volatile int *)0x2000230c;
    piVar7  = (volatile int *)0x2000230c;
    piVar6  = (volatile int *)0x2000230c;
    piVar5  = (volatile int *)0x2000230c;
    piVar4  = (volatile int *)0x2000230c;
    piVar2  = (volatile int *)0x2000230c;

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
    if (2 < g_log_level) {
        if (g_log_use_alt_sink == 0) log_message(0x000a3669,0x000a3a0f);
        else            debug_print(0x000a3669,0x000a3a0f);
    }
    puVar21 = *(u32 **)(param_1 + 0x1054);
    set_task_wake_state(1);
    iVar18 = now_has_persist_task(param_1, param_1[0xd5]);
    if (iVar18 == 0) {
        if (*param_2 != 2) {
            trigger_screen_state_change(0, param_1, 0);
            pcVar20 = (char *)get_device_info();
            if ((*pcVar20 == '\x02') && (iVar18 = get_device_info(), *(int *)(iVar18 + 0x40) == 0)) {
                iVar18 = get_device_info();
                submit_task_work(iVar18 + 0x38);
            }
        }
        param_1[0xd5] = '\0';
        puVar16 = *(u8 **)(param_1 + 0x1054);
        *puVar16 = 0;
        puVar16[1] = 0;
        puVar16[2] = 0;
        puVar16[3] = 0;
        *(u8 *)(*(int *)(param_1 + 0x1054) + 4) = 1;
        iVar18 = is_msg_expiration();
        if (iVar18 == 1) {
            cVar12 = '\x05';
        } else {
            iVar18 = get_device_info();
            cVar12 = *(char *)(iVar18 + 0xdd);
            if (cVar12 != '\0') cVar12 = '\x06';
        }
        set_task_display_mode(cVar12);
        publish_task_transition();
        if (*param_2 != 2) {
            iVar18 = 100;
            do {
                if (param_1[0xfe6] == '\x01') break;
                task_wait_ticks(0x148, 0);
                iVar18 = iVar18 + -1;
            } while (iVar18 != 0);
        }
        if (1 < *piVar10) {
            if (g_log_use_alt_sink == 0) log_message(0x000a3696,0x000a3875,**(u32 **)(param_1 + 0x1054),uVar19, (u32)(u8)param_1[0xd5]);
            else            debug_print(0x000a3696,0x000a3875,**(u32 **)(param_1 + 0x1054),uVar19, (u32)(u8)param_1[0xd5]);
        }
    }
    g_esb_notify_slave_role_guard = 0; /* *DAT_0002e0fc: same byte address */
    if (2 < *piVar10) {
        if (g_log_use_alt_sink == 0) { iVar18 = get_device_info(); log_message(0x000a36ff,0x000a3875,(u32)*(u8 *)(iVar18 + 0xdd), (u32)(u8)param_1[0x1070]); }
        else            { iVar18 = get_device_info(); debug_print(0x000a36ff,0x000a3875,(u32)*(u8 *)(iVar18 + 0xdd), (u32)(u8)param_1[0x1070]); }
    }
    puVar3 = g_20007b38;
    piVar2 = (volatile int *)0x20007554;
    uVar19 = 0;
LAB_0002df4c:
    if ((param_1[1] == '\x01') || (iVar18 = get_device_info(), *(char *)(iVar18 + 1) == '\b')) {
LAB_0002e012:
        iVar13 = local_2c[0];
        if (*param_1 == '\x01') {
            (*(void (**)(void *, int))(param_2 + 0x98))(param_2, 0x26);
            iVar13 = local_2c[0];
        }
        goto LAB_0002ce1c;
    }
    cVar12 = (char)task_transition_pending();
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
        iVar18 = is_battery_critical();
        if (iVar18 != 1) {
            if (((*(char *)(*(int *)(param_1 + 0x1014) + 1) == '\0') &&
                 (iVar18 = peer_address_is_uninitialized(iVar18,
                                                         (u32)(uVar22 >> 32)),
                  iVar18 != 0)) &&
                (iVar18 = get_device_info(), *(char *)(*(int *)(iVar18 + 0x1010) + 1) == '\0')) {
                if (((*param_2 == 2) && (iVar18 = get_task_signal_mode(), iVar18 == 0)) ||
                    (((int)(*puVar3 << 0x1e) < 0 && (iVar18 = get_task_signal_mode(), iVar18 == 1)))) {
                    if ((int)(*puVar3 << 0x1e) < 0) {
                        *puVar3 = *puVar3 & 0xfffffffd;
                    }
                    iVar18 = can_begin_task_transition();
                    if (iVar18 == 0) {
                        update_temp_task_status(param_1, 6, 2);
                        uVar14 = 0xa2733;
                        goto LAB_0002cd8c;
                    }
                    clear_active_task();
                    if (*param_1 == '\x01') {
                        sync_message_signal_to_slave(1);
                        clear_timeout_message(0);
                        reset_task_transition_state();
                        finalize_task_transition();
                        update_temp_task_status(param_1, 4, 2);
                        trigger_screen_state_change(0xa0a61, param_1, 1);
                    } else if (param_1[0xd5] != '\x04') {
                        goto LAB_0002e084;
                    }
                    if (*piVar10 < 1) goto LAB_0002cf58;
                    iVar18 = g_log_use_alt_sink;
                    uVar14 = 0xa37a8;
                    goto LAB_0002e184;
                }
LAB_0002e084:
                iVar18 = is_task_transition_ready();
                if (iVar18 == 1) {
                    if (param_1[0x108f] == '\0') {
                        if (*param_1 == '\x01') {
                            sync_message_signal_to_slave(0);
                            update_temp_task_status(param_1, 5, 2);
                            trigger_screen_state_change(0xa0a47, param_1, 1);
                            if (*piVar10 < 1) goto LAB_0002cf58;
                            iVar18 = g_log_use_alt_sink;
                            uVar14 = 0xa2831;
                            goto LAB_0002e184;
                        }
                        if (param_1[0xd5] != '\x05') goto LAB_0002e040;
                        if (0 < *piVar10) {
                            iVar18 = g_log_use_alt_sink;
                            uVar14 = 0xa37c8;
LAB_0002e184:
                            if (iVar18 == 0) log_message(uVar14,0x000a3875);
                            else             debug_print(uVar14,0x000a3875);
                        }
                        goto LAB_0002cf58;
                    }
                    clear_active_task();
                    if (*param_1 == '\x01') {
                        sync_message_signal_to_slave(1);
                        clear_timeout_message(0);
                        reset_task_transition_state();
                        finalize_task_transition();
                        update_temp_task_status(param_1, 4, 2);
                        uVar14 = 0xa0a61;
                        goto LAB_0002cd8c;
                    }
                    if (param_1[0xd5] == '\x04') goto LAB_0002ccda;
                }
                if ((param_1[0x108f] != '\0') && (uVar14 = 0xa37f6, param_1[0xd5] == '\x04'))
                    goto LAB_0002e00e;
            } else {
                uVar19 = uVar19 + 1;
                if (((uVar19 & 0x1f) == 0) && (0 < *piVar10)) {
                    if (g_log_use_alt_sink == 0) log_message(0x000a3770,0x000a3875);
                    else            debug_print(0x000a3770,0x000a3875);
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
    task_wait_ticks(0x667, 0);
    goto LAB_0002df4c;

CASE1:
    if (2 < g_log_level) {
        if (g_log_use_alt_sink == 0) log_message(0x000a3811,0x000a3a0f);
        else            debug_print(0x000a3811,0x000a3a0f);
    }
    trigger_screen_state_change(0xa383d, param_1, 0);
    while ((*param_2 != 1 && (iVar18 = get_task_signal_mode(), iVar18 != 1))) {
        if (((char)((int *)*(int **)(param_1 + 0x1054))[1] == '\x02') &&
            (**(int **)(param_1 + 0x1054) == 0x10)) {
            param_1[0xd5] = '\x10';
            trigger_screen_state_change(0xa3758, param_1, 1);
            iVar13 = local_2c[0];
            goto LAB_0002ce1c;
        }
        task_wait_ticks(0x667, 0);
    }
    uVar17 = 0;
LAB_0002cb9a:
    param_1[0xd5] = (char)uVar17;
    goto LAB_0002cf58;

CASE2:
    if (2 < g_log_level) {
        if (g_log_use_alt_sink == 0) log_message(0x000a2c85,0x000a3a0f);
        else            debug_print(0x000a2c85,0x000a3a0f);
    }
    piVar2 = (volatile int *)0x20007554;
    uVar19 = 0;
    while (1) {
        if ((*(char *)(*(int *)(param_1 + 0xff0) + 5) == '\0') || (param_1[0xfea] != '\n')) {
            if (2 < *piVar4) {
                if (g_log_use_alt_sink == 0) log_message(0x000a2cb2,0x000a39a0,(u32)(u8)param_1[0xd5]);
                else            debug_print(0x000a2cb2,0x000a39a0,(u32)(u8)param_1[0xd5]);
            }
            sync_to_slave(param_1, 8, 0);
            if (*param_2 == 2) update_persist_task_status_to_wait_blow_head();
            else               update_persist_task_status_to_idle(param_1);
            iVar13 = 0xa2ce2;
            if (*param_1 == '\x01') {
                task_wait_ticks(0x4000, 0);
                iVar13 = 0xa2ce2;
            }
            goto LAB_0002ce1c;
        }
        if ((param_1[1] == '\x01') || (iVar18 = get_device_info(), *(char *)(iVar18 + 1) == '\b')) {
            if (2 < *piVar4) {
                if (g_log_use_alt_sink == 0) log_message(0x000a2768,0x000a39a0,(u32)(u8)param_1[0xd5]);
                else            debug_print(0x000a2768,0x000a39a0,(u32)(u8)param_1[0xd5]);
            }
            update_persist_task_status_to_idle(param_1);
            iVar13 = 0xa2cfc;
            goto LAB_0002ce1c;
        }
        iVar18 = **(int **)(param_1 + 0xff0);
        if (iVar18 == 0) {
            *(u8 *)(*(int *)(param_1 + 0xff0) + 5) = 0;
            if (2 < *piVar4) {
                if (g_log_use_alt_sink == 0) log_message(0x000a2d1a,0x000a39a0,(u32)(u8)param_1[0xd5], (u32)*(u8 *)(*(int *)(param_1 + 0xff0) + 5));
                else            debug_print(0x000a2d1a,0x000a39a0,(u32)(u8)param_1[0xd5], (u32)*(u8 *)(*(int *)(param_1 + 0xff0) + 5));
            }
            local_2c[0] = 0xa2d5a;
            update_persist_task_status(param_1, **(u32 **)(param_1 + 0x1054), 1);
            iVar13 = local_2c[0];
            goto LAB_0002ce1c;
        }
        if (*param_2 == 2) break;
        uVar19 = uVar19 + 1;
        if (((uVar19 & 0xf) == 0) && (2 < *piVar4)) {
            if (*piVar2 == 0) log_message(0x000a2d97,0x000a39a0,uVar19,iVar18,(u32)*param_2, (u32)(u8)param_1[0xdd]);
            else              debug_print(0x000a2d97,0x000a39a0,uVar19,iVar18,(u32)*param_2, (u32)(u8)param_1[0xdd]);
        }
        if (param_1[0xd5] == '\x01') {
            iVar13 = 0xa2ad4;
            if (*piVar4 < 3) goto LAB_0002ce1c;
            uVar19 = (u8)param_1[0xd5];
            iVar18 = g_log_use_alt_sink;
            uVar14 = 0xa2de3;
            uVar15 = 0xa39a0;
            goto LAB_0002cbe8;
        }
        task_wait_ticks(0x667, 0);
    }
    if (param_1[0xdd] == '\0') {
        update_temp_task_status(param_1, 6);
    } else {
        update_temp_task_status(param_1, 4);
        reset_task_transition_state();
    }
    if (2 < *piVar4) {
        if (g_log_use_alt_sink == 0) log_message(0x000a2d6f,0x000a39a0,**(u32 **)(param_1 + 0x1054), (u32)(u8)param_1[0xd5]);
        else            debug_print(0x000a2d6f,0x000a39a0,**(u32 **)(param_1 + 0x1054), (u32)(u8)param_1[0xd5]);
    }
    update_persist_task_status(param_1, **(u32 **)(param_1 + 0x1054), 3);
    goto LAB_0002cf58;

CASE_DEFAULT:
    task_wait_ticks(0x8000, 0);
    goto LAB_0002ca3c;

CASE4:
    if (2 < g_log_level) {
        if (g_log_use_alt_sink == 0) log_message(0x000a2a7e,0x000a3a0f);
        else            debug_print(0x000a2a7e,0x000a3a0f);
    }
    iVar18 = process_task_state_four(param_1, param_1 + 0xd4, param_2, local_2c);
    goto LAB_0002ca34;

CASE5:
    if (2 < g_log_level) {
        if (g_log_use_alt_sink == 0) log_message(0x000a2a4d,0x000a3a0f);
        else            debug_print(0x000a2a4d,0x000a3a0f);
    }
    iVar18 = process_task_state_five(param_1, param_1 + 0xd4, param_2, local_2c);
LAB_0002ca34:
    iVar13 = local_2c[0];
    if (iVar18 == 10) goto LAB_0002ce1c;
LAB_0002ca3c:
    iVar13 = local_2c[0];
    if (iVar18 != 0xb) goto LAB_0002ce1c;
    goto LAB_0002cf58;

CASE6:
    if (2 < g_log_level) {
        if (g_log_use_alt_sink == 0) log_message(0x000a2aad,0x000a3a0f);
        else            debug_print(0x000a2aad,0x000a3a0f);
    }
    pcVar20 = (char *)&g_pending_message_flag;
    puVar3 = g_20007b38;
    uVar19 = 0;
    param_1[0xdc] = '\0';
    while (1) {
        if ((param_1[1] == '\x01') || (iVar18 = get_device_info(), *(char *)(iVar18 + 1) == '\b')) {
            if (2 < *piVar2) {
                if (g_log_use_alt_sink == 0) log_message(0x000a2768,0x000a39bb,(u32)(u8)param_1[0xd5]);
                else            debug_print(0x000a2768,0x000a39bb,(u32)(u8)param_1[0xd5]);
            }
            update_persist_task_status_to_idle(param_1);
            iVar13 = 0xa2ad4;
            goto LAB_0002ce1c;
        }
        if ((((*param_2 == 1) && (iVar18 = get_task_signal_mode(), iVar18 == 0)) ||
             (((int)(*puVar3 << 0x1e) < 0 && (iVar18 = get_task_signal_mode(), iVar18 == 1)))) ||
            (((int)(*puVar3 << 0x1e) < 0 && (iVar18 = get_task_signal_mode(), iVar18 == 2)))) {
            if ((int)(*puVar3 << 0x1e) < 0) {
                *puVar3 = *puVar3 & 0xfffffffd;
            }
            iVar18 = now_has_persist_task(param_1, param_1[0xd5]);
            if (iVar18 != 1) {
                sync_to_slave(param_1, 8, 0);
                update_persist_task_status_to_idle(param_1);
                iVar13 = 0xa2ad4;
                if (*piVar2 < 3) goto LAB_0002ce1c;
                uVar19 = (u8)param_1[0xd5];
                iVar18 = g_log_use_alt_sink;
                uVar14 = 0xa291d;
                uVar15 = 0xa39bb;
                goto LAB_0002cbe8;
            }
            if (2 < *piVar2) {
                if (g_log_use_alt_sink == 0) log_message(0x000a2af2,0x000a39bb,(u32)(u8)param_1[0xd5], **(u32 **)(param_1 + 0x1054));
                else            debug_print(0x000a2af2,0x000a39bb,(u32)(u8)param_1[0xd5], **(u32 **)(param_1 + 0x1054));
            }
            uVar17 = **(u32 **)(param_1 + 0x1054) & 0xff;
            goto LAB_0002cb9a;
        }
        iVar18 = now_has_persist_task(param_1, param_1[0xd5]);
        if (iVar18 == 1) {
            if (2 < *piVar2) {
                if (g_log_use_alt_sink == 0) log_message(0x000a2b22,0x000a39bb,(u32)(u8)param_1[0xd5], *(u32 *)(param_1 + 0xdf),(u32)(u8)param_1[0xe3]);
                else            debug_print(0x000a2b22,0x000a39bb,(u32)(u8)param_1[0xd5], *(u32 *)(param_1 + 0xdf),(u32)(u8)param_1[0xe3]);
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
            iVar13 = 0xa2ad4;
            if (*piVar2 < 3) goto LAB_0002ce1c;
            uVar19 = (u8)param_1[0xd5];
            iVar18 = g_log_use_alt_sink;
            uVar14 = 0xa2b59;
            uVar15 = 0xa39bb;
            goto LAB_0002cbe8;
        }
        if ((param_1[0x108f] != '\0') && (iVar18 = is_task_transition_ready(), iVar18 == 1)) {
            clear_active_task();
            if (*param_1 == '\x01') {
                sync_message_signal_to_slave(1);
                clear_timeout_message(0);
                reset_task_transition_state();
                finalize_task_transition();
                update_temp_task_status(param_1, 4, 2);
                uVar14 = 0xa0a61;
                goto LAB_0002cd8c;
            }
            if (param_1[0xd5] == '\x04') goto LAB_0002ccda;
        }
        if (param_1[0xd5] == '\x04') {
            if (*param_1 == '\x02') {
                task_wait_ticks(0x1334, 0);
            }
            iVar18 = g_log_use_alt_sink;
            uVar14 = 0xa2bc0;
            goto LAB_0002cd00;
        }
        if (param_1[0xfe6] == '\x01') {
            uVar14 = 0x667;
            goto LAB_0002cd18;
        }
        uVar19 = uVar19 + 1;
        if (((uVar19 & 0xf) == 0) && (2 < *piVar2)) {
            if (g_log_use_alt_sink == 0) log_message(0x000a2c0b,0x000a39bb,uVar19,**(u32 **)(param_1 + 0xff0), (u32)*param_2,(u32)(u8)param_1[0xdd],(u32)(u8)param_1[0xe3], *(u32 *)(param_1 + 0xdf),(u32)(u8)param_1[0xdc]);
            else            debug_print(0x000a2c0b,0x000a39bb,uVar19,**(u32 **)(param_1 + 0xff0), (u32)*param_2,(u32)(u8)param_1[0xdd],(u32)(u8)param_1[0xe3], *(u32 *)(param_1 + 0xdf),(u32)(u8)param_1[0xdc]);
        }
        if ((*pcVar20 != '\0') && (iVar18 = should_finish_task_wait(), iVar18 != 0)) break;
        get_device_info();
        task_wait_ticks(0x667, 0);
    }
    clear_active_task();
    set_task_display_mode(6);
    update_temp_task_status(param_1, 4, 2);
    uVar14 = 0xa2c70;
LAB_0002cd8c:
    trigger_screen_state_change(uVar14, param_1, 1);
    goto LAB_0002cf58;

CASE7:
    if (2 < g_log_level) {
        if (g_log_use_alt_sink == 0) log_message(0x000a32b6,0x000a3a0f);
        else            debug_print(0x000a32b6,0x000a3a0f);
    }
    uVar15 = 0xa3325;
    uVar14 = 0xa38f9;
    piVar2 = (volatile int *)0x20007554;
    uVar19 = 0;
    goto LAB_0002d6ce;

CASE8:
    if (2 < g_log_level) {
        if (g_log_use_alt_sink == 0) log_message(0x000a3290,0x000a3a0f);
        else            debug_print(0x000a3290,0x000a3a0f);
    }
    param_1[0xb0d] = '\0';
    iVar18 = get_device_info();
    uVar11 = (u8)read_task_mode();
    *(u8 *)(iVar18 + 0xdd) = uVar11;
    while ((*param_2 != 1 || (param_1[0xfea] != '\n'))) {
        task_wait_ticks(0x667, 0);
    }
    if (2 < *piVar7) {
        if (g_log_use_alt_sink == 0) log_message(0x000a291d,0x000a3916,(u32)(u8)param_1[0xd5]);
        else            debug_print(0x000a291d,0x000a3916,(u32)(u8)param_1[0xd5]);
    }
    sync_to_slave(param_1, 8, 0);
    update_persist_task_status_to_idle(param_1);
    local_2c[0] = 0xa3311;
    goto LAB_0002d118;

CASE9:
    if (2 < g_log_level) {
        if (g_log_use_alt_sink == 0) log_message(0x000a2e31,0x000a3a0f);
        else            debug_print(0x000a2e31,0x000a3a0f);
    }
    uVar15 = 0xa2f08;
    uVar14 = 0xa3982;
    piVar2 = (volatile int *)0x20007554;
    uVar19 = 0;
    iVar18 = *(int *)(param_1 + 0xffc);
    goto LAB_0002d03e;

CASE10:
    if (2 < g_log_level) {
        if (g_log_use_alt_sink == 0) log_message(0x000a30bd,0x000a3a0f);
        else            debug_print(0x000a30bd,0x000a3a0f);
    }
    uVar15 = 0xa318d;
    uVar14 = 0xa394b;
    piVar2 = (volatile int *)0x20007554;
    uVar19 = 0;
    pcVar20 = *(char **)(param_1 + 0x1000);
    goto LAB_0002d37c;

CASE11:
    if (2 < g_log_level) {
        if (g_log_use_alt_sink == 0) log_message(0x000a31da,0x000a3a0f);
        else            debug_print(0x000a31da,0x000a3a0f);
    }
    uVar15 = 0xa3244;
    uVar14 = 0xa3590;
    piVar2 = (volatile int *)0x20007554;
    uVar19 = 0;
    goto LAB_0002d4ce;

CASE12:
    if (2 < g_log_level) {
        if (g_log_use_alt_sink == 0) log_message(0x000a2f57,0x000a3a0f);
        else            debug_print(0x000a2f57,0x000a3a0f);
    }
    uVar15 = 0xa3071;
    uVar14 = 0xa3967;
    piVar2 = (volatile int *)0x20007554;
    uVar19 = 0;
    goto LAB_0002d1b4;

CASE14:
    if (2 < g_log_level) {
        if (g_log_use_alt_sink == 0) log_message(0x000a3373,0x000a3a0f);
        else            debug_print(0x000a3373,0x000a3a0f);
    }
    uVar15 = 0xa33de;
    uVar14 = 0xa38dd;
    piVar2 = (volatile int *)0x20007554;
    uVar19 = 0;
    goto LAB_0002d7ee;

CASE15:
    if (2 < g_log_level) {
        if (g_log_use_alt_sink == 0) log_message(0x000a342b,0x000a3a0f);
        else            debug_print(0x000a342b,0x000a3a0f);
    }
    uVar15 = 0xa34a2;
    uVar14 = 0xa38be;
    piVar2 = (volatile int *)0x20007554;
    uVar19 = 0;
    goto LAB_0002d998;

CASE16:
    if (2 < g_log_level) {
        if (g_log_use_alt_sink == 0) log_message(0x000a34f2,0x000a3a0f);
        else            debug_print(0x000a34f2,0x000a3a0f);
    }
    piVar2 = (volatile int *)0x20007554;
    uVar19 = 0;
    goto LAB_0002dac0;

CASE17:
    if (2 < g_log_level) {
        if (g_log_use_alt_sink == 0) log_message(0x000a35a2,0x000a3a0f);
        else            debug_print(0x000a35a2,0x000a3a0f);
    }
    uVar15 = 0xa3619;
    uVar14 = 0xa3886;
    piVar2 = (volatile int *)0x20007554;
    uVar19 = 0;
    goto LAB_0002dd2a;

LAB_0002cf58:
    iVar18 = 0xb;
    goto LAB_0002c9b6;

LAB_0002dd2a:
    if ((param_1[1] == '\x01') || (iVar18 = get_device_info(), *(char *)(iVar18 + 1) == '\b'))
        goto LAB_0002dd30;
    if (**(char **)(param_1 + 0x101c) == '\0') {
        local_2c[0] = 0xa35df;
        if (*param_2 != 2) {
            if (*piVar9 < 3) goto LAB_0002d2da;
            uVar19 = (u8)param_1[0xd5];
            iVar18 = g_log_use_alt_sink;
            uVar14 = 0xa3886;
            goto LAB_0002d5b8;
        }
        sync_to_slave(param_1, 8, 0);
        if (*piVar9 < 3) goto LAB_0002d9fc;
        bVar1 = param_1[0xd5];
        iVar18 = g_log_use_alt_sink;
        uVar14 = 0xa3886;
        goto LAB_0002d9f0;
    }
    if (param_1[0xd5] == '\x01') {
        iVar13 = 0xa35f7;
        if (2 < *piVar9) {
            if (g_log_use_alt_sink == 0) { log_message(0x000a2de3,0x000a3886,(u32)(u8)param_1[0xd5]); iVar13 = 0xa35f7; }
            else            { debug_print(0x000a2de3,0x000a3886,(u32)(u8)param_1[0xd5]); iVar13 = 0xa35f7; }
        }
        goto LAB_0002ce1c;
    }
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar9)) {
        if (*piVar2 == 0) log_message(uVar15,uVar14,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2, (u32)(u8)param_1[0xdd]);
        else              debug_print(uVar15,uVar14,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2, (u32)(u8)param_1[0xdd]);
    }
    task_wait_ticks(0x667, 0);
    goto LAB_0002dd2a;
LAB_0002dd30:
    if (2 < *piVar9) {
        if (g_log_use_alt_sink == 0) log_message(0x000a2768,0x000a3886,(u32)(u8)param_1[0xd5]);
        else            debug_print(0x000a2768,0x000a3886,(u32)(u8)param_1[0xd5]);
    }
    update_persist_task_status_to_idle(param_1);
    iVar13 = 0xa35cd;
    goto LAB_0002ce1c;

LAB_0002dac0:
    if (param_1[0xfea] == '\f') goto code_r0x0002dac8;
    if ((param_1[1] == '\x01') || (iVar18 = get_device_info(), *(char *)(iVar18 + 1) == '\b')) {
        if (2 < *piVar8) {
            bVar1 = param_1[0xd5];
            iVar18 = g_log_use_alt_sink;
            uVar14 = 0xa2768;
LAB_0002dc06:
            if (iVar18 == 0) log_message(uVar14,0x000a38a5,(u32)bVar1);
            else             debug_print(uVar14,0x000a38a5,(u32)bVar1);
        }
        goto LAB_0002db7c;
    }
    iVar18 = is_task_transport_blocked();
    if (((iVar18 == 0) && (iVar18 = get_device_info(), 1 < **(u8 **)(iVar18 + 0x100c))) &&
        (iVar18 = get_device_info(), **(u8 **)(iVar18 + 0x100c) < 10)) {
        iVar18 = get_device_info();
        **(u8 **)(iVar18 + 0x100c) = 10;
    }
    if (((*(char *)(*(int *)(param_1 + 0x100c) + 7) == '\0') ||
         (iVar18 = get_device_info(), **(char **)(iVar18 + 0x100c) == '\0')) ||
        (((**(char **)(param_1 + 0x100c) == '\b' || (**(char **)(param_1 + 0x100c) == '\v')) &&
          (param_1[0xdb] == '\0')))) {
        if (*param_1 == '\x01') {
            send_event(0);
        }
        if (*param_2 == 2) {
            sync_to_slave(param_1, 8, 0);
            if (2 < *piVar8) {
                bVar1 = param_1[0xd5];
                iVar18 = g_log_use_alt_sink;
                uVar14 = 0xa3215;
                goto LAB_0002dc06;
            }
        } else {
            if (2 < *piVar8) {
                if (g_log_use_alt_sink == 0) log_message(0x000a294a,0x000a38a5,(u32)(u8)param_1[0xd5]);
                else            debug_print(0x000a294a,0x000a38a5,(u32)(u8)param_1[0xd5]);
            }
            sync_to_slave(param_1, 8, 0);
        }
        goto LAB_0002db7c;
    }
    if (param_1[0xd5] == '\x01') {
        if (2 < *piVar8) {
            if (g_log_use_alt_sink == 0) log_message(0x000a2de3,0x000a38a5,(u32)(u8)param_1[0xd5]);
            else            debug_print(0x000a2de3,0x000a38a5,(u32)(u8)param_1[0xd5]);
        }
        set_task_wake_state(1);
        iVar13 = 0xa2a32;
        goto LAB_0002ce1c;
    }
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar8)) {
        if (*piVar2 == 0) log_message(0x000a3558,0x000a38a5,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2 ,(u32)(u8)param_1[0xdd]);
        else              debug_print(0x000a3558,0x000a38a5,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2 ,(u32)(u8)param_1[0xdd]);
    }
    if ((*param_1 == '\x01') &&
        (((**(u8 **)(param_1 + 0x100c) - 7 < 2 || (**(u8 **)(param_1 + 0x100c) == 0xb)) &&
          ((uVar19 * 0xcccccccdu >> 2 | uVar19 * 0xcccccccdu << 30) <= 0xcccccccu)))) {
        param_1[0xdb] = param_1[0xdb] + -1;
    }
    task_wait_ticks(0x667, 0);
    goto LAB_0002dac0;

LAB_0002d998:
    if ((param_1[1] == '\x01') || (iVar18 = get_device_info(), *(char *)(iVar18 + 1) == '\b'))
        goto LAB_0002d99e;
    if (**(char **)(param_1 + 0x1018) == '\0') {
        local_2c[0] = 0xa3468;
        if (*param_2 == 2) {
            sync_to_slave(param_1, 8, 0);
            if (2 < *piVar8) {
                bVar1 = param_1[0xd5];
                iVar18 = g_log_use_alt_sink;
                uVar14 = 0xa38be;
LAB_0002d9f0:
                if (iVar18 == 0) log_message(0x000a3215,uVar14,(u32)bVar1);
                else             debug_print(0x000a3215,uVar14,(u32)bVar1);
            }
            goto LAB_0002d9fc;
        }
        if (*piVar8 < 3) goto LAB_0002d2da;
        uVar19 = (u8)param_1[0xd5];
        iVar18 = g_log_use_alt_sink;
        uVar14 = 0xa38be;
        goto LAB_0002d5b8;
    }
    if (param_1[0xd5] == '\x01') {
        iVar13 = 0xa3480;
        if (2 < *piVar8) {
            if (g_log_use_alt_sink == 0) { log_message(0x000a2de3,0x000a38be,(u32)(u8)param_1[0xd5]); iVar13 = 0xa3480; }
            else            { debug_print(0x000a2de3,0x000a38be,(u32)(u8)param_1[0xd5]); iVar13 = 0xa3480; }
        }
        goto LAB_0002ce1c;
    }
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar8)) {
        if (*piVar2 == 0) log_message(uVar15,uVar14,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2, (u32)(u8)param_1[0xdd]);
        else              debug_print(uVar15,uVar14,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2, (u32)(u8)param_1[0xdd]);
    }
    task_wait_ticks(0x667, 0);
    goto LAB_0002d998;
LAB_0002d99e:
    if (2 < *piVar8) {
        if (g_log_use_alt_sink == 0) log_message(0x000a2768,0x000a38be,(u32)(u8)param_1[0xd5]);
        else            debug_print(0x000a2768,0x000a38be,(u32)(u8)param_1[0xd5]);
    }
    update_persist_task_status_to_idle(param_1);
    iVar13 = 0xa3456;
    goto LAB_0002ce1c;

LAB_0002d7ee:
    if ((param_1[1] == '\x01') || (iVar18 = get_device_info(), *(char *)(iVar18 + 1) == '\b'))
        goto LAB_0002d7f4;
    if (**(char **)(param_1 + 0x1014) == '\0') {
        local_2c[0] = 0xa33aa;
        if (*param_2 == 2) {
            sync_to_slave(param_1, 8, 0);
            if (2 < *piVar7) {
                if (g_log_use_alt_sink == 0) log_message(0x000a3215,0x000a38dd,(u32)(u8)param_1[0xd5]);
                else            debug_print(0x000a3215,0x000a38dd,(u32)(u8)param_1[0xd5]);
            }
        } else {
            if (2 < *piVar7) {
                if (g_log_use_alt_sink == 0) log_message(0x000a294a,0x000a38dd,(u32)(u8)param_1[0xd5]);
                else            debug_print(0x000a294a,0x000a38dd,(u32)(u8)param_1[0xd5]);
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
        iVar13 = 0xa33bf;
        if (2 < *piVar7) {
            if (g_log_use_alt_sink == 0) { log_message(0x000a2de3,0x000a38dd,(u32)(u8)param_1[0xd5]); iVar13 = 0xa33bf; }
            else            { debug_print(0x000a2de3,0x000a38dd,(u32)(u8)param_1[0xd5]); iVar13 = 0xa33bf; }
        }
        goto LAB_0002ce1c;
    }
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar7)) {
        if (*piVar2 == 0) log_message(uVar15,uVar14,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2, (u32)(u8)param_1[0xdd]);
        else              debug_print(uVar15,uVar14,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2, (u32)(u8)param_1[0xdd]);
    }
    task_wait_ticks(0x667, 0);
    goto LAB_0002d7ee;
LAB_0002d7f4:
    if (2 < *piVar7) {
        if (g_log_use_alt_sink == 0) log_message(0x000a2768,0x000a38dd,(u32)(u8)param_1[0xd5]);
        else            debug_print(0x000a2768,0x000a38dd,(u32)(u8)param_1[0xd5]);
    }
    update_persist_task_status_to_idle(param_1);
    iVar13 = 0xa339b;
    goto LAB_0002ce1c;

LAB_0002d1b4:
    if ((param_1[1] == '\x01') || (iVar18 = get_device_info(), *(char *)(iVar18 + 1) == '\b'))
        goto LAB_0002d1ba;
    if (**(char **)(param_1 + 0x1020) == '\0') {
        local_2c[0] = 0xa2f9c;
        if (*param_2 != 2) {
            if (2 < *piVar5) {
                if (g_log_use_alt_sink == 0) log_message(0x000a301e,0x000a3967,(u32)(u8)param_1[0xd5],0, (u32)(u8)param_1[0xfea],(u32)*param_2);
                else            debug_print(0x000a301e,0x000a3967,(u32)(u8)param_1[0xd5],0, (u32)(u8)param_1[0xfea],(u32)*param_2);
            }
            goto LAB_0002d2da;
        }
        if (2 < *piVar5) {
            if (g_log_use_alt_sink == 0) log_message(0x000a2fb0,0x000a3967,(u32)(u8)param_1[0xd5],0,(u32)(u8)param_1[0xfea] ,2);
            else            debug_print(0x000a2fb0,0x000a3967,(u32)(u8)param_1[0xd5],0,(u32)(u8)param_1[0xfea] ,2);
        }
        sync_to_slave(param_1, 8, 0);
        if (*param_2 == 2) update_persist_task_status_to_wait_blow_head();
        else               update_persist_task_status_to_idle(param_1);
        trigger_screen_state_change(0xa2733, param_1, 1);
        goto LAB_0002d118;
    }
    if (param_1[0xd5] == '\x01') {
        iVar13 = 0xa2ad4;
        if (*piVar5 < 3) goto LAB_0002ce1c;
        uVar19 = (u8)param_1[0xd5];
        iVar18 = g_log_use_alt_sink;
        uVar14 = 0xa2de3;
        uVar15 = 0xa3967;
        goto LAB_0002cbe8;
    }
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar5)) {
        if (*piVar2 == 0) log_message(uVar15,uVar14,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2, (u32)(u8)param_1[0xdd]);
        else              debug_print(uVar15,uVar14,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2, (u32)(u8)param_1[0xdd]);
    }
    task_wait_ticks(0x667, 0);
    goto LAB_0002d1b4;
LAB_0002d1ba:
    if (2 < *piVar5) {
        if (g_log_use_alt_sink == 0) log_message(0x000a2768,0x000a3967,(u32)(u8)param_1[0xd5]);
        else            debug_print(0x000a2768,0x000a3967,(u32)(u8)param_1[0xd5]);
    }
    update_persist_task_status_to_idle(param_1);
    iVar13 = 0xa2f7e;
    goto LAB_0002ce1c;

LAB_0002d4ce:
    if ((param_1[1] == '\x01') || (iVar18 = get_device_info(), *(char *)(iVar18 + 1) == '\b'))
        goto LAB_0002d4d4;
    if ((*(char *)(*(int *)(param_1 + 0x1004) + 6) == '\0') &&
        (*(char *)(*(int *)(param_1 + 0x1008) + 6) == '\0')) {
        local_2c[0] = 0xa3201;
        if (*param_2 != 2) {
            if (2 < *piVar6) {
                uVar19 = (u8)param_1[0xd5];
                iVar18 = g_log_use_alt_sink;
                uVar14 = 0xa3930;
LAB_0002d5b8:
                if (iVar18 == 0) log_message(0x000a294a,uVar14,uVar19);
                else             debug_print(0x000a294a,uVar14,uVar19);
            }
            goto LAB_0002d2da;
        }
        sync_to_slave(param_1, 8, 0);
        if (2 < *piVar6) {
            if (g_log_use_alt_sink == 0) log_message(0x000a3215,0x000a3930,(u32)(u8)param_1[0xd5]);
            else            debug_print(0x000a3215,0x000a3930,(u32)(u8)param_1[0xd5]);
        }
        goto LAB_0002d0b4;
    }
    if (param_1[0xd5] == '\x01') {
        iVar13 = 0xa2ad4;
        if (*piVar6 < 3) goto LAB_0002ce1c;
        uVar19 = (u8)param_1[0xd5];
        iVar18 = g_log_use_alt_sink;
        uVar14 = 0xa2de3;
        uVar15 = 0xa3930;
        goto LAB_0002cbe8;
    }
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar6)) {
        if (*piVar2 == 0) log_message(uVar15,uVar14,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2, (u32)(u8)param_1[0xdd]);
        else              debug_print(uVar15,uVar14,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2, (u32)(u8)param_1[0xdd]);
    }
    task_wait_ticks(0x667, 0);
    goto LAB_0002d4ce;
LAB_0002d4d4:
    if (2 < *piVar6) {
        if (g_log_use_alt_sink == 0) log_message(0x000a2768,0x000a3930,(u32)(u8)param_1[0xd5]);
        else            debug_print(0x000a2768,0x000a3930,(u32)(u8)param_1[0xd5]);
    }
    update_persist_task_status_to_idle(param_1);
    iVar13 = 0xa3201;
    goto LAB_0002ce1c;

LAB_0002d37c:
    if ((param_1[1] != '\x01') && (iVar18 = get_device_info(), *(char *)(iVar18 + 1) != '\b')) {
        if (*pcVar20 != '\0') {
            if (param_1[0xd5] != '\x01') goto LAB_0002d46a;
            iVar13 = 0xa2ad4;
            if (*piVar6 < 3) goto LAB_0002ce1c;
            uVar19 = (u8)param_1[0xd5];
            iVar18 = g_log_use_alt_sink;
            uVar14 = 0xa2de3;
            uVar15 = 0xa394b;
            goto LAB_0002cbe8;
        }
        local_2c[0] = 0xa3104;
        if (*param_2 != 2) {
            if (2 < *piVar6) {
                if (g_log_use_alt_sink == 0) log_message(0x000a315d,0x000a394b,(u32)(u8)param_1[0xd5],0);
                else            debug_print(0x000a315d,0x000a394b,(u32)(u8)param_1[0xd5],0);
            }
LAB_0002d2da:
            sync_to_slave(param_1, 8, 0);
LAB_0002d9fc:
            update_persist_task_status_to_idle(param_1);
            goto LAB_0002d118;
        }
        if (2 < *piVar6) {
            if (g_log_use_alt_sink == 0) log_message(0x000a3119,0x000a394b,(u32)(u8)param_1[0xd5],0,(u32)(u8)param_1[1]);
            else            debug_print(0x000a3119,0x000a394b,(u32)(u8)param_1[0xd5],0,(u32)(u8)param_1[1]);
        }
        sync_to_slave(param_1, 8, 0);
        update_persist_task_status_to_idle(param_1);
        trigger_screen_state_change(0xa2733, param_1, 1);
        goto LAB_0002d3ec;
    }
    goto LAB_0002d382;
LAB_0002d46a:
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar6)) {
        if (*piVar2 == 0) log_message(uVar15,uVar14,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2, (u32)(u8)param_1[0xdd]);
        else              debug_print(uVar15,uVar14,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2, (u32)(u8)param_1[0xdd]);
    }
    task_wait_ticks(0x667, 0);
    goto LAB_0002d37c;
LAB_0002d382:
    if (2 < *piVar6) {
        if (g_log_use_alt_sink == 0) log_message(0x000a2768,0x000a394b,(u32)(u8)param_1[0xd5]);
        else            debug_print(0x000a2768,0x000a394b,(u32)(u8)param_1[0xd5]);
    }
    update_persist_task_status_to_idle(param_1);
    iVar13 = 0xa30e5;
    goto LAB_0002ce1c;

LAB_0002d03e:
    if ((param_1[1] == '\x01') || (iVar13 = get_device_info(), *(char *)(iVar13 + 1) == '\b'))
        goto LAB_0002d044;
    if (*(char *)(iVar18 + 1) == '\0') {
        local_2c[0] = 0xa2e7c;
        finish_task_media();
        if (*param_2 == 2) {
            trigger_screen_state_change(0xa2733, param_1, 1);
            finish_task_audio();
            if (2 < *piVar5) {
                if (g_log_use_alt_sink == 0) log_message(0x000a2e93,0x000a3982,(u32)(u8)param_1[0xd5], (u32)*(u8 *)(iVar18 + 1),(u32)(u8)param_1[1]);
                else            debug_print(0x000a2e93,0x000a3982,(u32)(u8)param_1[0xd5], (u32)*(u8 *)(iVar18 + 1),(u32)(u8)param_1[1]);
            }
            sync_to_slave(param_1, 8, 0);
LAB_0002d0b4:
            update_persist_task_status_to_idle(param_1);
LAB_0002d3ec:
            if (*param_1 == '\x01') {
                task_wait_ticks(0x4000, 0);
            }
            uVar14 = 0x2667;
        } else {
            if (2 < *piVar5) {
                if (g_log_use_alt_sink == 0) log_message(0x000a2ed8,0x000a3982,(u32)(u8)param_1[0xd5], (u32)*(u8 *)(iVar18 + 1));
                else            debug_print(0x000a2ed8,0x000a3982,(u32)(u8)param_1[0xd5], (u32)*(u8 *)(iVar18 + 1));
            }
            sync_to_slave(param_1, 8, 0);
            update_persist_task_status_to_idle(param_1);
            finish_task_audio();
LAB_0002d118:
            iVar13 = local_2c[0];
            if (*param_1 != '\x01') goto LAB_0002ce1c;
            uVar14 = 0x4000;
        }
LAB_0002cd18:
        task_wait_ticks(uVar14, 0);
        iVar13 = local_2c[0];
        goto LAB_0002ce1c;
    }
    if (param_1[0xd5] == '\x01') {
        iVar13 = 0xa2ad4;
        if (2 < *piVar5) {
            uVar19 = (u8)param_1[0xd5];
            iVar18 = g_log_use_alt_sink;
            uVar14 = 0xa2de3;
            uVar15 = 0xa3982;
LAB_0002cbe8:
            if (iVar18 == 0) { log_message(uVar14,uVar15,uVar19); iVar13 = 0xa2ad4; }
            else             { debug_print(uVar14,uVar15,uVar19);                      iVar13 = 0xa2ad4; }
        }
        goto LAB_0002ce1c;
    }
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar5)) {
        if (*piVar2 == 0) log_message(uVar15,uVar14,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2, (u32)(u8)param_1[0xdd]);
        else              debug_print(uVar15,uVar14,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2, (u32)(u8)param_1[0xdd]);
    }
    task_wait_ticks(0x667, 0);
    goto LAB_0002d03e;
LAB_0002d044:
    if (2 < *piVar5) {
        if (g_log_use_alt_sink == 0) log_message(0x000a291d,0x000a3982,(u32)(u8)param_1[0xd5]);
        else            debug_print(0x000a291d,0x000a3982,(u32)(u8)param_1[0xd5]);
    }
    update_persist_task_status_to_idle(param_1);
    iVar13 = 0xa2e5b;
    goto LAB_0002ce1c;

LAB_0002d6ce:
    if ((param_1[1] == '\x01') || (iVar18 = get_device_info(), *(char *)(iVar18 + 1) == '\b'))
        goto LAB_0002d6d4;
    if (**(char **)(param_1 + 0x1010) == '\0') {
        local_2c[0] = 0xa32ef;
        if (*param_2 == 2) {
            if (2 < *piVar7) {
                bVar1 = param_1[0xd5];
                iVar18 = g_log_use_alt_sink;
                uVar14 = 0xa3215;
LAB_0002d71c:
                if (iVar18 == 0) log_message(uVar14,0x000a38f9,(u32)bVar1);
                else             debug_print(uVar14,0x000a38f9,(u32)bVar1);
            }
        } else if (2 < *piVar7) {
            bVar1 = param_1[0xd5];
            iVar18 = g_log_use_alt_sink;
            uVar14 = 0xa294a;
            goto LAB_0002d71c;
        }
        update_persist_task_status_to_idle(param_1);
        iVar13 = local_2c[0];
        goto LAB_0002ce1c;
    }
    if (param_1[0xd5] == '\x01') {
        iVar13 = 0xa3305;
        if (2 < *piVar7) {
            if (g_log_use_alt_sink == 0) { log_message(0x000a2de3,0x000a38f9,(u32)(u8)param_1[0xd5]); iVar13 = 0xa3305; }
            else            { debug_print(0x000a2de3,0x000a38f9,(u32)(u8)param_1[0xd5]); iVar13 = 0xa3305; }
        }
        goto LAB_0002ce1c;
    }
    uVar19 = uVar19 + 1;
    if (((uVar19 & 0xf) == 0) && (2 < *piVar7)) {
        if (*piVar2 == 0) log_message(uVar15,uVar14,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2, (u32)(u8)param_1[0xdd]);
        else              debug_print(uVar15,uVar14,uVar19,**(u32 **)(param_1 + 0xff0),(u32)*param_2, (u32)(u8)param_1[0xdd]);
    }
    task_wait_ticks(0x667, 0);
    goto LAB_0002d6ce;
LAB_0002d6d4:
    if (2 < *piVar7) {
        if (g_log_use_alt_sink == 0) log_message(0x000a2768,0x000a38f9,(u32)(u8)param_1[0xd5]);
        else            debug_print(0x000a2768,0x000a38f9,(u32)(u8)param_1[0xd5]);
    }
    update_persist_task_status_to_idle(param_1);
    iVar13 = 0xa32df;
    goto LAB_0002ce1c;

LAB_0002ccda:
    iVar18 = g_log_use_alt_sink;
    uVar14 = 0xa2ba7;
LAB_0002cd00:
    if (iVar18 == 0) log_message(uVar14);
    else             debug_print(uVar14);
    goto LAB_0002cf58;

code_r0x0002dac8:
    if (2 < *piVar8) {
        if (g_log_use_alt_sink == 0) log_message(0x000a3517,0x000a38a5,(u32)(u8)param_1[0xd5],(u32)(u8)param_1[1]);
        else            debug_print(0x000a3517,0x000a38a5,(u32)(u8)param_1[0xd5],(u32)(u8)param_1[1]);
    }
    sync_to_slave(param_1, 8, 0);
    if (*param_2 == 2) {
        update_persist_task_status_to_wait_blow_head();
    } else {
LAB_0002db7c:
        update_persist_task_status_to_idle(param_1);
    }
    set_task_wake_state(1);
    iVar13 = 0xa2a21;
LAB_0002ce1c:
    local_2c[0] = iVar13;
    iVar18 = local_2c[0];
    if (local_2c[0] != 0) {
        if (2 < g_log_level) {
            if (g_log_use_alt_sink == 0) log_message(0x000a384c,0x000a3a0f,(u32)(u8)param_1[0xd5],local_2c[0]);
            else            debug_print(0x000a384c,0x000a3a0f,(u32)(u8)param_1[0xd5],local_2c[0]);
        }
        trigger_screen_state_change(iVar18, param_1, 0);
        iVar18 = is_task_transition_ready();
        if (iVar18 == 1) {
            iVar18 = is_msg_expiration();
            if (iVar18 == 1) {
                cVar12 = '\x05';
            } else {
                iVar18 = get_device_info();
                cVar12 = *(char *)(iVar18 + 0xdd);
                if (cVar12 != '\0') cVar12 = '\x06';
            }
            set_task_display_mode(cVar12);
        }
    }
    return 0;
}
