/* readable reconstruction; identity: FUN_000286f8 @ 0x000286f8
 * public-name: process_task_sync_event
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   esb_send_command_and_wait_ack            <= FUN_00027448 @ 0x00027448
 *   esb_pairing_sync_step                    <= FUN_000275fc @ 0x000275fc
 *   process_task_sync_event                  <= FUN_000286f8 @ 0x000286f8
 *   trigger_screen_state_change              <= FUN_0002bc2c @ 0x0002bc2c
 *   update_temp_task_status                  <= FUN_0002bffc @ 0x0002bffc
 *   check_pending_messages_flag              <= FUN_0002c1fc @ 0x0002c1fc
 *   sync_message_signal_to_slave             <= FUN_0002c224 @ 0x0002c224
 *   update_touch_key_flag                    <= FUN_0002c324 @ 0x0002c324
 *   get_low_battery_flag_if_master           <= FUN_0002efa8 @ 0x0002efa8
 *   mark_master_or_low_battery_flag          <= FUN_0002efc0 @ 0x0002efc0
 *   msg_content_recalc_unread                <= FUN_00033cf8 @ 0x00033cf8
 *   k_msleep_ticks32768_a                    <= FUN_0007cb8e @ 0x0007cb8e
 *   prepare_quick_note_mode                  <= FUN_0007cdb6 @ 0x0007cdb6
 *   reset_esb_sync_state                     <= FUN_0007ce60 @ 0x0007ce60
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   rodata_a0a7b                             @ 0x000a0a7b
 *   g_notify_wakeup_msg_sync_flag            @ 0x2000ff4d
 *   g_notify_wakeup_delay_flag               @ 0x20018d97
 */
/* Reconstructed FUN_000286f8 @ 0x286f8  (parity: 1/1 trials, PROVEN)
 * CFG_VERIFY_PREFIX_FIRST: intentional non-returning service loop. */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned undefined4;
typedef unsigned char undefined1;
extern int get_device_info(void);
extern void esb_send_command_and_wait_ack(unsigned a, int b, int c);
extern void esb_pairing_sync_step(void);
extern void trigger_screen_state_change(unsigned a, unsigned b, int c);
extern void update_temp_task_status(unsigned a, int b, int c);
extern void check_pending_messages_flag(void);
extern void sync_message_signal_to_slave(int a);
extern void update_touch_key_flag(void);
extern int get_low_battery_flag_if_master(void);
extern void mark_master_or_low_battery_flag(void);
extern int msg_content_recalc_unread(void);
extern void k_msleep_ticks32768_a(int a);
extern void prepare_quick_note_mode(unsigned a, int b);
extern void reset_esb_sync_state(int a);
extern void send_event_status(int a);
extern int sync_to_slave(unsigned a, int b, int c);
extern void thunk_FUN_00074844(int a, int b);
extern void update_persist_task_status(unsigned a, int b, int c);

