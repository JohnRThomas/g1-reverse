/* net-core FUN_010218b4 @ 0x10218b4  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef long long (*code)(void);
void FUN_010218b4(void) {
    uint32_t v = *(volatile uint32_t*)0x21000530;
    code fn = *(code*)(v + 0);
    fn();
}

