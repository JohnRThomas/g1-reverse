/* Reconstructed FUN_000727ac @ 0x727ac  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00072040(void*);
extern int FUN_0007205c(void*);
extern void FUN_00072078(void*);
extern int FUN_00073f6c(void*,unsigned,void*,unsigned,unsigned,unsigned,unsigned);
extern uintptr_t g1_recon_tagged_heap_node_release(unsigned *node, int release);
extern void FUN_0007e2ec(unsigned,unsigned);
extern void FUN_0007e2fa(unsigned long, ...);

uint32_t FUN_000727ac(unsigned *param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    unsigned *puVar7 = param_1 + 2;
    unsigned uVar8 = 0;
    int iVar2 = FUN_00072040(puVar7);
    if (iVar2 == 0){
        FUN_0007e2fa(0x99cbd, 0x000f0920, 0x000f08c7, 0x72);
        FUN_0007e2fa(0x000f0935, puVar7);
        uVar8=0x72;
        FUN_0007e2ec(0x000f08c7, uVar8);
        return 0x72;
    }
    FUN_00072078(puVar7);
    unsigned *puVar6 = (unsigned*)*param_1;
    unsigned uVar3;
    if (puVar6 == 0){
        uVar3 = 0;
        if ((param_3 | param_4) != 0){
            int r = FUN_00073f6c(puVar7, uVar8, param_1+3, param_3|param_4, param_3, param_4, param_3);
            if (r != 0) return 0;
            return *(uint32_t*)(*(int*)(0x2000b448+8)+0x14);
        }
    } else {
        unsigned *puVar4 = (unsigned*)param_1[1];
        unsigned uVar5 = *puVar6 & 0xfffffffc;
        *param_1 = uVar5;
        if (puVar6 == puVar4){
            param_1[1] = uVar5;
        }
        uVar3 = (unsigned)g1_recon_tagged_heap_node_release(puVar6, 1);
    }
    iVar2 = FUN_0007205c(puVar7);
    if (iVar2 != 0){
        return uVar3;
    }
    FUN_0007e2fa(0x99cbd, 0x000f08f4, 0x000f08c7, 0xf0);
    FUN_0007e2fa(0x000f090b, puVar7);
    uVar8=0xf0;
    FUN_0007e2ec(0x000f08c7, uVar8);
    return uVar3;
}
