#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00035050 @ 0x00035050
 * public-name: verify_whitelist_json
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   whitelist_contains_app                   <= FUN_00034ff0 @ 0x00034ff0
 *   verify_whitelist_json                    <= FUN_00035050 @ 0x00035050
 *   cjson_delete                             <= FUN_00064b1c @ 0x00064b1c
 *   cbor_decode_start_default                <= FUN_0008500c @ 0x0008500c
 *   sllist_count_nodes                       <= FUN_00085020 @ 0x00085020
 *   sllist_node_at_index                     <= FUN_00085030 @ 0x00085030
 *   sllist_find_by_name_ci                   <= FUN_0008503c @ 0x0008503c
 *   cjson_is_array                           <= FUN_000850c8 @ 0x000850c8
 *   strncpy_zero_pad                         <= FUN_0008705a @ 0x0008705a
 * address symbols (name @ address):
 *   rodata_9a1dd                             @ 0x0009a1dd
 *   rodata_9e1b6                             @ 0x0009e1b6
 *   rodata_9e235                             @ 0x0009e235
 *   rodata_a862c                             @ 0x000a862c
 *   rodata_a8638                             @ 0x000a8638
 *   rodata_a864e                             @ 0x000a864e
 *   rodata_a866e                             @ 0x000a866e
 *   rodata_a869b                             @ 0x000a869b
 *   rodata_a870b                             @ 0x000a870b
 *   rodata_a8762                             @ 0x000a8762   [INLINED -- G6 literal batch]
 *   rodata_a886d                             @ 0x000a886d   [INLINED -- G6 literal batch]
 *   rodata_a8884                             @ 0x000a8884   [INLINED -- G6 literal batch]
 *   rodata_f33e4                             @ 0x000f33e4
 *   rodata_f3630                             @ 0x000f3630
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_whitelist_buffer                   @ 0x2001a22c
 */
