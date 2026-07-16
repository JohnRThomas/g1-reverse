/* Reconstructed FUN_000857e0 @ 0x857e0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef void (*fn_t)(int *);
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

void FUN_000857e0(int *param_1)
{
    int iVar1;

    __DMB();
    iVar1 = *(int *)(*param_1 + 0x18);
    if ((*(unsigned int *)(*param_1 + 0x10) & 0x20000000) == 0) {
        if ((iVar1 != 0) || ((int)((unsigned int)*(unsigned short *)param_1[8] << 0x1f) < 0)) goto LAB_00085810;
    } else {
        if (iVar1 != 0) goto LAB_00085810;
        if (*(unsigned short *)((int)param_1 + 0x26) <=
            (unsigned short)((*(short *)(param_1[7] + 2) + -1) - *(short *)(param_1[8] + param_1[5] * 8 + 4)))
            goto LAB_00085810;
    }
    if ((fn_t)param_1[4] != (fn_t)0) {
        ((fn_t)param_1[4])(param_1);
    }
LAB_00085810:
    *(unsigned short *)((int)param_1 + 0x26) = 0;
}
