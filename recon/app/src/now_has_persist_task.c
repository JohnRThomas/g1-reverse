/* Reconstructed now_has_persist_task @ 0x2be64  (parity: CFG state-case proven, 4/4 cases) */
#include <stdint.h>

extern void FUN_0007cdf8(void);                                              /* signal_persist_task_event (spinlock body) */
extern void FUN_0007dda4(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);  /* log_message */
extern void FUN_00019c70(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);  /* debug_print */

unsigned char now_has_persist_task(unsigned char *param_1, unsigned int param_2)
{
    volatile unsigned char *lock = (volatile unsigned char *)0x20018d9cUL;
    while (*lock != 0) {
        FUN_0007cdf8();
    }
    int *p = *(int **)(param_1 + 0x1054);
    unsigned int uVar3 = *((unsigned char *)p + 4);
    unsigned char uVar2 = 0;
    if (uVar3 > 1) {
        if (*(volatile int *)0x2000230cUL > 3) {
            unsigned int b = *(unsigned char *)(param_1 + 0xd5);
            if (*(volatile unsigned int *)0x20007554UL == 0) {
                FUN_0007dda4(0xa2566u, 0xa267bu, uVar3, param_2, b);
            } else {
                FUN_00019c70(0xa2566u, 0xa267bu, uVar3, param_2, b);
            }
        }
        uVar2 = 1;
    }
    return uVar2;
}
