/* net-core FUN_01033cd0 @ 0x1033cd0  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* CPUNET ESB DPPI wiring: publish/subscribe for the ACK turnaround @ 0x01033cd0.
 * Ghidra-gap leaf; extent 0x3a.  Binds TIMER2 SUBSCRIBE (0x1c4) and RADIO
 * (0x080) to DPPI channel g_net_radio_trx_ppi_ch_e and 0x41014000+0x98 to
 * g_esb_ppi_ch_id_3, then enables the channel in DPPIC CHENSET.
 */
void FUN_01033cd0(void)
{
    volatile unsigned int *a = (volatile unsigned int *)0x41014000u;
    unsigned int chB, chC, v;

    a[0x118u / 4u] = 0u;
    (void)a[0x118u / 4u];
    chB = *(volatile unsigned char *)0x2100645eu;
    v = chB | 0x80000000u;
    *(volatile unsigned int *)(0x41019000u + 0x1c4u) = v;
    *(volatile unsigned int *)(0x41008000u + 0x80u) = v;
    chC = *(volatile unsigned char *)0x2100645du;
    a[0x98u / 4u] = chC | 0x80000000u;
    *(volatile unsigned int *)(0x4100f000u + 0x504u) = 1u << chB;
}
