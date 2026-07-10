/* net-core FUN_010218cc @ 0x10218cc  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef long long (*code)(void);
void FUN_010218cc(void) {
    uint32_t v = *(volatile uint32_t*)0x21000530;
    code fn = *(code*)(v + 0xc);
    fn();
}

