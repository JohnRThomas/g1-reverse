/* net-core FUN_010218d8 @ 0x10218d8  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef long long (*code)(void);
void FUN_010218d8(void) {
    uint32_t v = *(volatile uint32_t*)0x21000530;
    code fn = *(code*)(v + 0x10);
    fn();
}

