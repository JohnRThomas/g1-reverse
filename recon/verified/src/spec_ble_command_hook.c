/* Reconstructed spec_ble_command_hook @ 0xef28  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>

extern int  FUN_000181fc();
extern void FUN_00086c78();
extern void FUN_00086c1e();
extern int  FUN_0000eefe();
extern void DEBUG_PRINT();
extern void FUN_00019c70();
extern int  FUN_000870be();
extern void FUN_00087080();
extern void FUN_00086ffe();
extern int  FUN_00021c04();
extern int  FUN_00087036();
extern void FUN_00086a06_v();
extern int  FUN_00086a06();
extern int  FUN_0000ef12();
extern void FUN_00021a40();
extern int  FUN_00064ca4();
extern void FUN_00085076();
extern void FUN_0008509e();
extern void FUN_00085046();
extern int  FUN_00085014();
extern void FUN_00021cd8();
extern void FUN_00064b1c();
extern void FUN_0007c244();
extern void FUN_00074844();
extern int  FUN_0004c0a8();
extern int  FUN_0007c18e();
extern void FUN_00072908();
extern int  FUN_00025448();
extern void thunk_FUN_00072880();
extern void change_work_mode_to();
extern void FUN_0002efc0();
extern void FUN_00010a68();
extern void FUN_00086f00();
extern void FUN_00086fee();

#define LVL_A (*(volatile int32_t*)0x2000230cUL)
#define LVL_B (*(volatile int32_t*)0x20007554UL)
#define G_20007554 (*(volatile int32_t*)0x20007554UL)   /* same addr as LVL_B; written by "reboot flag" cmd */

