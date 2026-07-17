/* Reconstructed clean_fb_data @ 0x471cc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void FUN_00019c70(unsigned int, unsigned int, ...);
extern void FUN_00086c78(int, void*, int);

int clean_fb_data(int param_1, void *param_2, int param_3, int param_4, int param_5, int param_6)
{
    int iVar1;
    uintptr_t row;
    uintptr_t end;
    if (0x27f < param_5) param_5 = 0x280;
    if (199 < param_6) param_6 = 200;
    if ((param_5 < param_3) || (param_6 < param_4)) {
        if (*(volatile int*)0x2000230cUL > 0) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0xd7347U, 0xd7374U);
            } else {
                FUN_00019c70(0xd7347U, 0xd7374U);
            }
        }
        iVar1 = -1;
    } else {
        param_3 = param_3/2;
        /* Firmware address arithmetic is 32-bit modular arithmetic.  Spell it
           through uintptr_t/uint32_t so negative row indices and wraparound do
           not invoke signed-overflow or out-of-object pointer arithmetic UB. */
        row = (uintptr_t)(uint32_t)param_1 +
              ((uint32_t)param_4 - 1u) * sizeof(uint32_t);
        end = (uintptr_t)(uint32_t)param_1 +
              (uint32_t)param_6 * sizeof(uint32_t);
        while (end != row) {
            row += sizeof(uint32_t);
            uintptr_t clear = (uintptr_t)*(uint32_t*)row +
                              (uint32_t)param_3;
            uint32_t count = 1u - (uint32_t)param_3 +
                             (uint32_t)(param_5/2);
            FUN_00086c78((int)(uint32_t)clear, param_2, (int)count);
        }
        iVar1 = (int)((uint32_t)(param_5/2) - (uint32_t)param_3 + 1u);
    }
    return iVar1;
}
