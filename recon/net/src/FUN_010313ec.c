/* net-core FUN_010313ec @ 0x10313ec  (parity 300 trials PROVEN) */
extern int rtc_compare_int_lock(void);                    /* FUN_01031248 */
extern unsigned long long z_nrf_rtc_timer_read(void);     /* FUN_010313a8 */
extern int rtc_compare_event_clear(int);                  /* FUN_0103a6ae */
extern int rtc_compare_int_unlock(int, int);              /* FUN_010312d0 */

int FUN_010313ec(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4,
                 unsigned int param_5, unsigned int param_6, char param_7)
{
    (void)param_2;
    int interrupt_was_enabled = rtc_compare_int_lock();
    unsigned long long current_time = z_nrf_rtc_timer_read();
    unsigned long long PARAM34 = (((unsigned long long)param_4) << 32) | param_3;
    int uVar6;

    if (current_time >= PARAM34) {
        if (param_7 == 0) {
            /* atomic_or(&force_isr_mask, BIT(chan)); raw SRAM back-map 0x21004964 */
            __atomic_fetch_or((unsigned int*)0x21004964u, (1u << param_1), __ATOMIC_ACQ_REL);
            goto STORE_BLOCK;
        } else {
            uVar6 = (int)0xffffffea;
            goto DONE;
        }
    } else {
        unsigned long long diff = PARAM34 - current_time;
        if (diff >= 0x800001ull) {
            uVar6 = (int)0xffffffea;
            goto DONE;
        }
        {
            unsigned int base = 0x21002b60u + param_1*16u;
            unsigned int stored8 = *(volatile unsigned int*)(unsigned long)(base+8);
            unsigned int storedc = *(volatile unsigned int*)(unsigned long)(base+0xc);
            if (param_4 != storedc || param_3 != stored8) {
                unsigned int iVar7 = 0x10000u << (param_1 & 0xffu);
                *(volatile unsigned int*)0x41016348ul = iVar7;
                rtc_compare_event_clear((int)param_1);
                unsigned int iVar8 = 3;
                unsigned int uVar2 = param_3 & 0xffffffu;
                unsigned int idx = param_1 + 0x150u;
                volatile unsigned int * const rtc =
                    (volatile unsigned int *)0x41016000u; /* RTC0_NS raw MMIO back-map */
                volatile unsigned int * const compare_event =
                    (volatile unsigned int *)(0x41016000u +
                    ((((param_1 + 0x50u) * 4u) & 0xffffu)));
                for (;;) {
                    rtc[idx] = uVar2 & 0xffffffu; /* CC[param_1], raw 0x0103146a */
                    rtc[0x344u/4u] = iVar7;       /* INTENSET, raw 0x0103146e */
                    unsigned int iVar5 = rtc[0x504u/4u]; /* COUNTER @ 0x41016504 */
                    if ((((uVar2 - iVar5) - 3u) & 0xffffffu) <= 0x7ffffdu) break;

                    /* Stock NCS 2.5.1 set_alarm(): an already-latched compare may
                     * belong to the prior CC value, so re-read COUNTER before deciding. */
                    if (*compare_event != 0u) {
                        iVar5 = rtc[0x504u/4u]; /* second COUNTER read, raw 0x01031488 */
                        if (((iVar5 - (param_3 & 0xffffffu)) & 0xffffffu) <= 0x800000u) {
                            break;
                        }
                        rtc_compare_event_clear((int)param_1);
                    }
                    if (param_7 != 0) { uVar6 = (int)0xffffffea; goto DONE; }
                    uVar2 = iVar8 + iVar5;
                    iVar8 = iVar8 + 1;
                }
            }
        }
        goto STORE_BLOCK;
    }

STORE_BLOCK: ;
    {
        unsigned int iVar4 = 0x21002b60u + param_1*16u;
        *(volatile unsigned int*)(unsigned long)iVar4 = param_5;
        *(volatile unsigned int*)(unsigned long)(iVar4+8) = param_3;
        *(volatile unsigned int*)(unsigned long)(iVar4+0xc) = param_4;
        *(volatile unsigned int*)(unsigned long)(iVar4+4) = param_6;
        uVar6 = 0;
    }
DONE:
    rtc_compare_int_unlock((int)param_1, interrupt_was_enabled);
    return uVar6;
}