void process_task_sync_event(unsigned param_1)
{
    volatile char *pcVar2 = (volatile char *)0x2000ff4d;
    volatile char *pcVar1 = (volatile char *)0x20018d97;
    int iVar3;
    char *pcVar4;
    unsigned uVar5;
    unsigned char uVar6;
    undefined1 *puVar7;

    do {
        while ((iVar3 = get_device_info(), *(volatile char *)(iVar3 + 1) == '\x01' ||
               (iVar3 = get_device_info(), *(volatile char *)(iVar3 + 1) == '\b'))) {
            thunk_FUN_00074844(0x28000, 0);
        }
        pcVar4 = (char *)get_device_info();
        if (*(volatile char *)pcVar4 == '\x01') {
            iVar3 = get_device_info();
            switch (**(volatile unsigned char **)(iVar3 + 0x100c)) {
            case 1:
                uVar5 = get_device_info();
                iVar3 = sync_to_slave(uVar5, 0xd, 0);
                if (iVar3 < 500) {
                    prepare_quick_note_mode(param_1, 0);
                    reset_esb_sync_state(0);
                    iVar3 = get_low_battery_flag_if_master();
                    if (iVar3 == 0) {
                        iVar3 = get_device_info();
                        uVar6 = 3;
                        puVar7 = *(volatile undefined1 **)(iVar3 + 0x100c);
                    } else {
                        iVar3 = get_device_info();
                        uVar6 = 2;
                        puVar7 = *(volatile undefined1 **)(iVar3 + 0x100c);
                    }
                    *(volatile undefined1 *)puVar7 = uVar6;
                    iVar3 = get_device_info();
                    if (**(volatile int **)(iVar3 + 0x1054) != 0x10) {
                        uVar5 = get_device_info();
                        update_persist_task_status(uVar5, 0x10, 2);
                    }
                }
                break;
            case 3:
                uVar5 = get_device_info();
                iVar3 = sync_to_slave(uVar5, 0xe, 0);
                if (iVar3 < 500) {
                    iVar3 = get_device_info();
                    uVar6 = 4;
                    puVar7 = *(volatile undefined1 **)(iVar3 + 0x100c);
LAB_0002884a:
                    *(volatile undefined1 *)puVar7 = uVar6;
                }
                break;
            case 5:
                uVar5 = get_device_info();
                iVar3 = sync_to_slave(uVar5, 0xf, 0);
                if (iVar3 < 500) {
                    mark_master_or_low_battery_flag();
                    send_event_status(0x18);
                    iVar3 = get_device_info();
                    uVar6 = 6;
                    puVar7 = *(volatile undefined1 **)(iVar3 + 0x100c);
                    goto LAB_0002884a;
                }
                break;
            case 10:
                uVar5 = get_device_info();
                iVar3 = sync_to_slave(uVar5, 0x10, 0);
                if (iVar3 < 500) {
                    iVar3 = get_device_info();
                    **(volatile undefined1 **)(iVar3 + 0x100c) = 0xb;
                    iVar3 = get_device_info();
                    *(volatile undefined1 *)(iVar3 + 0xdb) = 8;
                }
                break;
            case 0xd:
                uVar5 = get_device_info();
                iVar3 = sync_to_slave(uVar5, 0x11, 0);
                if (iVar3 < 500) {
                    iVar3 = get_device_info();
                    uVar6 = 0xe;
                    puVar7 = *(volatile undefined1 **)(iVar3 + 0x100c);
                    goto LAB_0002884a;
                }
                break;
            case 0xf:
                uVar5 = get_device_info();
                iVar3 = sync_to_slave(uVar5, 0x12, 0);
                if (iVar3 < 500) {
                    iVar3 = get_device_info();
                    uVar6 = 0x10;
                    puVar7 = *(volatile undefined1 **)(iVar3 + 0x100c);
                    goto LAB_0002884a;
                }
            }
        } else {
            iVar3 = get_device_info();
            if (**(volatile char **)(iVar3 + 0x100c) == '\x01') {
                uVar5 = get_device_info();
                esb_send_command_and_wait_ack(uVar5, 0xe, 0);
                prepare_quick_note_mode(param_1, 0);
            } else if (**(volatile char **)(iVar3 + 0x100c) == '\x05') {
                uVar5 = get_device_info();
                esb_send_command_and_wait_ack(uVar5, 0xf, 0);
            }
        }
        if (*pcVar1 != '\0') {
            k_msleep_ticks32768_a(2000);
            *pcVar1 = '\0';
        }
        esb_pairing_sync_step();
        pcVar4 = (char *)get_device_info();
        if ((*(volatile char *)pcVar4 == '\x01') && (*pcVar2 != '\0')) {
            sync_message_signal_to_slave(3);
            iVar3 = get_device_info();
            if ((*(volatile char *)(iVar3 + 0x108f) != '\0') &&
                ((iVar3 = msg_content_recalc_unread(), iVar3 != 0 &&
                  (iVar3 = get_device_info(), *(volatile char *)(iVar3 + 0xd5) != '\x04')))) {
                uVar5 = get_device_info();
                update_temp_task_status(uVar5, 4, 2);
                uVar5 = get_device_info();
                trigger_screen_state_change(0xa0a7b, uVar5, 1);
                check_pending_messages_flag();
            }
            *pcVar2 = '\0';
            update_touch_key_flag();
        }
        k_msleep_ticks32768_a(200);
    } while (1);
}
