#include "g1_net_symbols.h"
/* net-core FUN_0102b2ac @ 0x102b2ac  (parity 300 trials PROVEN) */
#include <stdint.h>

extern uint32_t FUN_0103b530(uint32_t a);
extern void FUN_0103b62e(void *dst, uint32_t val, uint32_t len);

void FUN_0102b2ac(uint32_t *param_1)
{
    uint8_t *p1b = (uint8_t *)param_1;

    uint32_t buf = FUN_0103b530(0x100);
    *(volatile uint32_t *)(p1b + 0x10) = buf;
    FUN_0103b62e((void *)(uintptr_t)buf, 0, 0x100);

    uint8_t *puVar3 = (uint8_t *)(uintptr_t)(*(volatile uint32_t *)(p1b + 0x10));
    *(volatile uint8_t *)puVar3 = 0xfb;
    *(volatile uint32_t *)(puVar3 + 0x11) = *(volatile uint32_t *)(p1b + 0x1a);
    *(volatile uint16_t *)(puVar3 + 0x15) = *(volatile uint16_t *)(p1b + 0x1e);
    *(volatile uint32_t *)p1b = ((uintptr_t)&rodata_102b9c9) /*=0x102b9c9*/;

    uint32_t uVar1;
    uint8_t uVar2;
    if (*(volatile int32_t *)(p1b - 0xb0) == 1) {
        uVar2 = 2;
        uVar1 = "or" /*=0x103d132*/;
    } else {
        uVar2 = 4;
        uVar1 = " data bus error" /*=0x103d13e*/;
    }
    *(volatile uint32_t *)(p1b + 8) = uVar1;
    *(volatile uint8_t *)(p1b + 4) = uVar2;
    *(volatile uint32_t *)(p1b + 0xc) = ((uintptr_t)&rodata_102b95d) /*=0x102b95d*/;

    typedef void (*fn_t)(void *);
    fn_t f = (fn_t)(uintptr_t)(*(volatile uint32_t *)(p1b - 4));
    f((void *)(p1b + 4));

    *(volatile uint32_t *)((uintptr_t)&g_net_fault_record_ptr) /*=0x21004610*/ = (uint32_t)(uintptr_t)param_1;
}

