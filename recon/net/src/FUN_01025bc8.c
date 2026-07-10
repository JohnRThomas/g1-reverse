/* net-core FUN_01025bc8 @ 0x1025bc8  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef long long (*code)(void);
void FUN_01025bc8(void) {
    uint32_t v = *(volatile uint32_t*)0x21000574;
    code fn = *(code*)(v + 8);
    fn();
}

