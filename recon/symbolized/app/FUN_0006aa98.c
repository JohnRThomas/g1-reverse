#include "g1_app_symbols.h"
/* named: FUN_0006aa98 */
/* Reconstructed FUN_0006aa98 @ 0x6aa98  (parity: 196/300 trials, PROVEN) */
#include <stdint.h>
static inline int32_t smlad(uint32_t a, uint32_t b, int32_t acc){
    return acc + (int32_t)(int16_t)a * (int32_t)(int16_t)b
               + (int32_t)(int16_t)(a>>16) * (int32_t)(int16_t)(b>>16);
}
void FUN_0006aa98(int64_t* param_1, int param_2, int16_t* param_3, int param_4){
    volatile int64_t* p1 = (volatile int64_t*)param_1;
    int iVar4 = ((uintptr_t)&tbl_8bc60) /*=0x8bcb8*/;
    if(param_4 > 0){
        uint32_t uVar12=0, uVar11=0xd60000, uVar8=0;
        volatile int16_t* local_2c=param_3;
        while(1){
            int iVar5 = (int)0xc22eeebf;
            int iVar6 = ((int)uVar12>>4) - 5;
            uint32_t uVar10 = *(volatile uint32_t*)(param_2 + iVar6*4);
            int iVar9 = iVar4 + uVar8*0x18;
            int p6 = param_2 + iVar6*4;
            uVar12 += 5;
            uVar8 = uVar12 & 0xf;
            int32_t s = smlad(uVar10, uVar11, 0);
            s = smlad(*(volatile uint32_t*)(p6+4), *(volatile uint32_t*)(iVar9+4), s);
            s = smlad(*(volatile uint32_t*)(p6+8), *(volatile uint32_t*)(iVar9+8), s);
            s = smlad(*(volatile uint32_t*)(p6+0xc), *(volatile uint32_t*)(iVar9+0xc), s);
            s = smlad(*(volatile uint32_t*)(p6+0x10), *(volatile uint32_t*)(iVar9+0x10), s);
            s = smlad(*(volatile uint32_t*)(p6+0x14), *(volatile uint32_t*)(iVar9+0x14), s);
            iVar6 = s;
            int64_t lVar2 = (int64_t)iVar6 * (int64_t)0x3ee61bc6;
            int64_t lVar3 = lVar2 + p1[0];
            uint32_t uVar7 = ((uint32_t)lVar3 >> 0x1e) | (uint32_t)((int)((uint64_t)lVar3>>0x20)*4);
            int64_t uVar1 = (int64_t)iVar6 * (int64_t)(int)0x8233c872 + p1[1];
            p1[0] = (int64_t)(int)uVar7 * (int64_t)(int)(0x8233c872u - 0x046c6a97u) + uVar1;
            p1[1] = (int64_t)(int)uVar7 * (int64_t)iVar5 + lVar2;
            *local_2c = (int16_t)(((int32_t)(uVar7 + 0x8000)) >> 0x10);
            if((int)uVar12 >= param_4*5) break;
            uVar11 = *(volatile uint32_t*)(iVar4 + uVar8*0x18);
            local_2c = local_2c + 1;
        }
    }
}

