/* net-core FUN_01021914 @ 0x1021914  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef long long (*code)(void);
void FUN_01021914(void) {
    uint32_t v = *(volatile uint32_t*)0x21000530;
    code fn = *(code*)(v + 0x2c);
    fn();
}

