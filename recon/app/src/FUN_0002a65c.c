/* Reconstructed FUN_0002a65c @ 0x2a65c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);
extern void FUN_00023a54(void);
extern void FUN_0002ace0(void);
extern int FUN_00032ee4(void);
extern void FUN_00032fe8(void);
extern void FUN_0003304c(void);
extern void FUN_00047ad0(void);
extern void FUN_00049638(void);
extern void FUN_0007cb66(void);
extern void FUN_000864c2(void);

void FUN_0002a65c(char *param_1)
{
    volatile int *dbg = (volatile int*)0x2000230c;
    volatile int *flag = (volatile int*)0x20007554;
    int iVar1;

    if (2 < *dbg) {
        if (*flag == 0) DEBUG_PRINT();
        else FUN_00019c70();
    }
    FUN_000864c2();
    FUN_00023a54();
    FUN_0002ace0();
    iVar1 = FUN_00032ee4();
    if (iVar1 == 0) {
        FUN_0007cb66();
        FUN_0007cb66();
    } else {
        FUN_0007cb66();
        FUN_00032fe8();
        FUN_0003304c();
    }
    FUN_0007cb66();
    if (*(volatile uint8_t*)param_1 == 1) {
        FUN_0007cb66();
        FUN_0007cb66();
        FUN_00047ad0();
        FUN_00049638();
    } else if (*(volatile uint8_t*)param_1 == 2) {
        FUN_0007cb66();
        FUN_0007cb66();
        FUN_0007cb66();
        FUN_00049638();
    }
    FUN_00032ee4();
    FUN_0007cb66();
    FUN_0007cb66();
}

