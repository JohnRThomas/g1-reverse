/* Reconstructed power_down_panel @ 0x15fdc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, ...);
extern void FUN_000179e0(void);
extern void FUN_00019c70(uint32_t, ...);
extern int FUN_0007c038(int);
extern int FUN_00083dc8(int, ...);

unsigned int power_down_panel(void)
{
    volatile int *piVar1 = (volatile int*)0x2000230cUL;
    int iVar2;
    unsigned int format_string;

    FUN_0007c038(2);
    FUN_000179e0();
    if (0 < *piVar1) {
        if (*(volatile int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x0009949aUL, 0x00099c17UL);
        } else {
            FUN_00019c70(0x0009949aUL, 0x00099c17UL);
        }
    }
    FUN_0007c038(0x10);
    iVar2 = FUN_00083dc8(*(volatile uint32_t*)(*(volatile uint32_t*)(0x00087d10UL + 4) + 0x1c), 4, 3, 1);
    if (iVar2 < 0) {
        if (*piVar1 < 1) {
            return 0;
        }
        iVar2 = *(volatile int*)0x20007554UL;
        format_string = 0x0009940bUL;
    } else {
        if (0 < *piVar1) {
            if (*(volatile int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x000994b9UL, 0x00099c17UL);
            } else {
                FUN_00019c70(0x000994b9UL, 0x00099c17UL);
            }
        }
        FUN_0007c038(5);
        iVar2 = FUN_00083dc8(*(volatile uint32_t*)(*(volatile uint32_t*)(0x00087cf8UL + 4) + 0x1c), 8, 1);
        if (iVar2 < 0) {
            if (*piVar1 < 1) {
                return 0;
            }
            iVar2 = *(volatile int*)0x20007554UL;
            format_string = 0x00099329UL;
        } else {
            if (*piVar1 < 1) {
                return 0;
            }
            iVar2 = *(volatile int*)0x20007554UL;
            format_string = 0x000994d3UL;
        }
    }
    if (iVar2 == 0) {
        DEBUG_PRINT(format_string, 0x00099c17UL);
    } else {
        FUN_00019c70(format_string, 0x00099c17UL);
    }
    return 0;
}

