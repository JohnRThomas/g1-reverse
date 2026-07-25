/* net-core FUN_01032804 @ 0x1032804  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* ESB RADIO STATE 4 - "ACK transmitted, arm RX" @ 0x01032804 (Ghidra gap,
 * extent 0x36).  Entered through the continuation slot
 * g_net_radio_irq_continuation_ptr (0x210049a0), which FUN_01032e54 loads with
 * the RUNTIME Thumb pointer 0x01033005 (= analysis 0x01032804 | 1).  It sets
 * RADIO SHORTS 0x117, notifies the ESB event handler with the configured
 * payload length, points PACKETPTR at the RX staging buffer 0x2100625e, and
 * publishes state 4 with continuation 0x01033655 (= FUN_01032e54).
 */
extern void FUN_010218d8(void);
extern void FUN_010218cc(unsigned int, unsigned int);

void FUN_01032804(void)
{
    volatile unsigned int *radio = (volatile unsigned int *)0x41008000u;
    volatile unsigned char *cfg = (volatile unsigned char *)0x21004a94u;
    void (*handler)(unsigned int);

    FUN_010218d8();
    FUN_010218cc(0x0103cafcu, 0x2100065cu);
    radio[0x200u / 4u] = 0x117u;
    handler = *(void (*volatile *)(unsigned int))0x2100499cu;
    handler(cfg[0x11]);
    radio[0x504u / 4u] = 0x2100625eu;
    *(volatile unsigned int *)0x210049a0u = 0x01033655u;
    *(volatile unsigned char *)0x21006458u = 4u;
}
