#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00033f54 @ 0x00033f54
 * public-name: push_message
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   message_table_contains_id                <= FUN_00033f24 @ 0x00033f24
 *   push_message                             <= FUN_00033f54 @ 0x00033f54
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_a7dc5                             @ 0x000a7dc5
 *   rodata_a7e3d                             @ 0x000a7e3d   [INLINED -- refactor stage 01]
 *   rodata_a7e85                             @ 0x000a7e85   [INLINED -- refactor stage 01]
 *   rodata_a7ec3                             @ 0x000a7ec3
 *   rodata_a823b                             @ 0x000a823b
 *   rodata_a8248                             @ 0x000a8248
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_message_pool                           @ 0x20007dac
 *   g_message_table_mirror                   @ 0x20008eb4
 *   g_message_table_mirror_ovfl_slot         @ 0x20009e08
 *   g_message_table_slot_count               @ 0x2001a22b
 */
/* Reconstructed FUN_00033f54 @ 0x33f54  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
#include "../../../headers/g1_dedupe.h"
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
    unsigned int final_r2;
    long long uVar9;
    volatile int *g88 = (volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    volatile int *g94 = (volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;

    if (param_1 == 0) {
        uVar6 = 0x34f;
        iVar7 = *g88;
        format_string = ((unsigned long)&rodata_a7dc5) /*=0xa7dc5*/;
        uVar5 = ((unsigned long)&rodata_a8248) /*=0xa8248*/;
    } else {
        iVar7 = *g94;
        if (*(int *)(param_1 + 0x1b0) == 0) {
            uVar9 = message_table_contains_id(0x14, *(int *)(param_1 + 8), param_3, 0, param_1, param_2, param_3);
            uVar6 = (unsigned int)((unsigned long long)uVar9 >> 0x20);
            if ((int)uVar9 == 0) goto LAB_00033fb2;
            if (iVar7 < 1) return 0;
            iVar7 = *g88;
            format_string = 0x000a7ddf;
            uVar5 = ((unsigned long)&rodata_a823b) /*=0xa823b*/;
        } else {
            uVar9 = message_table_contains_id(0x14, *(int *)(param_1 + 8), param_3, *(int *)(param_1 + 0x1b0), param_1, param_2, param_3);
            uVar6 = (unsigned int)((unsigned long long)uVar9 >> 0x20);
            if ((int)uVar9 != 0) goto LAB_00033fb2;
            if (iVar7 < 1) return 0;
            iVar7 = *g88;
            format_string = 0x000a7e0f;
            uVar5 = ((unsigned long)&rodata_a823b) /*=0xa823b*/;
        }
    }
    G1_LOG_ROUTE(iVar7 == 0, format_string, uVar5, uVar6, iVar7);
    return 0;

LAB_00033fb2:
    pbVar1 = (unsigned char *)((unsigned long)&g_message_table_slot_count) /*=0x2001a22b*/;
    *(unsigned char *)(param_1 + 0xf) = 0;
    bVar4 = *pbVar1;
    uVar8 = (unsigned int)bVar4;
    if (uVar8 < 0x14) {
        iVar2 = uVar8 * 0x1b4 + ((unsigned long)g_message_pool) /*=0x20007dac*/;
        *(unsigned char *)(param_1 + 0xe) = 0;
        *(unsigned char *)(param_1 + 0xd) = 0;
        *(unsigned char *)(param_1 + 0xc) = bVar4;
        memcpy(iVar2, param_1, 0x1b4);
        final_r2 = 0x1b4;
        if (0 < iVar7) {
            G1_LOG_ROUTE(*g88 == 0, ((unsigned long)"%s(): update pos to %d, uidtail %d message->startShowTime %d action %d\n") /*=0xa7e3d*/, ((unsigned long)&rodata_a823b) /*=0xa823b*/, uVar8, *(int *)(param_1 + 8), *(int *)(param_1 + 4), *(int *)(param_1 + 0x1b0));
            final_r2 = uVar8;
        }
        bVar4 = *pbVar1 + 1;
    } else {
        final_r2 = 0;
        if (0 < iVar7) {
            G1_LOG_ROUTE(*g88 == 0, ((unsigned long)"%s(): update pos to %d, uidtail %d message->startShowTime %d\n") /*=0xa7e85*/, ((unsigned long)&rodata_a823b) /*=0xa823b*/, 0x13, uVar6, *(int *)(param_1 + 4));
        }
        iVar2 = 10;
        iVar7 = ((unsigned long)g_message_table_mirror) /*=0x20008eb4*/;
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
        memcpy(((unsigned long)g_message_table_mirror_ovfl_slot) /*=0x20009e08*/, param_1, 0x1b4);
        iVar7 = 0x20009dac;
        bVar4 = 0x14;
        *(unsigned short *)(0x20009dac + 0x68) = 0x13;
        *(unsigned char *)(iVar7 + 0x6a) = 0;
    }
    uVar6 = ((unsigned long)&rodata_a7ec3) /*=0xa7ec3*/;
    iVar7 = *g88;
    *pbVar1 = bVar4;
    G1_LOG_ROUTE(iVar7 == 0, uVar6, bVar4, final_r2, iVar7);
    return *pbVar1;
}
