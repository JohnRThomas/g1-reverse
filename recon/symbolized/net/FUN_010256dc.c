#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010256dc @ 0x010256dc
 * public-name: FUN_010256dc
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010256dc @ 0x010256dc -- raw backmap retained. */
#include <stdint.h>

extern uint32_t FUN_010255a4(void);

typedef void (*fault_reporter_t)(const char *module_text);

__attribute__((noreturn))
void FUN_010256dc(uint32_t module, uint32_t reason,
                  uint32_t detail, uint32_t context)
{
    /* The private controller deliberately enters its fatal path atomically. */
    __asm__ volatile("cpsid i" ::: "memory");
    fault_reporter_t reporter =
        *(fault_reporter_t volatile *)G1N_21001c1c;
    char text[12];
    *(uint32_t *)&text[0] = reason;
    *(uint32_t *)&text[4] = detail;
    *(uint32_t *)&text[8] = context;

    if (reporter != 0) {
        uint32_t value = module;
        uint8_t digits = 0;
        do {
            ++digits;
            value /= 10u;
        } while (value != 0);
        text[digits] = '\0';
        value = module;
        while (digits != 0) {
            --digits;
            uint32_t quotient = value / 10u;
            text[digits] = (char)('0' + value - quotient * 10u);
            value = quotient;
        }
        reporter(text);
        __builtin_unreachable();
    }

    (void)FUN_010255a4();
    ((void (*)(void))(uintptr_t)0)();
    __builtin_unreachable();
}
