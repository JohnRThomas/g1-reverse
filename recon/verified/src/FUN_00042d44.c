/* Reconstructed FUN_00042d44 @ 0x42d44  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned undefined4;
typedef unsigned char byte;
typedef unsigned char undefined1;
extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_00040708(void);
extern void FUN_00040794(int a);
extern void FUN_000417f8(int a);
extern void FUN_000429f8(void);
extern int FUN_00042c8c(void *a, int b);
extern void FUN_000431b4(int a);
extern void FUN_000431c0(void);
extern void FUN_000432d0(void);
extern void FUN_00047ba8(void);
extern unsigned long long FUN_0007d382(void);
extern unsigned long long FUN_0007d3c2(int a, int b, unsigned c, unsigned d);
extern void thunk_FUN_00043308(void);

undefined4 FUN_00042d44(int param_1, undefined4 param_2, int param_3)
{
    byte bVar2;
    byte *pbVar3;
    int iVar4, iVar6;
    char *pcVar5;
    unsigned long long uVar7;
    unsigned char local_14[2], local_12, uStack_11;
    volatile int *verbose = (volatile int *)0x2000230c;
    volatile int *dbg = (volatile int *)0x20007554;

    (void)local_12; (void)uStack_11; (void)param_2;
    local_14[0] = 0;
    iVar4 = FUN_000167a8();
    FUN_000431b4(param_1 + 0x24);
    FUN_000432d0();
    if ((param_3 == 2) || (0x17 < *(volatile byte *)(iVar4 + 0xf1))) {
        iVar4 = FUN_000167a8();
        **(volatile undefined1 **)(iVar4 + 0x1014) = 0;
        iVar4 = FUN_000167a8();
        iVar6 = *(volatile int *)(iVar4 + 0x1014);
        iVar4 = FUN_000167a8();
        *(volatile undefined1 *)(iVar4 + 0xed5) = *(volatile undefined1 *)(iVar6 + 0x20);
        FUN_000431c0();
    } else {
        if ((param_3 == 1) && (pcVar5 = (char *)FUN_000167a8(), *pcVar5 == '\x01')) {
            FUN_00047ba8();
        }
        pcVar5 = (char *)FUN_000167a8();
        if ((*pcVar5 == '\x01') &&
            (iVar4 = FUN_000167a8(), pbVar3 = (byte *)0x20004bf0,
             *(volatile char *)(*(volatile int *)(iVar4 + 0x1014) + 2) != '\0')) {
            uVar7 = FUN_0007d382();
            uVar7 = FUN_0007d3c2((int)uVar7, (int)(uVar7 >> 0x20), *(volatile unsigned *)(pbVar3 + 8), *(volatile unsigned *)(pbVar3 + 0xc));
            if ((int)(unsigned)((unsigned)uVar7 < 0x3e9) <= (int)(uVar7 >> 0x20)) {
                *pbVar3 = *pbVar3 + 1;
                uVar7 = FUN_0007d382();
                *(volatile unsigned long long *)(pbVar3 + 8) = uVar7;
                if (0x13 < *pbVar3) {
                    if (1 < *verbose) {
                        if (*dbg == 0) DEBUG_PRINT(0, 0);
                        else FUN_00019c70(0, 0);
                    }
                    *pbVar3 = 0x14;
                    iVar4 = FUN_000167a8();
                    *(volatile undefined1 *)(*(volatile int *)(iVar4 + 0x1014) + 2) = 0xb;
                    iVar4 = FUN_000167a8();
                    local_14[0] = *(volatile byte *)(*(volatile int *)(iVar4 + 0x1014) + 2);
                    iVar4 = FUN_00042c8c(local_14, 3);
                    if (iVar4 != 0) return 0;
                    iVar4 = FUN_000167a8();
                    **(volatile undefined1 **)(iVar4 + 0x1014) = 0;
                    iVar4 = FUN_000167a8();
                    *(volatile undefined1 *)(*(volatile int *)(iVar4 + 0x1014) + 1) = 0;
                    return 0;
                }
            }
        }
        iVar4 = FUN_000167a8();
        if (((uint)*(volatile byte *)(*(volatile int *)(iVar4 + 0x1014) + 2) == (int)*(volatile char *)0x200034f5) &&
            (iVar4 = FUN_000167a8(), *(volatile char *)(*(volatile int *)(iVar4 + 0x1014) + 3) == *(volatile char *)0x2001cdce)) {
            FUN_00040794(param_3);
            FUN_000417f8(param_3);
            return 0;
        }
        pcVar5 = (char *)FUN_000167a8();
        if (*pcVar5 == '\x01') {
            FUN_000429f8();
            iVar4 = FUN_000167a8();
            *(volatile char *)0x2001cdce = *(volatile char *)(*(volatile int *)(iVar4 + 0x1014) + 3);
            iVar4 = FUN_000167a8();
            local_14[0] = *(volatile byte *)(*(volatile int *)(iVar4 + 0x1014) + 2);
            local_14[1] = *(volatile char *)0x2001cdce;
            iVar4 = FUN_000167a8();
            local_12 = *(volatile undefined1 *)(*(volatile int *)(iVar4 + 0x1014) + 0xc);
            iVar4 = FUN_000167a8();
            if ((*(volatile char *)(*(volatile int *)(iVar4 + 0x1014) + 2) != '\n') &&
                (iVar4 = FUN_000167a8(), *(volatile char *)(*(volatile int *)(iVar4 + 0x1014) + 2) != '\v')) {
                if (2 < *verbose) {
                    if (*dbg == 0) {
                        iVar4 = FUN_000167a8();
                        bVar2 = *(volatile byte *)(*(volatile int *)(iVar4 + 0x1014) + 2);
                        iVar4 = FUN_000167a8();
                        DEBUG_PRINT(0, 0, (uint)bVar2, (uint)*(volatile byte *)(*(volatile int *)(iVar4 + 0x1014) + 3));
                    } else {
                        iVar4 = FUN_000167a8();
                        (void)*(volatile undefined1 *)(*(volatile int *)(iVar4 + 0x1014) + 2);
                        iVar4 = FUN_000167a8();
                        FUN_00019c70(0);
                    }
                }
                FUN_00042c8c(local_14, 3);
            }
            thunk_FUN_00043308();
            FUN_00040708();
            uVar7 = FUN_0007d382();
            iVar4 = FUN_000167a8();
            *(volatile unsigned long long *)(*(volatile int *)(iVar4 + 0x1014) + 4) = uVar7;
            iVar4 = FUN_000167a8();
            iVar6 = *(volatile int *)(iVar4 + 0x1014);
            iVar4 = FUN_000167a8();
            *(volatile undefined1 *)(iVar4 + 0xcd) = *(volatile undefined1 *)(iVar6 + 3);
        }
    }
    return 0;
}

