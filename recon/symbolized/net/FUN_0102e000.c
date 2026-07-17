#include "g1_net_symbols.h"
/* net-core FUN_0102e000 @ 0x102e000  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_0102dcf4(uint32_t a);
extern int32_t FUN_0102df2c(void);
extern void FUN_01039bb0(uint32_t a, uint32_t b);
extern void FUN_01039bbe(uint32_t a, uint32_t b, uint32_t c);

typedef void (*fn_t)(uint32_t);

void FUN_0102e000(void)
{
    volatile uint8_t * const flag = (uint8_t *)((unsigned long)&g_net_dev_init_done_flag) /*=0x21004fad*/;

    if (*flag == 0) {
        uint32_t r4, r6, p0, p1;
        int32_t iVar3;
        fn_t f;

        FUN_0102dcf4(1);

        r4 = ((unsigned long)&rodata_103c0ec) /*=0x103c0ec*/;
        r6 = ((unsigned long)&rodata_103c0fc) /*=0x103c0fc*/;

        for (;;) {
            if (r4 > r6) {
                FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d5d7) /*=0x103d5d7*/, 0x188);
                FUN_01039bb0(((unsigned long)&rodata_103d5d7) /*=0x103d5d7*/, 0x188);
            } else if (r4 == r6) {
                break;
            }
            p1 = *(volatile uint32_t *)(r4 + 4);
            if (*(volatile uint8_t *)(p1 + 5) != 0) {
                p0 = *(volatile uint32_t *)(r4);
                f = (fn_t)(*(volatile uint32_t *)(p0 + 8));
                f(r4);
            }
            r4 += 0x10;
        }

        do {
            iVar3 = FUN_0102df2c();
        } while (iVar3 != 0);

        *flag = 1;
    }
}
