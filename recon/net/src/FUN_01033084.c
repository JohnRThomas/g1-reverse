/* net-core FUN_01033084 @ 0x1033084  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* ESB timeslot/notification release @ 0x01033084 (Ghidra-gap, extent 0x20).
 * Takes the 0x21000530 vtable slot 0x10 hook, then slot 0xc with the
 * (0x0103cafc, 0x2100065c) descriptor pair, and clears TIMER2 SHORTS bits
 * 0x40004.  Called by FUN_010330b0.
 */
extern void FUN_010218d8(void);
extern void FUN_010218cc(unsigned int, unsigned int);

void FUN_01033084(void)
{
    volatile unsigned int *reg;
    FUN_010218d8();
    FUN_010218cc(0x0103cafcu, 0x2100065cu);
    reg = *(volatile unsigned int *volatile *)0x21000698u;
    reg[0x200u / 4u] = reg[0x200u / 4u] & ~0x40004u;
}
