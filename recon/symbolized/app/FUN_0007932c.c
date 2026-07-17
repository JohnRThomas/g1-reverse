#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007932c @ 0x0007932c
 * public-name: FUN_0007932c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   mem_find_byte                            <= FUN_00086bc8 @ 0x00086bc8
 *   fnmatch_build_class_table                <= FUN_0008789c @ 0x0008789c
 * address symbols (name @ address):
 *   rodata_885b0                             @ 0x000885b0
 */
/* Reconstructed FUN_0007932c @ 0x7932c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
typedef unsigned char byte;
typedef u32 (*fn)(u32,...);
extern int mem_find_byte(u32 a, u32 b, u32 c);
extern void fnmatch_build_class_table(u32 a, u32 b);

u32 FUN_0007932c(u32 param_1, u32 *param_2, int *param_3, u32 *param_4){
    int iVar1; u32 uVar2; u32 uVar4; byte *pbVar5; u32 uVar6;
    u32 *puVar7; u32 *puVar8; u32 *puVar9; int iVar10; u32 *puVar11; int iVar12;
    u32 local_34[4];
    fn pcVar3;

    iVar12 = 0;
    local_34[0] = ((volatile u32*)((unsigned long)&rodata_885b0) /*=0x885b0*/)[0];
    local_34[1] = ((volatile u32*)((unsigned long)&rodata_885b0) /*=0x885b0*/)[1];
    local_34[2] = ((volatile u32*)((unsigned long)&rodata_885b0) /*=0x885b0*/)[2];
    pcVar3 = (fn)0x8712bUL;
    if (param_2[6] == 3) pcVar3 = (fn)0x87127UL;
    uVar6 = param_2[2];
    uVar4 = uVar6 - 1;
    if (uVar4 < 0x15d) iVar10 = 0;
    else { iVar10 = uVar6 - 0x15d; uVar6 = 0x15d; }
    if (0x15c < uVar4) param_2[2] = uVar6;
    puVar9 = param_2 + 7;
    *param_2 = *param_2 | 0xd00;
    puVar11 = puVar9;
  LAB_00079384:
    do {
        iVar1 = mem_find_byte(local_34[iVar12], *(byte*)(uintptr_t)*param_3, 2);
        puVar8 = puVar11;
        if (iVar1 != 0) {
            if (iVar12 == 1) {
                if (param_2[1] == 0) { param_2[1] = 8; *param_2 = *param_2 | 0x200; }
                *param_2 = *param_2 & 0xfffffaff;
                uVar4 = param_2[2]; param_2[2] = uVar4 - 1;
                if (uVar4 == 0) { iVar12 = 2; goto LAB_00079384; }
            } else if (iVar12 == 2) {
                if ((*param_2 & 0x600) != 0x200) break;
                *param_2 = *param_2 | 0x100;
                uVar4 = param_2[2]; param_2[1] = 0x10; param_2[2] = uVar4 - 1;
                if (uVar4 == 0) break;
            } else {
                uVar4 = param_2[2]; param_2[2] = uVar4 - 1;
                if (uVar4 == 0) { iVar12 = 1; goto LAB_00079384; }
            }
            pbVar5 = (byte*)(uintptr_t)*param_3;
            *param_3 = (int)(uintptr_t)(pbVar5 + 1);
            puVar8 = (u32*)((char*)puVar11 + 1);
            *(byte*)puVar11 = *pbVar5;
            iVar1 = param_3[1]; param_3[1] = iVar1 - 1;
            if ((iVar1 - 1 < 1) && (iVar1 = ((fn)(uintptr_t)param_2[0x60])(param_1, (u32)(uintptr_t)param_3), iVar1 != 0)) {
                iVar12 = 0; goto LAB_000794a0;
            }
        }
        iVar12 = iVar12 + 1;
        puVar11 = puVar8;
    } while (iVar12 != 3);
    if (param_2[1] == 0) param_2[1] = 10;
    iVar12 = 0;
    fnmatch_build_class_table(param_2[5], 0xf8d5aUL - param_2[1]);
    while (1) {
        puVar8 = puVar11;
        if (param_2[2] == 0) break;
        pbVar5 = (byte*)(uintptr_t)*param_3;
        uVar4 = (u32)*pbVar5;
        if (*(char*)(uintptr_t)(param_2[5] + uVar4) == '\0') break;
        if ((uVar4 == 0x30) && ((int)(*param_2 << 0x14) < 0)) {
            iVar12 = iVar12 + 1;
            if (iVar10 != 0) { iVar10 = iVar10 - 1; param_2[2] = param_2[2] + 1; }
        } else {
            *param_2 = *param_2 & 0xfffff6ff;
            puVar8 = (u32*)((char*)puVar11 + 1);
            *(byte*)puVar11 = *pbVar5;
        }
        iVar1 = param_3[1]; param_3[1] = iVar1 - 1;
        if (iVar1 - 1 < 1) {
            iVar1 = ((fn)(uintptr_t)param_2[0x60])(param_1, (u32)(uintptr_t)param_3);
            if (iVar1 != 0) break;
        } else {
            *param_3 = *param_3 + 1;
        }
        param_2[2] = param_2[2] - 1;
        puVar11 = puVar8;
    }
  LAB_000794a0:
    puVar11 = puVar8;
    if ((int)(*param_2 << 0x17) < 0) {
        if (puVar9 < puVar8) {
            puVar11 = (u32*)((char*)puVar8 - 1);
            ((fn)(uintptr_t)param_2[0x5f])(param_1, (u32)*(byte*)((char*)puVar8 - 1), (u32)(uintptr_t)param_3);
        }
        if (puVar11 == puVar9) return 1;
    }
    if ((*param_2 & 0x10) == 0) {
        *(byte*)puVar11 = 0;
        uVar2 = pcVar3(param_1, (u32)(uintptr_t)puVar9, 0, param_2[1]);
        puVar7 = (u32*)(uintptr_t)*param_4;
        uVar4 = *param_2;
        *param_4 = (u32)(uintptr_t)(puVar7 + 1);
        puVar7 = (u32*)(uintptr_t)*puVar7;
        if ((uVar4 & 0x20) == 0) {
            if ((int)(uVar4 << 0x1f) < 0) *(short*)puVar7 = (short)uVar2;
            else *puVar7 = uVar2;
        } else {
            *puVar7 = uVar2;
        }
        param_2[3] = param_2[3] + 1;
    }
    param_2[4] = (u32)((int)(uintptr_t)puVar11 + param_2[4] + (iVar12 - (int)(uintptr_t)puVar9));
    return 0;
}
