#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01008a58 @ 0x01008a58
 * public-name: FUN_01008a58
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_sdc_optfeat_fp_a                   @ 0x21000044
 *   g_net_sdc_optfeat_fp_c                   @ 0x21000048
 *   g_net_sdc_optfeat_fp_b                   @ 0x2100004c
 *   g_net_layout_count_table                 @ 0x21000a30
 */
/* net-core FUN_01008a58 @ 0x01008a58 */
#include <stdint.h>

extern int FUN_010098d8(uint32_t, void *);
extern int FUN_01009ea4(uint32_t, uint8_t, int);
extern int FUN_0100a1e0(uint32_t, uint8_t, uint8_t, uint16_t);
extern int FUN_0100a50c(uint32_t, uint8_t, uint8_t);
extern int FUN_0100a5c8(uint32_t, uint8_t, uint8_t);
extern int FUN_0100a664(uint8_t, uint8_t, uint32_t, int);
extern int FUN_0101077c(uint32_t);
extern void FUN_010217ac(uint32_t, uint32_t, uint32_t);
extern void FUN_01021820(uint32_t);
extern void FUN_0102182c(uint8_t, uint32_t);
extern void FUN_0102185c(uint32_t, uint32_t);
extern int FUN_01027846(uint8_t, uint8_t, uint8_t, uint8_t);
extern int FUN_010279e6(uint32_t, uint8_t, uint32_t);

typedef int (*encoder3_t)(uint32_t, uint8_t, uint8_t);
typedef int (*encoder1_t)(uint32_t);
typedef int (*encoder5_t)(uint32_t, uint8_t, uint8_t, uint8_t, uint8_t);

#define S ((volatile uint8_t *)((unsigned long)&g_net_layout_count_table) /*=0x21000a30*/)
#define FPA (*(volatile uintptr_t *)((unsigned long)&g_net_sdc_optfeat_fp_a) /*=0x21000044*/)
#define FPB (*(volatile uintptr_t *)((unsigned long)&g_net_sdc_optfeat_fp_b) /*=0x2100004c*/)
#define FPC (*(volatile uintptr_t *)((unsigned long)&g_net_sdc_optfeat_fp_c) /*=0x21000048*/)
#define ALIGN4(v) (((v) + 3u) & ~3u)
#define ALIGN8(v) (((v) + 7u) & ~7u)

int FUN_01008a58(uint32_t start, int sizing_only)
{
    uint8_t descriptor_frame[20];
    uint8_t *descriptor = descriptor_frame + 8;
    uint32_t cursor = ALIGN8(start);
    uint32_t call_pos;
    int n;

    descriptor[0] = 0;
    descriptor[1] = S[0];
    descriptor[2] = S[1];
    descriptor[3] = S[2];
    descriptor[4] = S[3];
    descriptor[5] = S[4];
    descriptor[6] = S[15];
    descriptor[7] = 0;
    descriptor[8] = S[21];
    descriptor[9] = S[22];
    descriptor[10] = S[23];
    descriptor[11] = S[24];
    if (S[30] != 0)
        descriptor[7] = S[4];

    n = FUN_010098d8(sizing_only == 0 ? cursor : 0, descriptor);
    cursor += (uint32_t)n;

    uint8_t count = (uint8_t)(S[0] + S[1]);
    int aggregate = 0;
    for (uint8_t i = 0; i < count; ++i)
        aggregate += FUN_01027846(S[5], S[6], S[7], S[8]);

    cursor = ALIGN4(cursor);
    n = FUN_01009ea4(sizing_only == 0 ? cursor : 0, count, aggregate);
    cursor += (uint32_t)n;

    if (S[2] != 0) {
        cursor = ALIGN4(cursor);
        n = FUN_0100a1e0(sizing_only == 0 ? cursor : 0, S[2],
                         (uint8_t)(S[15] + S[3]),
                         *(volatile uint16_t *)(S + 10));
        cursor += (uint32_t)n;
    }
    if (S[31] != 0 && S[9] != 0) {
        cursor = ALIGN4(cursor);
        n = FUN_0100a50c(sizing_only == 0 ? cursor : 0, S[9],
                         S[32] != 0 ? 0xffu : 0x25u);
        cursor += (uint32_t)n;
    }
    if (S[12] != 0 && (S[2] != 0 || (S[31] != 0 && S[9] != 0))) {
        cursor = ALIGN8(cursor);
        n = FUN_0101077c(sizing_only == 0 ? cursor : 0);
        cursor += (uint32_t)n;
    }
    if (FPA != 0 && S[4] != 0) {
        cursor = ALIGN4(cursor);
        n = ((encoder3_t)FPA)(sizing_only == 0 ? cursor : 0, S[4], S[13]);
        cursor += (uint32_t)n;
    }
    if (FPB != 0 && S[14] != 0) {
        cursor = ALIGN4(cursor);
        n = ((encoder1_t)FPB)(sizing_only == 0 ? cursor : 0);
        cursor += (uint32_t)n;
    }
    if (FPC != 0 && S[15] != 0) {
        cursor = ALIGN4(cursor);
        n = ((encoder5_t)FPC)(sizing_only == 0 ? cursor : 0,
                              S[15], S[16], S[17], S[18]);
        cursor += (uint32_t)n;
    }
    if (S[30] != 0 && S[4] != 0) {
        cursor = ALIGN4(cursor);
        n = FUN_0100a5c8(sizing_only == 0 ? cursor : 0, S[4], S[20]);
        cursor += (uint32_t)n;
    }

    uint32_t first_pos = 0;
    if (S[25] != 0) {
        first_pos = ALIGN8(cursor);
        n = FUN_010279e6(sizing_only == 0 ? first_pos : 0, S[25], 0x10e);
        cursor = first_pos + (uint32_t)n;
    }
    uint32_t second_pos = 0;
    if (S[26] != 0) {
        second_pos = ALIGN8(cursor);
        n = FUN_010279e6(sizing_only == 0 ? second_pos : 0, S[26], 0xfb);
        cursor = second_pos + (uint32_t)n;
    }
    if (sizing_only == 0)
        FUN_010217ac(first_pos, second_pos, 0xfb);

    if (S[27] == 0 || S[28] == 0) {
        if (sizing_only == 0)
            FUN_01021820(0);
    } else {
        call_pos = ALIGN8(cursor);
        n = FUN_010279e6(sizing_only == 0 ? call_pos : 0, S[27], 0x104);
        uint32_t payload = ((call_pos + (uint32_t)n + 3u) & ~7u) | 4u;
        n = FUN_0100a664(S[28], (uint8_t)(S[22] + S[24]), payload, sizing_only);
        cursor = payload + (uint32_t)n;
        if (sizing_only == 0) {
            FUN_01021820(call_pos);
            FUN_0102182c(S[27], 0x100);
        }
    }

    if (*(volatile uint32_t *)(S + 36) != 0) {
        if (sizing_only == 0)
            *(volatile uint32_t *)(S + 36) = cursor;
        cursor += 0x28u;
    }
    if (S[29] != 0) {
        call_pos = ALIGN8(cursor);
        n = FUN_010279e6(sizing_only == 0 ? call_pos : 0, S[29], 10000);
        cursor = call_pos + (uint32_t)n;
        if (sizing_only == 0)
            FUN_0102185c(call_pos, 10000);
    }
    return (int)(cursor - start);
}
