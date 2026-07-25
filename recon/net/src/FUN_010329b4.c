/* net-core FUN_010329b4 @ 0x10329b4  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* ESB RADIO "abort and restart RX" @ 0x010329b4 (Ghidra gap, extent 0x70).
 * Tail-target of FUN_01032e54 when the received frame fails CRC, is a
 * duplicate, or the RX FIFO is full.  It clears the timeslot wiring, notifies
 * the event handler, forces RADIO TASKS_DISABLE and spins on EVENTS_DISABLED,
 * then re-arms SHORTS 0x117 and the DPPI pair.
 */
extern void FUN_01033ca4(void);
extern void FUN_010218e4(void);
extern void FUN_010218b4(void);
extern void FUN_01033bf0(unsigned int, unsigned int);
extern void FUN_01033b18(unsigned int, unsigned int);
extern void FUN_01032988(void);

void FUN_010329b4(void)
{
    volatile unsigned int *radio = (volatile unsigned int *)0x41008000u;
    volatile unsigned char *cfg = (volatile unsigned char *)0x21004a94u;
    void (*handler)(unsigned int);

    (*(volatile unsigned int *volatile *)0x21000698u)[0x10u / 4u] = 1u;
    FUN_01033ca4();
    FUN_010218e4();
    FUN_010218b4();
    FUN_01033bf0(1u, 0u);
    radio[0x200u / 4u] = 0x113u;
    handler = *(void (*volatile *)(unsigned int))0x2100499cu;
    handler(cfg[0x11]);
    radio[0x504u / 4u] = 0x2100625eu;
    radio[0x110u / 4u] = 0u;
    (void)radio[0x110u / 4u];
    radio[0x10u / 4u] = 1u;
    while (radio[0x110u / 4u] == 0u) {
    }
    radio[0x110u / 4u] = 0u;
    (void)radio[0x110u / 4u];
    radio[0x200u / 4u] = 0x117u;
    FUN_01033b18(1u, 0u);
    FUN_01032988();
    *(volatile unsigned int *)(0x41014000u + 0x18u) = 1u;
}
