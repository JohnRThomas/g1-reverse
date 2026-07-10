/* net-core FUN_01008d7c @ 0x1008d7c  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01008d00(uint32_t a, uint32_t b);
extern int32_t FUN_0101f624(void *a);
extern int32_t FUN_0101f668(uint32_t a);
extern int32_t FUN_0101f674(uint32_t a);
extern int32_t FUN_0102941c(void *a);

void FUN_01008d7c(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    const uint32_t iVar2 = 0x21000a30;
    uint32_t local[3];
    int32_t iVar1;

    local[0] = 0;
    local[1] = 0;
    iVar1 = FUN_0101f624(&local[0]);
    if (iVar1 != 0) {
        FUN_01008d00(3, 0xb3);
        goto step4;
    }

step4:
    local[2] = 1;
    iVar1 = FUN_0102941c(&local[2]);
    if (iVar1 != 0) {
        FUN_01008d00(3, 0xb7);
        goto step4;
    }

    iVar1 = FUN_0101f674((uint32_t) *(volatile uint8_t *)(iVar2 + 0x12));
    if (iVar1 != 0) {
        FUN_01008d00(3, 0xba);
        goto step4;
    }

    iVar1 = FUN_0101f668((uint32_t) *(volatile uint8_t *)(iVar2 + 0x11));
    if (iVar1 != 0) {
        FUN_01008d00(3, 0xbb);
        goto step4;
    }
}

