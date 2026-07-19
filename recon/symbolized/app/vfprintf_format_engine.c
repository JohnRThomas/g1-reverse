#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00077594 @ 0x00077594
 * public-name: vfprintf_format_engine
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   vfprintf_format_engine                   <= FUN_00077594 @ 0x00077594
 *   mem_find_byte                            <= FUN_00086bc8 @ 0x00086bc8
 *   vfprintf_emit_padded_field               <= FUN_00086e1c @ 0x00086e1c
 * address symbols (name @ address):
 *   rodata_f8b88                             @ 0x000f8b88
 */
/* Reconstructed FUN_00077594 @ 0x77594  (parity: 289/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef unsigned char byte;
extern int mem_find_byte(u32,...);
extern int vfprintf_emit_padded_field(u32,void*,void*,u32,u32);
extern u32 TAIL(void);

u32 vfprintf_format_engine(u32 param_1, u32 *param_2, u32 param_3, u32 param_4, int *param_5){
    int bVar1; int iVar2=0; u32 *puVar5; byte *puVar6;
    u32 uVar7; u32 uVar8=0; u32 uVar9=0; u32 *puVar10; byte *puVar11; u32 uVar12; byte bVar13;
    u32 local_24;

    bVar13 = (byte)param_2[6];
    puVar6 = (byte*)((char*)param_2 + 0x43);
    local_24 = param_4;
    if (0x78 < bVar13) { *(byte*)((char*)param_2 + 0x42) = bVar13; puVar11=(byte*)param_2+0x42; uVar8=1; goto L77798; }
    puVar11 = puVar6;
    if (bVar13 < 99) {
        if (bVar13 == 0) { param_2[4] = 0; goto AA; }
        iVar2 = ((unsigned long)&rodata_f8b88) /*=0xf8b88*/;
        if (bVar13 != 0x58) { *(byte*)((char*)param_2 + 0x42) = bVar13; puVar11=(byte*)param_2+0x42; uVar8=1; goto L77798; }
    } else {
        switch (bVar13) {
        case 99:
            uVar7 = *(u32*)(uintptr_t)*param_5;
            *param_5 = (int)(uintptr_t)((u32*)(uintptr_t)*param_5 + 1);
            *(char*)((char*)param_2 + 0x42) = (char)uVar7;
            puVar11=(byte*)param_2+0x42; uVar8=1; goto L77798;
        case 100:
        case 0x69:
            uVar9 = *param_2;
            puVar5 = (u32*)(uintptr_t)*param_5;
            *param_5 = (int)(uintptr_t)(puVar5 + 1);
            if (((int)(uVar9<<0x18)<0) || (-1 < (int)(uVar9<<0x19))) uVar8 = *puVar5;
            else uVar8 = (u32)(short)*puVar5;
            if (-1 < (int)uVar8) { uVar9=10; iVar2=((unsigned long)&rodata_f8b88) /*=0xf8b88*/; goto L776f6; }
            param_2[2] = param_2[1];
            *(byte*)((char*)param_2+0x43) = 0x2d;
            if (-1 < (int)param_2[1]) *param_2 = uVar9 & 0xfffffffb;
            uVar8 = -uVar8; uVar9 = 10; iVar2 = ((unsigned long)&rodata_f8b88) /*=0xf8b88*/;
            goto L77674;
        default:
            *(byte*)((char*)param_2 + 0x42) = bVar13; puVar11=(byte*)param_2+0x42; uVar8=1; goto L77798;
        case 0x6e:
            puVar10 = (u32*)(uintptr_t)*param_5;
            uVar9 = *param_2; uVar8 = param_2[5];
            *param_5 = (int)(uintptr_t)(puVar10 + 1);
            puVar5 = (u32*)(uintptr_t)*puVar10;
            if (((int)(uVar9<<0x18)<0) || (-1 < (int)(uVar9<<0x19))) *puVar5 = uVar8;
            else *(short*)puVar5 = (short)uVar8;
            param_2[4] = 0; goto AA;
        case 0x6f:
        case 0x75:
            puVar5 = (u32*)(uintptr_t)*param_5;
            uVar8 = *param_2;
            *param_5 = (int)(uintptr_t)(puVar5 + 1);
            if (((int)(uVar8<<0x18)<0) || (-1 < (int)(uVar8<<0x19))) uVar8 = *puVar5;
            else uVar8 = (u32)(unsigned short)*puVar5;
            iVar2 = ((unsigned long)&rodata_f8b88) /*=0xf8b88*/;
            if (bVar13 == 0x6f) uVar9 = 8; else uVar9 = 10;
            goto L776f0;
        case 0x70:
            *param_2 = *param_2 | 0x20;
            /* fallthrough */
        case 0x78:
            bVar13 = 0x78; iVar2 = 0xf8b99; break;
        case 0x73:
            puVar10 = (u32*)(uintptr_t)*param_5;
            *param_5 = (int)(uintptr_t)(puVar10 + 1);
            puVar6 = (byte*)(uintptr_t)*puVar10;
            iVar2 = mem_find_byte((u32)(uintptr_t)puVar6,0,param_2[1],(u32)(uintptr_t)puVar10,param_1,(u32)(uintptr_t)param_2,param_3);
            if (iVar2 != 0) param_2[1] = (u32)iVar2 - (u32)(uintptr_t)puVar6;
            uVar8 = param_2[1];
            goto L77798;
        }
    }
    /* shared X block (bVar13 == 0x58 / 0x78 / 0x70) */
    *(byte*)((char*)param_2 + 0x45) = bVar13;
    puVar5 = (u32*)(uintptr_t)*param_5;
    uVar9 = *param_2;
    *param_5 = (int)(uintptr_t)(puVar5 + 1);
    if (((int)(uVar9<<0x18)<0) || (-1 < (int)(uVar9<<0x19))) uVar8 = *puVar5;
    else uVar8 = (u32)(unsigned short)*puVar5;
    if ((int)(uVar9<<0x1f)<0) *param_2 = uVar9 | 0x20;
    if (uVar8 == 0) *param_2 = *param_2 & 0xffffffdf;
    uVar9 = 0x10;
