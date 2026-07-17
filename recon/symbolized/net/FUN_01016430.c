#include "g1_net_symbols.h"
/* net-core FUN_01016430 @ 0x1016430 */
#include <stdint.h>

extern unsigned int FUN_0100a5b4(void);
extern __attribute__((noreturn)) void FUN_01008d00(unsigned int, unsigned int, ...);
extern void FUN_010202fc(unsigned int, unsigned int);
extern void FUN_010204f4(unsigned int);
extern void FUN_01020764(unsigned int);
extern int FUN_01021108(unsigned int, unsigned int);
extern int FUN_010212ec(unsigned int, unsigned int);

int FUN_01016430(int use_alternate_finish, unsigned int context)
{
    volatile uint8_t *const state = (volatile uint8_t *)0x21000f90;
    const uint8_t *const lookup = (const uint8_t *)((unsigned long)&rodata_103c24c) /*=0x103c24c*/;
    unsigned int mode;
    unsigned int amount;
    uint8_t mapped = lookup[state[0x7a]];

    FUN_010204f4(mapped);
    state[0x8f] = mapped;
    mode = state[0xbd + state[0x98]];

    switch (mode) {
    case 1:
    case 4:
    case 8:
        amount = FUN_0100a5b4();
        if (amount > 0x40)
            amount = 0x40;
        amount = (uint8_t)amount;
        break;
    case 2:
        amount = 0x0d;
        break;
    default:
        FUN_01008d00(0x32, 0x90f);
    }

    FUN_010202fc(amount, mode);
    FUN_01020764(context);
    if (use_alternate_finish)
        return FUN_010212ec(1, mode) != 0;
    FUN_01021108(1, mode);
    return 1;
}
