/* net-core FUN_01033d54 @ 0x1033d54  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* CPUNET ESB DPPI wiring: RADIO<->TIMER2 retransmission pair @ 0x01033d54.
 * Ghidra-gap leaf; extent 0x38.  Binds RADIO PUBLISH (0x184) and TIMER2
 * SUBSCRIBE (0x1c0/0x090) to g_esb_ppi_ch_id_6 / g_esb_ppi_ch_id_5 and enables
 * both DPPI channels.
 */
void FUN_01033d54(void)
{
    unsigned int chD = *(volatile unsigned char *)0x21006460u;
    unsigned int chE;
    unsigned int vD = chD | 0x80000000u;
    unsigned int vE;

    *(volatile unsigned int *)(0x41008000u + 0x184u) = vD;
    chE = *(volatile unsigned char *)0x2100645fu;
    vE = chE | 0x80000000u;
    *(volatile unsigned int *)(0x41019000u + 0x1c0u) = vE;
    *(volatile unsigned int *)(0x41019000u + 0x90u) = vD;
    *(volatile unsigned int *)(0x41008000u + 0x90u) = vE;
    *(volatile unsigned int *)(0x4100f000u + 0x504u) = (1u << chD) | (1u << chE);
}
