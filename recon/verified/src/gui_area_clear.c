/* Reconstructed gui_area_clear @ 0x43228  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint32_t;

extern void FUN_0007dda4(unsigned long, ...);
extern uint32_t FUN_000167a8(void);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_000471cc(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f);
extern void FUN_00047260(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f);
extern uint32_t FUN_0007d4ec(void);

uint32_t gui_area_clear(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    volatile int *piVar1 = (volatile int*)0x2000230cUL;
    uint32_t iVar2;
    uint32_t uVar3;

    if (*piVar1 > 2) {
        if (*(volatile uint32_t*)0x20007554UL == 0) {
            FUN_0007dda4(0xaa8c8UL, 0xaae00UL);
        } else {
            FUN_00019c70(0xaa8c8UL, 0xaae00UL);
        }
    }
    iVar2 = FUN_0007d4ec();
    if (*(uint32_t*)(iVar2 + 0x35c) == 0) {
        if (*piVar1 > 0) {
            if (*(volatile uint32_t*)0x20007554UL == 0) {
                FUN_0007dda4(0xaa891UL, 0xaae00UL);
            } else {
                FUN_00019c70(0xaa891UL, 0xaae00UL);
            }
        }
        uVar3 = 0xffffffff;
    } else {
        iVar2 = FUN_000167a8();
        FUN_000471cc(iVar2 + 0xb90, 0, param_1, param_2, param_3, param_4);
        iVar2 = FUN_000167a8();
        uVar3 = *(uint32_t*)(iVar2 + 0xeb4);
        iVar2 = FUN_000167a8();
        FUN_00047260(uVar3, *(uint32_t*)(iVar2 + 0xeb8), param_1, param_2, param_3, param_4);
        uVar3 = 0;
    }
    return uVar3;
}
