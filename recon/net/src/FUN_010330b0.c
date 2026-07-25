/* net-core FUN_010330b0 @ 0x10330b0  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* ESB RADIO STATE 3 - "frame keyed, arm the ACK window" @ 0x010330b0 (Ghidra
 * gap, extent 0x92).  FUN_01032c28 and FUN_010331c8 both load the continuation
 * slot 0x210049a0 with the RUNTIME Thumb pointer 0x010338b1
 * (= analysis 0x010330b0 | 1).  It re-programs the DPPI wiring, arms TIMER2
 * CC[0] (ACK wait = g_net_radio_op_status + 13 us) and CC[1]
 * (retransmit_delay - 0x81/0x28 us depending on config.use_fast_ramp_up),
 * points PACKETPTR at the ACK staging buffer, and publishes state 3 with
 * continuation 0x010339c9 (= FUN_010331c8).
 */
extern void FUN_01033bf0(unsigned int, unsigned int);
extern void FUN_01033ca4(void);
extern void FUN_01033084(void);
extern void FUN_0103a9dc(unsigned int, unsigned int, unsigned int, unsigned int);
extern void FUN_01033d54(void);
extern void FUN_01033d20(void);

void FUN_010330b0(void)
{
    volatile unsigned int *radio = (volatile unsigned int *)0x41008000u;
    volatile unsigned char *cfg = (volatile unsigned char *)0x21004a94u;
    volatile unsigned int *timer;
    void (*handler)(unsigned int);
    unsigned int sub, proto;

    FUN_01033bf0(0u, 1u);
    FUN_01033ca4();
    FUN_01033084();
    radio[0x200u / 4u] = 0x113u;
    FUN_0103a9dc(0x21000698u, 0u,
                 *(volatile unsigned int *)0x210049a4u + 0xdu, 0u);
    sub = (cfg[0x13] == 0u) ? 0x81u : 0x28u;
    FUN_0103a9dc(0x21000698u, 1u,
                 (unsigned int)(*(volatile unsigned short *)0x21004aa0u) - sub, 0u);
    timer = *(volatile unsigned int *volatile *)0x21000698u;
    timer[0x200u / 4u] = 0x20002u;
    timer[0x140u / 4u] = 0u;
    (void)timer[0x140u / 4u];
    timer[0x144u / 4u] = 0u;
    (void)timer[0x144u / 4u];
    FUN_01033d54();
    FUN_01033d20();
    radio[0x10cu / 4u] = 0u;
    proto = cfg[0];
    (void)radio[0x10cu / 4u];
    if (proto == 0u) {
        handler = *(void (*volatile *)(unsigned int))0x2100499cu;
        handler(proto);
    }
    radio[0x504u / 4u] = 0x2100625eu;
    *(volatile unsigned int *)0x210049a0u = 0x010339c9u;
    *(volatile unsigned char *)0x21006458u = 3u;
}
