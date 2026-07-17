#include "g1_net_symbols.h"
/* net-core FUN_0100ec40 @ 0x100ec40  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern void FUN_0102583c(unsigned int a);

void FUN_0100ec40(void)
{
    /* g1_irq_lock/unlock map to Zephyr's arch_irq_lock/unlock in the project
     * integration and protect the ISR-visible intrusive-list update below. */
    unsigned char *puVar2 = (unsigned char *)((unsigned long)&g_net_pending_work_list) /*=0x21000ec8*/;
    unsigned int primask;
    unsigned int *puVar5;
    unsigned int uVar3;
    if (puVar2[0x20] != 0) return;
    *(unsigned int *)(puVar2 + 0x1c) = 0x0100f2e5;
    puVar2[0x20] = 2;
    primask = __get_PRIMASK();
    __disable_irq();
    puVar5 = (unsigned int *)(puVar2 + 8);
    *(unsigned int **)(puVar2 + 0x18) = puVar5;
    uVar3 = ((unsigned long)&g_net_ctrl_timeout_node_addr) /*=0x21000ee0*/;
    if ((*(int *)(puVar2+8) == 0) || (*(char*)(*(int*)(puVar2+8)+8) != 1)) {
        puVar5 = *(unsigned int **)(puVar2+4);
    }
    *puVar5 = uVar3;
    *(unsigned int *)(puVar2+4) = uVar3;
    if (primask == 0) __enable_irq();
    FUN_0102583c(*puVar2);
}
