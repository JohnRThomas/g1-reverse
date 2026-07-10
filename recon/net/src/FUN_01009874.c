/* net-core FUN_01009874 @ 0x1009874  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01008d00(uint32_t a, uint32_t b);
extern void FUN_010095c0(void);

int32_t FUN_01009874(void)
{
    volatile uint8_t * const p1 = (uint8_t *)0x21000ba8;
    volatile uint32_t * const p2 = (uint32_t *)0x21000bb0;
    volatile uint32_t * const p3 = (uint32_t *)0x21000bac;
    int32_t iVar1;

    if (*p1 != 1 && *p1 != 3) {
        FUN_01008d00(0x17, 0x146);
    }

    if (*p1 == 3) {
        if (*p2 != *p3) {
            FUN_01008d00(0x17, 0x149);
        }
        FUN_010095c0();
        *p1 = 4;
        iVar1 = 0;
    } else {
        *p1 = 2;
        iVar1 = (int32_t)*p3;
    }
    return iVar1;
}

