/* named: verify_whitelist_json */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
//   0x2001a22c  g_app_whitelist_buffer       
*/
/* Reconstructed verify_whitelist_json @ 0x35050  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned undefined4;
extern void DEBUG_PRINT(unsigned, ...);
extern void debug_print(unsigned, ...);
extern int whitelist_contains_app(void *a, void *b);
extern void cjson_delete(int a);
extern int FUN_0008500c(void);
extern int sllist_count_nodes(int a);
extern int sllist_node_at_index(int a, uint b);
extern int sllist_find_by_name_ci(int a, unsigned b);
extern int FUN_000850c8(void);
extern void strncpy_zero_pad(void *a, unsigned b, int c);

undefined4 verify_whitelist_json(void)
{
    volatile int *dbgp = (volatile int *)0x20007554;
    volatile unsigned char *pbVar2 = (volatile unsigned char *)0x2001a22c;
    int *piVar1;
    unsigned char bVar3;
    int iVar4, iVar5, iVar6, iVar7;
    undefined4 uVar8;
    uint uVar9, uVar10, uVar11;
    unsigned char auStack_60[15], local_51, auStack_50[39], local_29;

    iVar4 = FUN_0008500c();
    if (iVar4 == 0) {
        if (*dbgp == 0) DEBUG_PRINT(0xa8762);
        else debug_print(0);
        return 0;
    }
    iVar5 = sllist_find_by_name_ci(iVar4, 0xa862c);
    if (iVar5 == 0) {
        iVar5 = *dbgp;
        uVar8 = 0xa8638;
LAB_00035088:
        if (iVar5 == 0) DEBUG_PRINT(uVar8);
        else debug_print(0);
    } else {
        if ((int)((*pbVar2 & 1)) != (*(volatile int *)(iVar5 + 0xc) == 2)) {
            iVar5 = *dbgp;
            uVar8 = 0xa877a;
            goto LAB_00035088;
        }
        iVar5 = sllist_find_by_name_ci(iVar4, 0xa864e);
        if (iVar5 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa8659;
            goto LAB_00035088;
        }
        if (((uint)*pbVar2 << 0x1e) >> 0x1f != (uint)(*(volatile int *)(iVar5 + 0xc) == 2)) {
            iVar5 = *dbgp;
            uVar8 = 0xa8798;
            goto LAB_00035088;
        }
        iVar5 = sllist_find_by_name_ci(iVar4, 0xa866e);
        if (iVar5 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa87b5;
            goto LAB_00035088;
        }
        if (((uint)*pbVar2 << 0x1c) >> 0x1f != (uint)(*(volatile int *)(iVar5 + 0xc) == 2)) {
            iVar5 = *dbgp;
            uVar8 = 0xa87d3;
            goto LAB_00035088;
        }
        iVar5 = sllist_find_by_name_ci(iVar4, 0xa869b);
        if (iVar5 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa87f5;
            goto LAB_00035088;
        }
        if (((uint)*pbVar2 << 0x1d) >> 0x1f != (uint)(*(volatile int *)(iVar5 + 0xc) == 2)) {
            iVar5 = *dbgp;
            uVar8 = 0xa8812;
            goto LAB_00035088;
        }
        iVar5 = sllist_find_by_name_ci(iVar4, 0x9e1b6);
        if (iVar5 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa86c8;
            goto LAB_00035088;
        }
        iVar6 = sllist_find_by_name_ci(iVar5, 0x9e235);
        if (iVar6 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa86db;
            goto LAB_00035088;
        }
        if (((uint)*pbVar2 << 0x1b) >> 0x1f != (uint)(*(volatile int *)(iVar6 + 0xc) == 2)) {
            iVar5 = *dbgp;
            uVar8 = 0xa8833;
            goto LAB_00035088;
        }
        iVar5 = sllist_find_by_name_ci(iVar5, 0xf3630);
        if (iVar5 == 0) {
            iVar5 = *dbgp;
            uVar8 = 0xa86f4;
            goto LAB_00035088;
        }
        iVar6 = FUN_000850c8();
        if (iVar6 != 0) {
            bVar3 = sllist_count_nodes(iVar5);
            piVar1 = (int *)0x20007554;
            uVar9 = (uint)bVar3;
            if (pbVar2[1] != uVar9) {
                iVar5 = *dbgp;
                uVar8 = 0xa8850;
                goto LAB_00035088;
            }
            uVar11 = 0;
            for (uVar10 = uVar11; (uVar10 & 0xff) < uVar9; uVar10 = uVar10 + 1) {
                iVar6 = sllist_node_at_index(iVar5, uVar10);
                if (iVar6 == 0) {
                    iVar6 = *piVar1;
                    uVar8 = 0xa870b;
LAB_000351c4:
                    if (iVar6 == 0) DEBUG_PRINT(uVar8);
                    else debug_print(0);
                } else {
                    iVar7 = sllist_find_by_name_ci(iVar6, 0x9a1dd);
                    if (iVar7 == 0) {
                        iVar6 = *piVar1;
                        uVar8 = 0xa8724;
                        goto LAB_000351c4;
                    }
                    iVar6 = sllist_find_by_name_ci(iVar6, 0xf33e4);
                    if (iVar6 == 0) {
                        iVar6 = *piVar1;
                        uVar8 = 0xa8739;
                        goto LAB_000351c4;
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
                if (*dbgp == 0) DEBUG_PRINT(0xa886d);
                else debug_print(0);
                uVar8 = 1;
                goto LAB_0003523e;
            }
        }
    }
    uVar8 = 0;
LAB_0003523e:
    cjson_delete(iVar4);
    if (*dbgp == 0) DEBUG_PRINT(0xa8884, uVar8);
    else debug_print(0);
    return uVar8;
}

