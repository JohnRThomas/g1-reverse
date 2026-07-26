#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002c498 @ 0x0002c498
 * public-name: process_for_new_message_come_on
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   trigger_screen_state_change              <= FUN_0002bc2c @ 0x0002bc2c
 *   update_temp_task_status                  <= FUN_0002bffc @ 0x0002bffc
 *   update_persist_task_status_to_idle       <= FUN_0002c0e8 @ 0x0002c0e8
 *   update_persist_task_status_to_wait_blow_head <= FUN_0002c180 @ 0x0002c180
 *   check_pending_messages_flag              <= FUN_0002c1fc @ 0x0002c1fc
 *   sync_message_signal_to_slave             <= FUN_0002c224 @ 0x0002c224
 *   get_message_type_param                   <= FUN_0002c30c @ 0x0002c30c
 *   process_for_new_message_come_on          <= FUN_0002c498 @ 0x0002c498
 *   get_message_entry                        <= FUN_00033c4c @ 0x00033c4c
 *   clear_timeout_message                    <= FUN_00033d58 @ 0x00033d58
 *   push_message_3439c                       <= FUN_0003439c @ 0x0003439c
 *   set_message_pending_state                <= FUN_0003443c @ 0x0003443c
 *   set_new_message_pending_flag             <= FUN_00036030 @ 0x00036030
 * address symbols (name @ address):
 *   rodata_a0a7b                             @ 0x000a0a7b
 *   rodata_a2768                             @ 0x000a2768
 *   rodata_a2795                             @ 0x000a2795
 *   rodata_a27b1                             @ 0x000a27b1   [INLINED -- G6 literal batch]
 *   rodata_a28d4                             @ 0x000a28d4
 *   rodata_a39ef                             @ 0x000a39ef   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_0002c498 @ 0x2c498  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned char undefined1;
extern void log_message(unsigned, ...);
extern int get_device_info(void);
extern void debug_print(unsigned, ...);
extern void trigger_screen_state_change(unsigned a, byte *b, uint c);
extern void update_temp_task_status(byte *a, int b, int c);
extern void update_persist_task_status_to_idle(byte *a);
extern void update_persist_task_status_to_wait_blow_head(void);
extern void check_pending_messages_flag(void);
extern void sync_message_signal_to_slave(int a);
extern unsigned char get_message_type_param(byte a, int b);
extern void clear_timeout_message(int a);
extern int get_message_entry(int a);
extern void push_message_3439c(void);
extern void set_message_pending_state(int a);
extern void set_new_message_pending_flag(void);
extern void sync_to_slave(byte *a, int b, int c);
extern void FUN_0007ce5c(int a, int b);

undefined1 process_for_new_message_come_on(byte *param_1, int param_2, char *param_3, unsigned *param_4)
{
    volatile int *piVar1 = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    volatile int *piVar2 = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    undefined1 uVar3;
    int iVar4, iVar6;
    int *piVar5;
    char cVar7;
    uint uVar8, uVar9;
    int bVar10;

    uVar3 = get_message_type_param(param_1[0xfea], 0xf);
    *(volatile undefined1 *)(param_2 + 7) = uVar3;
    set_message_pending_state(2);
    iVar4 = get_device_info();
    uVar9 = 0;
    piVar5 = (int *)get_message_entry(*(volatile byte *)(iVar4 + 0xdd) - 1);
    iVar4 = *piVar5;
    do {
        if (((param_1[1] == 1) || (iVar6 = get_device_info(), *(volatile char *)(iVar6 + 1) == '\b')) ||
            (iVar6 = get_device_info(), *(volatile char *)(iVar6 + 0xfea) == '\f')) {
            if (2 < *piVar1) {
                if (*piVar2 == 0) log_message(((unsigned long)&rodata_a2768) /*=0xa2768*/, ((unsigned long)"process_for_new_message_come_on") /*=0xa39ef*/, (uint)*(volatile byte *)(param_2 + 1), *piVar2);
                else debug_print(((unsigned long)&rodata_a2768) /*=0xa2768*/, ((unsigned long)"process_for_new_message_come_on") /*=0xa39ef*/, (uint)*(volatile byte *)(param_2 + 1), *piVar2);
            }
            update_persist_task_status_to_idle(param_1);
            *param_4 = ((unsigned long)&rodata_a2795) /*=0xa2795*/;
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
            if (*piVar2 != 0) { debug_print(((unsigned long)"%s(): goto next screen, new screen %d !\r\n\n") /*=0xa27b1*/, ((unsigned long)"process_for_new_message_come_on") /*=0xa39ef*/, (uint)*(volatile byte *)(param_2 + 1), *piVar2); return 0xb; }
            log_message(((unsigned long)"%s(): goto next screen, new screen %d !\r\n\n") /*=0xa27b1*/, ((unsigned long)"process_for_new_message_come_on") /*=0xa39ef*/, (uint)*(volatile byte *)(param_2 + 1), *piVar2);
            return 0xb;
        }
        if ((*param_3 == '\x02') || (param_1[0xfea] == 0xb)) {
            if (2 < *piVar1) { if (*piVar2 == 0) log_message(0, 0); else debug_print(0); }
            set_new_message_pending_flag();
            if (2 < *piVar1) { if (*piVar2 == 0) log_message(0, 0); else debug_print(0); }
            if (param_1[0xb0d] == 1) {
                update_temp_task_status(param_1, 8, 2);
                set_message_pending_state(4);
                return 0xb;
            }
            if ((*(volatile char *)(param_2 + 1) == '\x05') && (uVar8 = (uint)*param_1, uVar8 == 1)) {
                sync_message_signal_to_slave(1);
                clear_timeout_message(0);
                check_pending_messages_flag();
                push_message_3439c();
                update_temp_task_status(param_1, 4, 2);
                trigger_screen_state_change(((unsigned long)&rodata_a0a7b) /*=0xa0a7b*/, param_1, uVar8);
                if (*piVar1 < 1) return 0xb;
                if (*piVar2 != 0) { debug_print(0); return 0xb; }
                log_message(0, 0);
                return 0xb;
            }
        }
        uVar9 = uVar9 + 1;
        if (((uVar9 & 0xf) == 0) && (2 < *piVar1)) {
            if (*piVar2 == 0) log_message(0, 0, (uint)*(volatile byte *)(param_2 + 7));
            else debug_print(0);
        }
        FUN_0007ce5c(0x667, 0);
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
        if (2 < *piVar1) { if (*piVar2 == 0) log_message(0, 0, (uint)*(volatile byte *)(param_2 + 1)); else debug_print(0); }
        *param_4 = ((unsigned long)&rodata_a28d4) /*=0xa28d4*/;
        sync_to_slave(param_1, 8, 0);
        if (*param_3 == '\x02') update_persist_task_status_to_wait_blow_head();
        else update_persist_task_status_to_idle(param_1);
        set_message_pending_state(6);
LAB_0002c4ec:
        uVar3 = 10;
    }
    return uVar3;
}
