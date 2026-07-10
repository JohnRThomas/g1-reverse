/* Reconstructed load_usr_setting @ 0x22e78  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);
extern int FUN_000225b4(int, void*, int);
extern void FUN_00022ddc(int);
extern int FUN_00032ee4(void);
extern void FUN_00032ef0(int);
extern void FUN_0007c28e(int, int);
extern void FUN_00086c78(void*, int, int);

int load_usr_setting(int param_1)
{
    volatile int *dbg = (volatile int*)0x2000230c;
    volatile int *a4 = (volatile int*)0x20007554;
    volatile uint8_t buf[0x20];
    int iVar1;
    int local_34;
    uint8_t local_24, local_21;

    FUN_00086c78((void*)buf, 0, 0x20);
    iVar1 = FUN_000225b4(0x134000, (void*)buf, 0x20);
    if (iVar1 != 0) {
        if (1 < *dbg) { if (*a4 == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        return -1;
    }
    if (1 < *dbg) { if (*a4 == 0) DEBUG_PRINT(); else FUN_00019c70(); }

    *(volatile uint8_t*)(param_1 + 0xed5) = buf[1];
    *(volatile uint8_t*)(param_1 + 0xef4) = buf[2];
    local_34 = *(volatile int*)(buf + 4);
    if (local_34 == 0) local_34 = 400;
    *(volatile int*)(param_1 + 0xf6c) = local_34;
    *(volatile uint8_t*)(param_1 + 0xfea) = buf[0];
    *(volatile uint8_t*)(param_1 + 0xf98) = buf[8];
    *(volatile uint8_t*)(param_1 + 0xf60) = buf[3];
    *(volatile uint8_t*)(param_1 + 0x1070) = buf[9];
    *(volatile uint8_t*)(param_1 + 0x108d) = buf[0xa];
    *(volatile uint8_t*)(param_1 + 0xec0) = buf[0xb];
    *(volatile uint32_t*)(param_1 + 0x1069) = *(volatile uint32_t*)(buf + 0xc);
    *(volatile uint8_t*)(param_1 + 0x106f) = buf[0x12];
    *(volatile uint16_t*)(param_1 + 0x106d) = *(volatile uint16_t*)(buf + 0x10);
    *(volatile uint8_t*)(param_1 + 0xef5) = buf[0x13];
    local_24 = buf[0x14];
    if (1 < local_24) local_24 = 0;
    *(volatile uint8_t*)(param_1 + 0x108f) = local_24;
    *(volatile uint8_t*)(param_1 + 0x1090) = buf[0x15];
    *(volatile uint8_t*)(param_1 + 0x1091) = buf[0x16];
    *(volatile uint8_t*)(param_1 + 0xec1) = buf[0x18];
    *(volatile uint32_t*)(param_1 + 0xf68) = *(volatile uint32_t*)(buf + 0x1c);

    if ((uint8_t)(buf[0] & buf[3]) == 0xff) {
        FUN_00022ddc(param_1);
    }
    if (8 < *(volatile uint8_t*)(param_1 + 0xec0)) {
        *(volatile uint8_t*)(param_1 + 0xec0) = 3;
    }
    if ((uint32_t)(*(volatile uint8_t*)(param_1 + 0xec1) - 1) > 8) {
        *(volatile uint8_t*)(param_1 + 0xec1) = 3;
    }
    if (*(volatile int8_t*)(param_1 + 0xfea) == 11) {
        *(volatile uint8_t*)(param_1 + 0xfea) = 10;
        FUN_0007c28e(param_1, 0);
    }
    local_21 = buf[0x17];
    if (1 < local_21) local_21 = 0;
    FUN_00032ef0(local_21);
    iVar1 = FUN_00032ee4();
    if (iVar1 == 1) {
        *(volatile uint8_t*)(param_1 + 0xf98) = 0;
        *(volatile uint8_t*)(param_1 + 0xfea) = 0xb;
        *(volatile uint8_t*)(param_1 + 0xed5) = 0x15;
        *(volatile uint16_t*)(param_1 + 0xec0) = 0x303;
    } else {
        *(volatile uint8_t*)(param_1 + 0xfea) = 10;
    }
    if (*(volatile int*)(param_1 + 0xf68) == -1) {
        *(volatile uint32_t*)(param_1 + 0xf68) = 0;
    }
    return 0;
}

