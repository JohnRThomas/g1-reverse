/* net-core FUN_01027a4a @ 0x1027a4a  (CFG-directed candidate) */
/* CPUNET 0x01027a4a, true executable extent 0x4a. Raw backmap: FUN_01027a4a. */
#include <stdint.h>
#include <cmsis_gcc.h>

void *FUN_01027a4a(void **head)
{
    uint32_t key = __get_PRIMASK();
    void *node;
    __disable_irq();
    node = *head;
    if (node != 0) {
        *head = *(void **)node;
        *(void **)node = 0;
    }
    if (key == 0u) {
        __enable_irq();
    }
    return node;
}
