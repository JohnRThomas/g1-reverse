/* net-core FUN_0102fbd0 @ 0x102fbd0  (parity 300 trials PROVEN) */
#include <stdint.h>

extern int32_t FUN_0102e284(uint32_t a, uint32_t b, void *c, uint32_t d);
extern void FUN_01030014(int32_t a, uint32_t b);
extern int32_t FUN_0103a44c(uint32_t a);

int32_t FUN_0102fbd0(uint32_t param_1)
{
    int32_t iVar1;

    if ((param_1 < 6) && (((int32_t)((0x2aU >> (param_1 & 0xff)) << 0x1f)) < 0)) {
        iVar1 = FUN_0103a44c(0x210009fc);
        if (iVar1 != 0) {
            FUN_01030014(iVar1 + 0xc, 1);
            *(volatile int8_t *)(iVar1 + 0x18) = (int8_t)param_1;
        }
    } else {
        struct {
            uint32_t type;
            uint32_t format;
            uint32_t argument;
        } record = {3, 0x0103ddb9, param_1};
        FUN_0102e284(0x0103c024, 0x1840, &record, 0);
        iVar1 = 0;
    }
    return iVar1;
}
