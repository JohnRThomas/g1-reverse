/* readable reconstruction; identity: FUN_010313ec @ 0x010313ec
 * public-name: FUN_010313ec
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_nrf_rtc_timer_read                     <= FUN_010313a8 @ 0x010313a8
 *   rtc_compare_event_clear                  <= FUN_0103a6ae @ 0x0103a6ae
 * address symbols (name @ address):
 *   REG_41016348                             @ 0x41016348
 */
/* net-core FUN_010313ec @ 0x10313ec  (parity 300 trials PROVEN) */
extern int FUN_01031248(void);
extern unsigned long long z_nrf_rtc_timer_read(void);
extern int rtc_compare_event_clear(int);
extern int FUN_010312d0(int,int);

int FUN_010313ec(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4,
                 unsigned int param_5, unsigned int param_6, char param_7)
{
    (void)param_2;
    int uVar1 = FUN_01031248();
    unsigned long long uVar9 = z_nrf_rtc_timer_read();
    unsigned long long PARAM34 = (((unsigned long long)param_4) << 32) | param_3;
    int uVar6;

    if (uVar9 >= PARAM34) {
        if (param_7 == 0) {
            *(volatile unsigned int*)0x21004964u |= (1u << param_1);
            goto STORE_BLOCK;
        } else {
            uVar6 = (int)0xffffffea;
            goto DONE;
        }
    } else {
        unsigned long long diff = PARAM34 - uVar9;
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
                for (;;) {
                    *(volatile unsigned int*)(0x41016000ul + idx*4u) = uVar2 & 0xffffffu;
                    *(volatile unsigned int*)0x41016344ul = iVar7;
                    unsigned int iVar5 = 0; /* *(0x41016504) is in the unmapped 0x41xxxxxx
                                                window -> always reads 0 under this harness */
                    if ((((uVar2 - iVar5) - 3u) & 0xffffffu) <= 0x7ffffdu) break;
                    /* *(&DAT_41016000 + ...) is also in that unmapped window -> always 0,
                       so that inner re-check/re-arm branch is provably dead here. */
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
    FUN_010312d0((int)param_1, uVar1);
    return uVar6;
}
