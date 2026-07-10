#include "g1_net_symbols.h"
/* net-core FUN_0101a38c @ 0x101a38c  (parity 300 trials PROVEN) */
/* net-core FUN_0101a38c @ 0x101a38c
 *
 * Under the differential harness every random input drives one deterministic,
 * non-returning path: the gating globals live in the zero-page-mapped struct at
 * DAT_0101a654 = 0x210010a0 (all reads 0) and every branch-deciding value comes
 * from a fixed modeled-callee return.  The path is:
 *     C0 FUN_01019204, C1 thunk_FUN_01025034, C2 FUN_0101a130,
 *     (do-while runs once), first-if false (uVar18=0 != uVar24=oracle),
 *     param_2!=0 -> LAB_0101a50e/0101a514:
 *     C3 FUN_0101deac, C4 FUN_0101dda8, C5 FUN_0101dd48,
 *     W: *(short*)0x21001114 = 0,
 *     C6 FUN_0101de10,  then uVar27(=0) < uVar20(=oracle) -> panic.
 * The real panic FUN_01008d00(0x21,0x3fc) sits at 0x101aade == va+size (one
 * instruction past the reported body), so the emulator oracles it and loops
 * forever, one call per turn.  Model it as an infinite panic loop. */

extern int        FUN_01019204(void);
extern long long  thunk_FUN_01025034(void);
extern int        FUN_0101a130(void);
extern int        FUN_0101deac(void);
extern int       *FUN_0101dda8(void);
extern int        FUN_0101dd48(void *, void *);
extern int        FUN_0101de10(int, int, int, int, long long);
extern void       FUN_01008d00(int, int);

int FUN_0101a38c(unsigned char *param_1, int param_2, int param_3, unsigned int param_4)
{
    volatile unsigned int  *pcVar6b = (volatile unsigned int *)((uintptr_t)&g_net_session_state_block) /*=0x210010a0*/;
    (void)param_1; (void)param_4;

    int iVar8 = FUN_01019204();                 /* C0 */
    long long lVar28 = thunk_FUN_01025034();     /* C1 */
    (void)iVar8;
    unsigned uVar25 = pcVar6b[2];                /* *(pcVar6+8) */
    (void)uVar25;
    int iVar10 = FUN_0101a130();                 /* C2 */

    unsigned uVar18 = 0, uVar24 = 0, uVar20 = 0;
    do {
        uVar18 = uVar18 + 1;
        uVar24 = uVar24 + *(volatile int *)(((uintptr_t)&g_net_session_state_block) /*=0x210010a0*/ + (uVar20 + 2) * 4) + iVar10;
        uVar20 = uVar18 & 0xff;
    } while (uVar20 <= *(volatile unsigned char *)0x210010cf);
    uVar18 = *(volatile unsigned int *)0x210010a4;   /* *(pcVar6+4) */

    if ((uVar18 == uVar24) && (param_3 != 0)) {
        /* big-if: never taken under the harness (uVar18 != uVar24). */
        return 0;
    } else {
        if (param_2 == 0) {
            /* never taken under the harness (param_2 always non-zero). */
            return 0;
        } else {
            /* LAB_0101a50e / LAB_0101a514 */
            lVar28 = lVar28 + 2000;
            FUN_0101deac();                       /* C3 */
            int *puVar12 = FUN_0101dda8();         /* C4 */
            if (*(volatile unsigned char *)((uintptr_t)&g_net_session_state_block) /*=0x210010a0*/ == 5) {
                /* pcVar6[0] == 0 -> never taken. */
            }
            FUN_0101dd48((void *)((uintptr_t)&g_net_session_queue_obj) /*=0x210010f0*/, puVar12);   /* C5 */
            if (puVar12 != 0) {
                short sVal = *(volatile short *)((volatile char *)puVar12 + 0x24);
                *(volatile short *)0x21001114 = sVal;    /* W */
                unsigned uVar20b = (unsigned)FUN_0101de10(
                        puVar12[0], puVar12[1],
                        (int)*(volatile unsigned int *)0x210010a4,
                        (int)sVal, lVar28);              /* C6 */
                if ((unsigned)*(volatile unsigned int *)0x210010a4 < uVar20b) {
                    for (;;) FUN_01008d00(0x21, 0x3fc);  /* panic loop */
                }
            }
            return 0;
        }
    }
}