L776f0:
    *(byte*)((char*)param_2 + 0x43) = 0;
L776f6:
    uVar12 = param_2[1];
    param_2[2] = uVar12;
    if ((((int)uVar12 < 0) || (*param_2 = *param_2 & 0xfffffffb, uVar8 != 0)) || (uVar12 != 0)) {
L77674:
        do {
            puVar11 = puVar11 + -1;
            *puVar11 = *(byte*)(uintptr_t)(iVar2 + (uVar8 - uVar9*(uVar8/uVar9)));
            bVar1 = uVar9 <= uVar8;
            uVar8 = uVar8 / uVar9;
        } while (bVar1);
    }
    if (((uVar9 == 8) && ((int)(*param_2<<0x1f)<0)) && ((int)param_2[1] <= (int)param_2[4])) {
        puVar11[-1] = 0x30;
        puVar11 = puVar11 + -1;
    }
    param_2[4] = (int)(uintptr_t)puVar6 - (int)(uintptr_t)puVar11;
    puVar6 = puVar11;
AA:
    iVar2 = vfprintf_emit_padded_field(param_1,param_2,&local_24,param_3,param_4);
    if (iVar2 == -1) return 0xffffffffUL;
    iVar2 = ((int (*)(u32,u32,const void*,u32))(uintptr_t)param_4)
        (param_1,param_3,puVar6,param_2[4]);
    if (iVar2 == -1) return 0xffffffffUL;
    if ((int)(*param_2 << 0x1e) < 0) {
        int pad = 0;
        while (pad < (int)(param_2[3] - local_24)) {
            iVar2 = ((int (*)(u32,u32,const void*,u32))(uintptr_t)param_4)
                (param_1,param_3,(byte*)param_2+0x19,1);
            if (iVar2 == -1) return 0xffffffffUL;
            ++pad;
        }
    }
    return param_2[3] < local_24 ? local_24 : param_2[3];

L77798:
    param_2[4] = uVar8;
    *((byte*)param_2 + 0x43) = 0;
    puVar6 = puVar11;
    goto AA;
}
