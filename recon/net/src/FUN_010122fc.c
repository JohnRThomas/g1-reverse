/* net-core FUN_010122fc @ 0x10122fc */
#include <stdint.h>

extern uint32_t FUN_01012308(void *, uint32_t);

uint32_t FUN_010122fc(void *record, uint32_t value)
{
    if ((*(uint16_t *)((uint8_t *)record + 2) & 0x18) != 0)
        return 1;
    return FUN_01012308(record, value);
}
