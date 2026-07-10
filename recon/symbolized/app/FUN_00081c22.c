#include "g1_app_symbols.h"
/* named: FUN_00081c22 */
/* Reconstructed FUN_00081c22 @ 0x81c22  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_0005c76c(uint32_t,uint32_t,uint32_t,uint32_t);
typedef uint32_t u32; typedef uint16_t u16;
#define H(p,off) (*(u16*)((char*)(p)+(off)))
void FUN_00081c22(u32* param_1){
    u32 *puVar5, *puVar7, *puVar8;
    u32 uVar3, uVar9; u16 uVar4, uVar1;
    puVar5 = (u32*)((u32*)*param_1)[0xc];
    if(puVar5 != 0){
        puVar7 = (u32*)*puVar5;
        if(puVar7 != 0) puVar7 = puVar7 - 100;
        uVar4 = 0; uVar3 = 0;
        puVar5 = puVar5 - 100;
        do {
            puVar8 = puVar7;
            if(puVar5 == param_1) goto L54;
            while(1){
                if(uVar3 < H(puVar5,0x2e)) uVar3 = H(puVar5,0x2e);
                puVar8 = puVar7;
                if(uVar4 < H(puVar5,0x1e)) uVar4 = H(puVar5,0x1e);
            L54:
                if(puVar8 == 0) goto L64;
                puVar5 = puVar8;
                if(puVar8[100] != 0) break;
                puVar7 = 0;
                if(puVar8 == param_1) goto L64;
            }
            puVar7 = (u32*)(puVar8[100] - 400);
        } while(1);
    }
    uVar3 = 0; uVar4 = 0;
L64:
    uVar9 = H(param_1,0x2e);
    uVar1 = H(param_1,0x1e);
    if((uVar9 <= uVar3) && (uVar1 <= uVar4)) return;
    if(uVar4 < uVar1) uVar4 = uVar1;
    u32 uVar2 = *(u32*)*param_1;
    if(uVar3 < uVar9) uVar3 = uVar9;
    FUN_0005c76c(uVar2, uVar3, uVar4, uVar9);
}

