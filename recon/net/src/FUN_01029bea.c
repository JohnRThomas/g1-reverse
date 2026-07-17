/* net-core FUN_01029bea @ 0x1029bea  (CFG-directed candidate) */
#include <stdint.h>
extern uint32_t FUN_0101f924(void);
void FUN_01029bea(volatile uint8_t *packet)
{
    packet[3] = 0x1eu;
    packet[4] = (uint8_t)FUN_0101f924();
}
