#include "g1_net_symbols.h"
/* net-core FUN_01021a38 @ 0x1021a38 */
#include <stdint.h>

extern unsigned int FUN_01021ab4(void);
extern uint8_t *FUN_01021ac0(unsigned int index);
extern int FUN_01022e34(const void *descriptor, void *entry);

int FUN_01021a38(int owner, uint8_t *assigned_index)
{
    uint8_t index;
    unsigned int count;
    uint8_t *entry;
    int length;

    if (owner == 0)
        return -22;

    count = FUN_01021ab4();
    for (index = 0; index < count; ++index) {
        entry = FUN_01021ac0(index);
        if (entry[0x26] == 0)
            break;
    }
    if (index >= count || index == UINT8_MAX)
        return -12;

    entry = FUN_01021ac0(index);
    *(uint16_t *)(entry + 0x24) = 0;
    entry[0x26] = 0;
    entry[0x28] = index;
    length = FUN_01022e34((const void *)((unsigned long)&rodata_102a665) /*=0x102a665*/, entry);
    entry[0x27] = (uint8_t)length;
    if (length == 0x20)
        return -35;

    *(int *)(entry + 0x20) = owner;
    entry[0x26] = 1;
    *assigned_index = index;
    return 0;
}
