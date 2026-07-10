#include "g1_app_symbols.h"
/* named: push_message */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20007dac  g_message_pool               
//   0x20008eb4  g_message_table_mirror       
//   0x2001a22b  g_message_table_slot_count   
*/
/* Reconstructed push_message @ 0x33f54  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int, ...);
extern int debug_print(int, ...);
extern long long message_table_contains_id(int,int,int,int,int,int,int);
extern int memcpy(int, ...);

unsigned char push_message(int param_1, int param_2, int param_3)
{
    unsigned char *pbVar1;
    unsigned int format_string;
    int iVar2;
    int iVar3;
    unsigned char bVar4;
    unsigned int uVar5;
    unsigned int uVar6;
    int iVar7;
    unsigned int uVar8;
    long long uVar9;
    volatile int *g88 = (volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
    volatile int *g94 = (volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;

    if (param_1 == 0) {
        uVar6 = 0x34f;
        iVar7 = *g88;
        format_string = "[%s-%d] message is NULL \n" /*=0xa7dc5*/;
        uVar5 = "push_message" /*=0xa8248*/;
    } else {
        iVar7 = *g94;
        if (*(int *)(param_1 + 0x1b0) == 0) {
            uVar9 = message_table_contains_id(0x14, *(int *)(param_1 + 8), param_3, 0, param_1, param_2, param_3);
            uVar6 = (unsigned int)((unsigned long long)uVar9 >> 0x20);
            if ((int)uVar9 == 0) goto LAB_00033fb2;
            if (iVar7 < 1) return 0;
            iVar7 = *g88;
            format_string = "%s(): slave add found same message, uidtail %d\n" /*=0xa7ddf*/;
            uVar5 = "push_message" /*=0xa823b*/;
        } else {
            uVar9 = message_table_contains_id(0x14, *(int *)(param_1 + 8), param_3, *(int *)(param_1 + 0x1b0), param_1, param_2, param_3);
            uVar6 = (unsigned int)((unsigned long long)uVar9 >> 0x20);
            if ((int)uVar9 != 0) goto LAB_00033fb2;
            if (iVar7 < 1) return 0;
            iVar7 = *g88;
            format_string = "%s(): can not found same message, uidtail %d\n" /*=0xa7e0f*/;
            uVar5 = "push_message" /*=0xa823b*/;
        }
    }
    if (iVar7 == 0) {
        DEBUG_PRINT(format_string, uVar5, uVar6);
    } else {
        debug_print(0);
    }
    return 0;

LAB_00033fb2:
    pbVar1 = (unsigned char *)((uintptr_t)&g_message_table_slot_count) /*=0x2001a22b*/;
    *(unsigned char *)(param_1 + 0xf) = 0;
    bVar4 = *pbVar1;
    uVar8 = (unsigned int)bVar4;
    if (uVar8 < 0x14) {
        iVar2 = uVar8 * 0x1b4 + (g_message_pool) /*=0x20007dac*/;
        *(unsigned char *)(param_1 + 0xe) = 0;
        *(unsigned char *)(param_1 + 0xd) = 0;
        *(unsigned char *)(param_1 + 0xc) = bVar4;
        memcpy(iVar2, param_1);
        if (0 < iVar7) {
            if (*g88 == 0) {
                DEBUG_PRINT("%s(): update pos to %d, uidtail %d message->startShowTime %d action %d\n" /*=0xa7e3d*/, "push_message" /*=0xa823b*/, uVar8, *(int *)(param_1 + 8), *(int *)(param_1 + 4), *(int *)(param_1 + 0x1b0));
            } else {
                debug_print("%s(): update pos to %d, uidtail %d message->startShowTime %d action %d\n" /*=0xa7e3d*/);
            }
        }
        bVar4 = *pbVar1 + 1;
    } else {
        if (0 < iVar7) {
            if (*g88 == 0) {
                DEBUG_PRINT("%s(): update pos to %d, uidtail %d message->startShowTime %d\n" /*=0xa7e85*/, "push_message" /*=0xa823b*/, 0x13, uVar6, *(int *)(param_1 + 4));
            } else {
                debug_print("%s(): update pos to %d, uidtail %d message->startShowTime %d\n" /*=0xa7e85*/, "push_message" /*=0xa823b*/, 0x13);
            }
        }
        iVar2 = 10;
        iVar7 = (g_message_table_mirror) /*=0x20008eb4*/;
        do {
            if (*(char *)(iVar7 + 0xd) == '\0') {
                iVar3 = memcpy(iVar7, iVar7 + 0x1b4, 0x1b4);
                *(char *)(iVar3 + 0xc) = (char)iVar2;
                if (*(char *)(iVar3 + 0xe) == '\0') {
                    *(unsigned char *)(param_1 + 0xd) = 0;
                }
            }
            iVar2 = iVar2 + 1;
            iVar7 = iVar7 + 0x1b4;
        } while (iVar2 != 0x13);
        memcpy((g_message_table_mirror_ovfl_slot) /*=0x20009e08*/, param_1, 0x1b4);
        iVar7 = ((uintptr_t)&g_push_message_slot_hdr) /*=0x20009dac*/;
        bVar4 = 0x14;
        *(unsigned short *)(((uintptr_t)&g_push_message_slot_hdr) /*=0x20009dac*/ + 0x68) = 0x13;
        *(unsigned char *)(iVar7 + 0x6a) = 0;
    }
    uVar6 = "[csh_debug_msg]push_message g_msg_num_push is %d \n" /*=0xa7ec3*/;
    iVar7 = *g88;
    *pbVar1 = bVar4;
    if (iVar7 == 0) {
        DEBUG_PRINT(uVar6);
    } else {
        debug_print(0);
    }
    return *pbVar1;
}

