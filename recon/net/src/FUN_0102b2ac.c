/* P4 iteration 26/27 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_210045e0[];
#define G1N_21004610 ((unsigned long)(g1_net_ram_blk_210045e0 + 0x30))
#else
#define G1N_21004610 0x21004610ul
#endif
/* net-core FUN_0102b2ac @ 0x102b2ac  (parity 300 trials PROVEN) */
#include <stdint.h>

extern uint32_t FUN_0103b530(uint32_t a);
extern void FUN_0103b62e(void *dst, uint32_t val, uint32_t len);

#ifdef G1_COHESIVE_BUILD
extern void FUN_0102b1c8(void);
extern unsigned int FUN_0102b15c(unsigned int, unsigned int, unsigned int);
#define G1_ESB_WORK_CALLBACK ((uint32_t)(uintptr_t)&FUN_0102b1c8) /*=0x0102b9c9*/
#define G1_ESB_RX_CALLBACK ((uint32_t)(uintptr_t)&FUN_0102b15c) /*=0x0102b95d*/
#else
#define G1_ESB_WORK_CALLBACK UINT32_C(0x0102b9c9)
#define G1_ESB_RX_CALLBACK UINT32_C(0x0102b95d)
#endif

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
    *(volatile uint32_t *)p1b = G1_ESB_WORK_CALLBACK;

    uint32_t uVar1;
    uint8_t uVar2;
    if (*(volatile int32_t *)(p1b - 0xb0) == 1) {
        uVar2 = 2;
        uVar1 = 0x0103d132;
    } else {
        uVar2 = 4;
        uVar1 = 0x0103d13e;
    }
    *(volatile uint32_t *)(p1b + 8) = uVar1;
    *(volatile uint8_t *)(p1b + 4) = uVar2;
    *(volatile uint32_t *)(p1b + 0xc) = G1_ESB_RX_CALLBACK;

    typedef void (*fn_t)(void *, uint32_t, uint32_t);
    fn_t f = (fn_t)(uintptr_t)(*(volatile uint32_t *)(p1b - 4));
    f((void *)(p1b + 4), 0x0103d13eu, uVar2);

    *(volatile uint32_t *)G1N_21004610 = (uint32_t)(uintptr_t)param_1;
}