/* Reconstructed FUN_00035050 @ 0x35050  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
typedef unsigned int uint;
typedef unsigned undefined4;
extern unsigned long whitelist_contains_app(const void*, const void*);
extern void cjson_delete(volatile int*);
extern int cbor_decode_start_default(void);
extern int sllist_count_nodes(int *);
extern int sllist_node_at_index(int a, uint b);
extern int sllist_find_by_name_ci(int, int);
extern int cjson_is_array(void);
extern void strncpy_zero_pad(void *a, unsigned b, int c);

undefined4 verify_whitelist_json(void)
{
    volatile int *dbgp = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    volatile unsigned char *pbVar2 = (volatile unsigned char *)((unsigned long)g_app_whitelist_buffer) /*=0x2001a22c*/;
    int *piVar1;
    unsigned char bVar3;
    int iVar4, iVar5, iVar6, iVar7;
    undefined4 uVar8;
    uint uVar9, uVar10, uVar11;
    unsigned char auStack_60[15], local_51, auStack_50[39], local_29;

    iVar4 = cbor_decode_start_default();
    if (iVar4 == 0) {
        if (*dbgp == 0) log_message(((unsigned long)"error root JSON NODE !\n") /*=0xa8762*/);
        else debug_print(((unsigned long)"error root JSON NODE !\n") /*=0xa8762*/);
        return 0;
    }
    iVar5 = sllist_find_by_name_ci(iVar4, ((unsigned long)&rodata_a862c) /*=0xa862c*/);
    if (iVar5 == 0) {
        iVar5 = *dbgp;
        uVar8 = ((unsigned long)&rodata_a8638) /*=0xa8638*/;
control_label_00035088:
        if (iVar5 == 0) log_message(uVar8);
        else debug_print(uVar8);
    } else {
        if ((int)((*pbVar2 & 1)) != (*(volatile int *)(iVar5 + 0xc) == 2)) {
            iVar5 = *dbgp;
            uVar8 = 0xa877a;
            goto control_label_00035088;
        }
        iVar5 = sllist_find_by_name_ci(iVar4, ((unsigned long)&rodata_a864e) /*=0xa864e*/);
        if (iVar5 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa8659;
            goto control_label_00035088;
        }
        if (((uint)*pbVar2 << 0x1e) >> 0x1f != (uint)(*(volatile int *)(iVar5 + 0xc) == 2)) {
            iVar5 = *dbgp;
            uVar8 = 0xa8798;
            goto control_label_00035088;
        }
        iVar5 = sllist_find_by_name_ci(iVar4, ((unsigned long)&rodata_a866e) /*=0xa866e*/);
        if (iVar5 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa87b5;
            goto control_label_00035088;
        }
        if (((uint)*pbVar2 << 0x1c) >> 0x1f != (uint)(*(volatile int *)(iVar5 + 0xc) == 2)) {
            iVar5 = *dbgp;
            uVar8 = 0xa87d3;
            goto control_label_00035088;
        }
        iVar5 = sllist_find_by_name_ci(iVar4, ((unsigned long)&rodata_a869b) /*=0xa869b*/);
        if (iVar5 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa87f5;
            goto control_label_00035088;
        }
        if (((uint)*pbVar2 << 0x1d) >> 0x1f != (uint)(*(volatile int *)(iVar5 + 0xc) == 2)) {
            iVar5 = *dbgp;
            uVar8 = 0xa8812;
            goto control_label_00035088;
        }
        iVar5 = sllist_find_by_name_ci(iVar4, ((unsigned long)&rodata_9e1b6) /*=0x9e1b6*/);
        if (iVar5 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa86c8;
            goto control_label_00035088;
        }
        iVar6 = sllist_find_by_name_ci(iVar5, ((unsigned long)&rodata_9e235) /*=0x9e235*/);
        if (iVar6 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa86db;
            goto control_label_00035088;
        }
        if (((uint)*pbVar2 << 0x1b) >> 0x1f != (uint)(*(volatile int *)(iVar6 + 0xc) == 2)) {
            iVar5 = *dbgp;
            uVar8 = 0xa8833;
            goto control_label_00035088;
        }
        iVar5 = sllist_find_by_name_ci(iVar5, ((unsigned long)&rodata_f3630) /*=0xf3630*/);
        if (iVar5 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa86f4;
            goto control_label_00035088;
        }
        iVar6 = cjson_is_array();
        if (iVar6 != 0) {
            bVar3 = sllist_count_nodes(iVar5);
            piVar1 = (int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
            uVar9 = (uint)bVar3;
            if (pbVar2[1] != uVar9) {
                iVar5 = *dbgp;
                uVar8 = 0xa8850;
                goto control_label_00035088;
            }
            uVar11 = 0;
            for (uVar10 = uVar11; (uVar10 & 0xff) < uVar9; uVar10 = uVar10 + 1) {
                iVar6 = sllist_node_at_index(iVar5, uVar10);
                if (iVar6 == 0) {
                    iVar6 = *piVar1;
                    uVar8 = ((unsigned long)&rodata_a870b) /*=0xa870b*/;
control_label_000351c4:
                    if (iVar6 == 0) log_message(uVar8);
                    else debug_print(uVar8);
                } else {
                    iVar7 = sllist_find_by_name_ci(iVar6, ((unsigned long)&rodata_9a1dd) /*=0x9a1dd*/);
                    if (iVar7 == 0) {
                        iVar6 = *piVar1;
                        uVar8 = 0xa8724;
                        goto control_label_000351c4;
                    }
                    iVar6 = sllist_find_by_name_ci(iVar6, ((unsigned long)&rodata_f33e4) /*=0xf33e4*/);
                    if (iVar6 == 0) {
                        iVar6 = *piVar1;
                        uVar8 = 0xa8739;
                        goto control_label_000351c4;
                    }
                    local_29 = 0;
                    local_51 = 0;
                    strncpy_zero_pad(auStack_50, *(volatile undefined4 *)(iVar7 + 0x10), 0x27);
                    strncpy_zero_pad(auStack_60, *(volatile undefined4 *)(iVar6 + 0x10), 0xf);
                    iVar6 = whitelist_contains_app(auStack_50, auStack_60);
                    if (iVar6 == 0) break;
                    uVar11 = uVar11 + 1 & 0xff;
                }
            }
            if (uVar11 == uVar9) {
                if (*dbgp == 0) log_message(((unsigned long)"the same whitelist ! \n") /*=0xa886d*/);
                else debug_print(((unsigned long)"the same whitelist ! \n") /*=0xa886d*/);
                uVar8 = 1;
                goto control_label_0003523e;
            }
        }
    }
    uVar8 = 0;
control_label_0003523e:
    cjson_delete(iVar4);
    if (*dbgp == 0) log_message(((unsigned long)"is_the_same_whitelist_app ret is %d\n") /*=0xa8884*/, uVar8);
    else debug_print(((unsigned long)"is_the_same_whitelist_app ret is %d\n") /*=0xa8884*/, uVar8);
    return uVar8;
}
