/* net-core FUN_0103a9dc @ 0x103a9dc  (P4 iteration 25; parity 200/200 directed+randomized trials, 0 mismatches) */
/* nrfx_timer_compare(p_instance, cc_channel, cc_value, enable_int) @ 0x0103a9dc.
 * Ghidra-gap leaf; extent 0x30 (the shared tail `b 0x103a9fa` ends at
 * 0x0103aa0c and FUN_0103aa0c follows).  It clears EVENTS_COMPARE[ch] and sets
 * INTENSET bit (16+ch) when enable_int != 0, clears INTENCLR otherwise, and
 * always writes CC[ch] (0x540 + 4*ch).  Called twice by FUN_010330b0.
 */
void FUN_0103a9dc(unsigned int p_instance, unsigned int cc_channel,
                  unsigned int cc_value, unsigned int enable_int)
{
    volatile unsigned int *const *inst = (volatile unsigned int *const *)p_instance;
    volatile unsigned int *p_reg = *inst;
    unsigned int mask = 0x10000u << cc_channel;

    if (enable_int == 0) {
        *(volatile unsigned int *)((unsigned int)p_reg + 0x308u) = mask;
    } else {
        *(volatile unsigned int *)((unsigned int)p_reg + 0x140u + cc_channel * 4u) = 0u;
        (void)*(volatile unsigned int *)((unsigned int)p_reg + 0x140u + cc_channel * 4u);
        *(volatile unsigned int *)((unsigned int)*inst + 0x304u) = mask;
    }
    *(volatile unsigned int *)((unsigned int)*inst + (cc_channel + 0x150u) * 4u) = cc_value;
}
