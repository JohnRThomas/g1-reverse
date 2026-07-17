/* FUN_010374dc @ 0x010374dc: remove a queued node and advance the head. */
#include <stdint.h>

extern void FUN_0103735c(uintptr_t list, void *node);
extern void FUN_01036f74(int force_advance);

void FUN_010374dc(uint8_t *node)
{
    if ((int8_t)node[0x0d] < 0) {
        node[0x0d] &= 0x7f;
        FUN_0103735c(0x21004b40u, node);
    }

    FUN_01036f74(*(uint8_t **)0x21004b30u == node);
}
