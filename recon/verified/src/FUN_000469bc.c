/* Reconstructed FUN_000469bc @ 0x469bc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(void);
extern int FUN_000167a8(void);
extern void FUN_00019c70(void);
extern int FUN_00023ee0(void);
extern void FUN_000431c0(void);
extern void FUN_00043484(void);
extern void FUN_00043e90(void);
extern int FUN_0007d3ee(void);
extern int FUN_0007d446(void);
extern int FUN_0007d4b2(void);

unsigned FUN_000469bc(void)
{
    int iVar1 = FUN_000167a8();
    if (*(volatile uint8_t*)(iVar1 + 0xf0) < 2) {
        if (*(volatile uint8_t*)0x2001cf91 != *(volatile uint8_t*)(iVar1 + 0xf0)) {
            FUN_000431c0();
            *(volatile uint8_t*)0x2001cf91 = *(volatile uint8_t*)(iVar1 + 0xf0);
        }
        if (*(volatile int8_t*)(iVar1 + 0xf0) == 1) {
            FUN_0007d3ee(); FUN_0007d446(); FUN_00043484();
            FUN_00023ee0(); FUN_0007d4b2();
            FUN_0007d3ee(); FUN_0007d446(); FUN_0007d3ee(); FUN_0007d446();
            FUN_00043e90(); FUN_00023ee0();
        } else {
            FUN_0007d3ee(); FUN_0007d446(); FUN_00043484();
            FUN_00023ee0(); FUN_0007d4b2();
            FUN_0007d3ee(); FUN_0007d446(); FUN_0007d3ee(); FUN_0007d446();
            FUN_00043e90(); FUN_00023ee0();
        }
        FUN_0007d4b2();
        FUN_0007d3ee(); FUN_0007d446(); FUN_0007d3ee(); FUN_0007d446();
        FUN_00043e90();
        return 0;
    } else {
        if (0 < *(volatile int*)0x2000230c) {
            if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT();
            else FUN_00019c70();
        }
        return 0xffffffff;
    }
}

