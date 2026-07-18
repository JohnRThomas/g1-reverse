/* net-core FUN_0102583c @ 0x0102583c -- raw backmap retained. */
#include <stdint.h>

extern __attribute__((noreturn)) void FUN_010256dc(uint32_t, uint32_t, ...);
extern void FUN_01025734(void);
#define controller_fault FUN_010256dc

void FUN_0102583c(uint32_t event)
{
    volatile uint8_t *const slots = (volatile uint8_t *)0x21001c24u;

    if (event > 4)
        controller_fault(0x69, 0x58);
    volatile uint8_t *slot = slots + event * 8u;
    if (slot[4] != 1)
        controller_fault(0x69, 0x59);
    uint8_t next = (uint8_t)(slot[5] + 1u);
    if (slot[6] != next)
        slot[5] = next;
    FUN_01025734();
}
