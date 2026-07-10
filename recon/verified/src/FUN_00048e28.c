/* Reconstructed FUN_00048e28 @ 0x48e28  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);
extern void FUN_00048b5c(void);

unsigned FUN_00048e28(unsigned param_1, unsigned param_2, unsigned param_3, int param_4)
{
    volatile int *piVar3 = (volatile int*)0x2000230c;
    volatile int *piVar2 = (volatile int*)0x20007554;
    unsigned uVar4 = *(volatile uint8_t*)0x2001d448;

    if (param_4 == 2) {
        if (param_2 != uVar4 && uVar4 != 0) {
            if (0 < *piVar3) {
                if (*piVar2 == 0) DEBUG_PRINT(); else FUN_00019c70();
                if (0 < *piVar3) {
                    if (*piVar2 == 0) DEBUG_PRINT(); else FUN_00019c70();
                    if (0 < *piVar3) {
                        if (*piVar2 == 0) DEBUG_PRINT(); else FUN_00019c70();
                    }
                }
            }
            FUN_00048b5c();
            return 0xffffffff;
        }
    } else if (param_4 == 1) {
        if (param_2 != uVar4 && uVar4 != 0) {
            if (0 < *piVar3) {
                if (*piVar2 == 0) DEBUG_PRINT(); else FUN_00019c70();
                if (0 < *piVar3) {
                    if (*piVar2 == 0) DEBUG_PRINT(); else FUN_00019c70();
                    if (0 < *piVar3) {
                        if (*piVar2 == 0) DEBUG_PRINT(); else FUN_00019c70();
                    }
                }
            }
            FUN_00048b5c();
            if (0 < *piVar3) {
                if (*piVar2 == 0) DEBUG_PRINT(); else FUN_00019c70();
            }
            *(volatile uint8_t*)0x2001d448 = (uint8_t)param_2;
        }
    } else {
        if (param_2 != uVar4 && 0 < *piVar3) {
            if (*piVar2 == 0) DEBUG_PRINT(); else FUN_00019c70();
            if (0 < *piVar3) {
                if (*piVar2 == 0) DEBUG_PRINT(); else FUN_00019c70();
            }
        }
    }
    FUN_00048b5c();
    return 0;
}

