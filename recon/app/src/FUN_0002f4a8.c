/* Reconstructed FUN_0002f4a8 @ 0x2f4a8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(void);
extern int FUN_000167a8(void);
extern void FUN_00019c70(void);
extern int FUN_0008638c(void);
extern void FUN_00086c04(void);
extern void FUN_00086c78(void);

#define PUVAR3 0x20018daaUL
#define DBG() do { if (*flag == 0) DEBUG_PRINT(); else FUN_00019c70(); } while (0)

typedef int (*fn4)(int,int,int,int);

void FUN_0002f4a8(unsigned param_1, int param_2, int param_3, int param_4)
{
    volatile int *piVar1 = (volatile int*)0x2000230c;
    volatile int *flag = (volatile int*)0x20007554;
    int i5;

    if (2 < *piVar1) { DBG(); }

    if (((param_1 - 5) & 0xff) < 0xfa || param_1 == 0) {
        if (0 < *piVar1) { DBG(); }
        return;
    }

    i5 = FUN_0008638c();
    if (i5 == 0) {
        if (0 < *piVar1) { DBG(); }
        return;
    }

    FUN_00086c78();

    { int b = FUN_000167a8(); int fn = *(volatile int*)(b + 0x1030); FUN_000167a8();
      i5 = ((fn4)(intptr_t)fn)(0, 0x400000, PUVAR3, 0x1000); }
    if (i5 != 0) {
        if (0 < *piVar1) { DBG(); }
        return;
    }

    { int b = FUN_000167a8(); int fn = *(volatile int*)(b + 0x1038); FUN_000167a8();
      i5 = ((fn4)(intptr_t)fn)(0, 0x400000, 0x1000, 0); }
    if (i5 != 0) {
        if (2 < *piVar1) { DBG(); }
        return;
    }

    *(volatile uint8_t*)(PUVAR3 + 1) = 0xaa;
    *(volatile uint8_t*)(PUVAR3 + 0) = 0x5a;
    *(volatile uint8_t*)(PUVAR3 + 2) = 0xa5;
    *(volatile uint8_t*)(PUVAR3 + 3) = 0x5a;
    *(volatile uint8_t*)(PUVAR3 + 4) = 0;
    *(volatile uint8_t*)(PUVAR3 + 5) = 0;
    *(volatile uint8_t*)(PUVAR3 + 6) = 0;
    *(volatile uint8_t*)(PUVAR3 + 7) = 0;
    {
        int lvl = *piVar1;
        if (param_1 < 5) {
            unsigned iVar6 = param_1 - 1;
            uintptr_t base = PUVAR3 + iVar6 * 0x14;
            *(volatile uint8_t*)(base + 8) = 0;
            *(volatile uint8_t*)(base + 9) = 0;
            *(volatile uint8_t*)(base + 0xa) = 0;
            *(volatile uint8_t*)(base + 0xb) = 0;
            *(volatile uint8_t*)(base + 0x14) = 0;
            *(volatile uint8_t*)(base + 0x15) = 0;
            *(volatile uint8_t*)(base + 0x16) = 0;
            *(volatile uint8_t*)(base + 0x17) = 0;
            if (2 < lvl) { DBG(); }
        } else {
            FUN_00086c04();
            if (2 < lvl) { DBG(); }
        }
    }

    { int b = FUN_000167a8(); int fn = *(volatile int*)(b + 0x1034); FUN_000167a8();
      i5 = ((fn4)(intptr_t)fn)(0, 0x400000, PUVAR3, 0x1000); }
    if (i5 == 0) {
        if (2 < *piVar1) { DBG(); }
    } else {
        if (0 < *piVar1) { DBG(); }
    }
    return;
}