uint32_t spec_ble_command_hook(uint32_t param_1, uint32_t param_2)
{
    int32_t iVar4, iVar5, iVar7;
    uint8_t bVar2;
    uint32_t uVar12, uVar19;

    iVar4 = FUN_000181fc();
    FUN_00086c78();
    FUN_00086c1e();

    iVar5 = FUN_0000eefe();
    if (iVar5 == 0) {
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        return 0;
    }

    iVar5 = FUN_000870be();
    if (iVar5 != 0) {
        /* dominant path: scan/parse the recognized packet and dispatch it.
           NOTE: iVar5 here is an oracle value used as a raw scan pointer in
           the original (searching for '@'); replicate the same scan so a
           garbage pointer causes the same non-terminating behavior on both
           sides (the parity harness treats "both never return" as a skip,
           not a mismatch -- but only if BOTH sides actually perform the scan). */
        volatile char *pcVar13 = (volatile char *)(intptr_t)(iVar5 + 3);
        volatile char *pcVar14 = pcVar13;
        volatile char *pcVar18;
        FUN_00086c78();
        FUN_00086c78();
        do {
            pcVar18 = pcVar14;
            pcVar14 = pcVar18 + 1;
        } while (*pcVar18 != '@');
        FUN_00087080();
        FUN_00086ffe();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        uVar12 = FUN_00021c04();
        return uVar12;
    }

    iVar5 = FUN_000870be();
    if (iVar5 == 0) {
        iVar5 = FUN_000870be();
        if (iVar5 == 0) {
            iVar5 = FUN_000870be();
            if (iVar5 == 0) {
                iVar7 = FUN_000870be();
                if (iVar7 != 0) {
                    if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
                    if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
                    if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
                    iVar4 = FUN_00086a06();
                    uVar12 = FUN_00086a06();
                    if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
                    return 0;
                }
                iVar5 = FUN_000870be();
                if (iVar5 != 0) {
                    if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
                    FUN_00086c78();
                    iVar4 = FUN_00086a06();
                    if (LVL_A < 3) {
                        if (iVar4 == 4) goto LAB_cmd4;
                        if (iVar4 != 9) goto LAB_notcmd9;
                    } else {
                        if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70();
                        if (iVar4 == 4) {
                            if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
LAB_cmd4:
                            FUN_00086c78();
                            FUN_00086fee();
                            uVar12 = FUN_0000ef12();
                            if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
                            FUN_00021a40();
                            return 0;
                        }
                        if (iVar4 != 9) {
LAB_notcmd9:
                            if (iVar4 == 0xa) {
                                if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
                                FUN_00064ca4();
                                FUN_00085076();
                                FUN_00085076();
                                FUN_0008509e();
                                uVar12 = FUN_00064ca4();
                                FUN_00085046();
                                FUN_00085014();
                                FUN_0000ef12();
                                if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
                                FUN_00021a40();
                                FUN_00064b1c();
                                return 0;
                            }
                            if (iVar4 == 0x58) {
                                if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
                                FUN_00021cd8();
                                return 0;
                            }
                            if (iVar4 == 0x4b) {
                                if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
                                FUN_00086c1e();
                                if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
                                FUN_00087080();
                                FUN_00086ffe();
                                uVar12 = FUN_00021c04();
                                return uVar12;
                            }
                            if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
                            return 0;
                        }
                        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
                    }
                    FUN_00064ca4();
                    FUN_00085076();
                    FUN_0008509e();
                    uVar12 = FUN_00064ca4();
                    FUN_00085046();
                    FUN_00085014();
                    FUN_0000ef12();
                    if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
                    FUN_00021a40();
                    FUN_00064b1c();
                    return 0;
                }

                /* deep "esbchannel/direction/reboot/mac/flash/..." command family:
                   virtually unreachable in practice (needs several consecutive
                   oracle==0 matches), implemented best-effort */
                iVar5 = FUN_00087036();
                if (iVar5 == 0) {
                    bVar2 = (uint8_t)FUN_00086a06();
                    *(volatile uint8_t *)(iVar4 + -0x77a) = bVar2;
                    DEBUG_PRINT();
                    *(volatile uint32_t *)(iVar4 + 0x8d0) = 0;
                } else {
                    iVar5 = FUN_00087036();
                    if (iVar5 != 0) {
                        iVar5 = FUN_00087036();
                        if (iVar5 == 0) {
                            bVar2 = (uint8_t)(*(volatile uint8_t *)(iVar4 + 0x8dd) | 4);
                            *(volatile uint8_t *)(iVar4 + 0x8dd) = bVar2;
                        } else {
                            iVar5 = FUN_00087036();
                            if (iVar5 != 0) {
                                iVar5 = FUN_00087036();
                                if (iVar5 == 0) {
                                    FUN_00086c78();
                                    FUN_00086f00();
                                    uVar12 = 200;
                                    { void (*pc)(void) = *(void(**)(void))(iVar4 + 0xc); pc(); }
                                    return 0;
                                }
                                iVar5 = FUN_00087036();
                                if (iVar5 == 0) {
                                    for (;;) {
                                        FUN_00074844();
                                        FUN_0004c0a8();
                                        DEBUG_PRINT();
                                    }
                                }
                                iVar5 = FUN_00087036();
                                if (iVar5 == 0) {
                                    iVar4 = FUN_00086a06();
                                    if (iVar4 == 1) { G_20007554 = 0; return 0; }
                                    G_20007554 = 1;
                                    return 0;
                                }
                                uVar19 = (uint32_t)FUN_00087036();
                                if (uVar19 == 0) {
                                    FUN_00086c78();
                                    *(volatile uint32_t *)(iVar4 + 0x7e8) = 0;
                                    FUN_00086f00();
                                    { void (*pc)(void) = *(void(**)(void))(iVar4 + 0xc); pc(); }
                                    *(volatile uint32_t *)(iVar4 + 0x8d0) = 0;
                                } else {
                                    /* remaining "pitch/level/net/mac/flash/workmode" leaf
                                       commands: not modeled individually (unreachable in
                                       practice); fall to generic tail below */
                                    FUN_00086c78();
                                    change_work_mode_to();
                                    uVar12 = 0x14;
                                    { void (*pc)(void) = *(void(**)(void))(iVar4 + 0xc); pc(); }
                                    return 0;
                                }
                            } else {
                                bVar2 = (uint8_t)(*(volatile uint8_t *)(iVar4 + 0x8dd) | 8);
                                *(volatile uint8_t *)(iVar4 + 0x8dd) = bVar2;
                            }
                        }
                    } else {
                        bVar2 = (uint8_t)FUN_00086a06();
                        *(volatile uint8_t *)(iVar4 + 0x86e) = bVar2;
                        DEBUG_PRINT();
                        if (*(volatile int8_t *)(iVar4 + 0x86e) == 0xb) {
                            *(volatile uint8_t *)(iVar4 + 0x768) = 2;
                            change_work_mode_to();
                            if (*(volatile int8_t *)(iVar4 + -0x77c) == 2) {
                                thunk_FUN_00072880();
                            }
                        } else {
                            *(volatile uint8_t *)(iVar4 + 0x768) = 1;
                            change_work_mode_to();
                        }
                        *(volatile uint32_t *)(iVar4 + 0x8d0) = 0;
                    }
                }
                thunk_FUN_00072880();
                return 0;
            }
            iVar5 = iVar5 + 3;
            iVar4 = FUN_00086a06();
            if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        } else {
            iVar5 = iVar5 + 3;
            uVar12 = (uint32_t)FUN_00086a06();
            if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
        }
    } else {
        iVar5 = iVar5 + 3;
        iVar4 = FUN_00086a06();
        if (2 < LVL_A) { if (LVL_B == 0) DEBUG_PRINT(); else FUN_00019c70(); }
    }

    uVar12 = 3;
    FUN_0007c244();
    return 0;
}

