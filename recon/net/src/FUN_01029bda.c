/* net-core FUN_01029bda @ 0x1029bda  (CFG-directed candidate) */
#include <stdint.h>
extern uint32_t FUN_0101f924(void);
void FUN_01029bda(volatile uint8_t *packet)
{
    packet[3] = 0x1du;
    packet[4] = (uint8_t)FUN_0101f924();
}
