#include "g1_net_symbols.h"
/* net-core FUN_01020088 @ 0x1020088 */
#include <stdint.h>
extern void FUN_0101ff4c(void);
extern void FUN_01008d00(uint32_t, uint32_t);

void FUN_01020088(uint32_t mode)
{
    volatile uint32_t *const peripheral = (volatile uint32_t *)REG_4100e000 /*=0x4100e000*/;
    peripheral[0x500 / 4] = 0;
    peripheral[0x500 / 4] = 0;
    FUN_0101ff4c();
    peripheral[0x80 / 4] = 0;

    if (mode == 1) {
        peripheral[0x500 / 4] = 2;
        peripheral[0x514 / 4] = 0x210014e4;
    } else if (mode == 2) {
        peripheral[0x500 / 4] = 3;
        peripheral[0x514 / 4] = 0x210014e4;
        peripheral[0x80 / 4] = 0x80000003;
    } else if (mode != 0) {
        FUN_01008d00(0x3d, 0x82);
        peripheral[0x500 / 4] = 2;
        peripheral[0x514 / 4] = 0x210014e4;
    }
}
