#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102e23c @ 0x0102e23c
 * public-name: FUN_0102e23c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103c0ec                           @ 0x0103c0ec
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d635                           @ 0x0103d635
 */
/* net-core FUN_0102e23c @ 0x102e23c — true CFG extent 58 bytes (ends 0x102e276) */
#include <stdint.h>

extern uint64_t FUN_01039bb0(uint32_t a, uint32_t b);
extern void FUN_01039bbe(uint32_t a, uint32_t b, uint32_t c);
extern void FUN_0102ddf4(void);

void FUN_0102e23c(int32_t param_1, uint32_t param_2, uint8_t param_3)
{
    int32_t t;
    uint8_t r3;
    int32_t r4;
    int32_t r3w;

    t = param_1 - ((unsigned long)&rodata_103c0ec) /*=0x103c0ec*/;
    t = t >> 4;
    t = t + 1;
    r3 = (uint8_t)t;

    if (param_1 == 0) {
        FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d635) /*=0x103d635*/, 0xdf);
        /* Fatal in production. If the reporter returns, its ABI r0/r1 pair
           becomes the physical fall-through object/value arguments; r2
           remains the previously loaded 0xdf reason code. */
        uint64_t fatal_result = FUN_01039bb0(((unsigned long)&rodata_103d635) /*=0x103d635*/, 0xdf);
        param_1 = (int32_t)(uint32_t)fatal_result;
        param_2 = (uint32_t)(fatal_result >> 32);
        param_3 = 0xdf;
    }

    r4 = *(volatile int32_t *)(param_1 + 4);
    *(volatile uint8_t *)(r4 + 4) = r3;
    r3w = *(volatile int32_t *)(param_1 + 4);
    *(volatile uint8_t *)(r3w + 6) = param_3;
    r3w = *(volatile int32_t *)(param_1 + 4);
    *(volatile uint32_t *)(r3w) = param_2;
    r3w = *(volatile int32_t *)(param_1 + 4);
    *(volatile uint8_t *)(r3w + 5) = 1;

    FUN_0102ddf4();
}
