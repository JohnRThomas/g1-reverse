/* Reconstructed gui_4bit_bitmap_override @ 0x43d78  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void *FUN_000167a8(void);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_000431a8(void);
extern int FUN_0004588c(int, uint32_t, int*, int*, uint32_t*, int);
extern void FUN_00047260(uint32_t, uint32_t, unsigned int, unsigned int, int, int);
extern void FUN_0007d586(int, int, int, int, int, int);

unsigned int gui_4bit_bitmap_override(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    int iVar1;
    unsigned int uVar2;
    int local_1c = 0;
    int local_18 = 0;
    uint32_t local_14 = 0;

    if ((param_2 < 0x281) && (param_3 < 0x1e1)) {
        iVar1 = FUN_0004588c(4, param_1, &local_1c, &local_18, &local_14, 0);
        if (-1 < iVar1) {
            FUN_0007d586(*(volatile uint32_t*)0x2000a034UL, local_14, local_1c, local_18, param_2, param_3);
            iVar1 = FUN_000431a8();
            if ((iVar1 << 0x1e) < 0) {
                iVar1 = (int)(intptr_t)FUN_000167a8();
                uVar2 = *(uint32_t*)(intptr_t)(iVar1 + 0xeb4);
                iVar1 = (int)(intptr_t)FUN_000167a8();
                FUN_00047260(uVar2, *(uint32_t*)(intptr_t)(iVar1 + 0xeb8), param_2, param_3, local_1c + param_2, local_18 + param_3);
            }
            return 0;
        }
        if (1 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x000aa8ebUL, 0x000aacafUL);
            } else {
                FUN_00019c70(0x000aa8ebUL, 0x000aacafUL);
            }
        }
    } else if (0 < *(volatile int*)0x2000230cUL) {
        if (*(volatile int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x000aaa01UL, 0x000aacafUL, param_2, param_3);
        } else {
            FUN_00019c70(0x000aaa01UL, 0x000aacafUL, param_2, param_3);
        }
    }
    return 0xffffffffUL;
}

