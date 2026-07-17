/* Reconstructed FUN_000518a8 @ 0x518a8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0004e048(unsigned, void **);
extern unsigned FUN_0005169c(unsigned);
extern void FUN_0007e2ec(uint32_t, uint32_t);
extern void FUN_0007e2fa();
extern void FUN_0007ef7e(void);
extern void FUN_0008096a(uint32_t, uint32_t, const void *);
extern int FUN_00080970(void *, void *);
extern unsigned FUN_000809f6(unsigned);
extern unsigned FUN_00080a46(int);
extern int FUN_00080a82(void *);
extern int FUN_00086be4(void *, int);
extern void FUN_00086c78(void *, int, unsigned);

#define P1(k) (*(volatile int*)((char*)param_1 + (k)))
#define P2u(k) (*(volatile uint32_t*)((char*)param_2 + (k)))

unsigned FUN_000518a8(int *param_1, unsigned *param_2)
{
    volatile uint32_t *puVar1 = (volatile uint32_t*)0x2000ab7c;
    int iVar2;
    unsigned uVar4;
    int *piVar5;
    void *storage;
    uint8_t authorization[8];
    struct diagnostic_record {
        uint32_t severity;
        uint32_t message;
        uint32_t argument;
        uint32_t status;
    } diagnostic;

    FUN_00086c78(param_2, 0, 0x18);
    if (P1(4) == -1) return 0x14;
    if (P1(4) != 0) {
        uVar4 = puVar1[2];
        P2u(0xc) = puVar1[0];
        P2u(0) = uVar4;
        P2u(4) = 0;
        if (P1(4) == (int)puVar1[1]) {
            if (uVar4 < (unsigned)(P1(4) + P1(0x10))) return 0x1f;
            P2u(8) = P1(0x10);
            *(volatile uint8_t*)((char*)param_2 + 0x10) = 1;
        }
        return 0;
    }
    if ((unsigned)P1(0x10) < 0x20) return 0x16;
    if (P1(8) == -1) return 0x15;
    P2u(0) = P1(8);
    P2u(4) = 0;
    piVar5 = (int*)(intptr_t)P1(0xc);
    if (*(volatile int*)piVar5 != (int)0x96f3b83d) return 0x17;
    uVar4 = P1(0x18);
    if (0x20 < uVar4) return 0x18;
    if (uVar4 != 0 && *puVar1 != 0xffffffff && uVar4 == (unsigned)*(volatile uint8_t*)0x2000ab88) {
        iVar2 = FUN_00086be4((uint8_t *)puVar1 + 0xd, P1(0x14));
        if (iVar2 == 0) return 0;
    }
    iVar2 = P1(0);
    if (iVar2 == -1) iVar2 = 0;
    uVar4 = FUN_00080a46(iVar2);
    if (3 < uVar4) {
        FUN_0007e2fa(0x00099cbd, 0x000f25c5, 0x000f2561, 0x71);
        FUN_0007e2fa(0x000f25e2);
        FUN_0007e2ec(0x000f2561, 0x71);
    }
    uVar4 ^= 1;
    iVar2 = FUN_000809f6(uVar4);
    if (iVar2 != 0) {
        P2u(0xc) = 0xffffffff;
        return 9;
    }
    uVar4 = FUN_0005169c(uVar4);
    P2u(0xc) = uVar4;
    if ((int)uVar4 < 0) return 9;
    iVar2 = FUN_0004e048(uVar4 & 0xff, &storage);
    if (iVar2 != 0) {
        diagnostic.severity = 4;
        diagnostic.message = 0x000f25fb;
        diagnostic.argument = P2u(0xc);
        diagnostic.status = (uint32_t)iVar2;
        FUN_0008096a(0x00088208, 0x2040, &diagnostic);
        return 10;
    }
    if (*(volatile uint32_t *)((uint8_t *)storage + 8) < (unsigned)P1(8)) {
        FUN_0007ef7e();
        diagnostic.severity = 4;
        diagnostic.message = 0x000f26e7;
        diagnostic.argument = P1(8);
        diagnostic.status = *(volatile uint32_t *)((uint8_t *)storage + 8);
        FUN_0008096a(0x00088208, 0x2040, &diagnostic);
        return 0x1e;
    }
    FUN_0007ef7e();
    if ((int8_t)P1(0x1c) != 0) {
        iVar2 = FUN_00080a82(authorization);
        if (iVar2 != 0) return 0x1a;
        iVar2 = FUN_00080970(authorization, piVar5 + 5);
        if (-1 < iVar2) return 0x1b;
    }
    P2u(8) = P1(0x10);
    *(volatile uint8_t*)((char*)param_2 + 0x10) = 1;
    return 0;
}
