/* readable reconstruction; identity: FUN_0102d0c4 @ 0x0102d0c4
 * public-name: FUN_0102d0c4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_rtc_timer_sync_valid               @ 0x21004fa9
 *   g_sdc_clock_calc_valid                   @ 0x21004faa
 *   g_sdc_clock_calc_lock                    @ 0x21004fab
 *   REG_4100b000                             @ 0x4100b000
 */
/* net-core FUN_0102d0c4 @ 0x102d0c4  (parity 300 trials PROVEN) */
#include <stdint.h>

extern int FUN_01039dec(unsigned int a, unsigned int b, unsigned int c, unsigned int *d);
extern uint64_t FUN_0102cfec(void);

#define DAT_19c 0x21004fabu
#define DAT_1a0 0x41011000u
#define DAT_1a4 0x41016000u
#define DAT_1a8 0x21004fa9u
#define DAT_1ac 0x007ffffeu
#define DAT_1b0 0x41012000u
#define DAT_1b4 0x4100b000u
#define DAT_1b8 0x007ffffbu
#define DAT_1bc 0x21004faau

void FUN_0102d0c4(void)
{
    unsigned int local_18, local_14;
    int iVar6;
    unsigned int uVar8;
    int iVar2, iVar3;
    unsigned int uVar7;
    unsigned char uVar5;

    /* ExclusiveAccess(DAT_19c) -- inline ldrexb, no observable side effect modeled */
    (void)*(volatile unsigned char *)DAT_19c;

    local_18 = 0;
    local_14 = 0;

    do {
        iVar6 = *(volatile int *)(DAT_1a4 + 0x504);
        /* DataMemoryBarrier(0x1f) -- inline dmb, no-op under this model */
        uVar8 = *(volatile unsigned int *)(DAT_1a0 + 0x504);
    } while (iVar6 != *(volatile int *)(DAT_1a4 + 0x504));

    iVar2 = FUN_01039dec(DAT_1a4, 3, (unsigned int)iVar6, &local_18);
    iVar3 = FUN_01039dec(DAT_1a0, 0xf, uVar8, &local_14);

    if (iVar3 == 0) {
        if (iVar2 != 0) {
            goto LAB_118;
        }
        goto BOTTOM;
    } else {
        if (iVar2 == 0 || local_14 < local_18) {
            local_18 = local_14;
        }
    LAB_118:
        uVar7 = (unsigned int)((iVar6 + (int)local_18) - 1) & 0xffffffu;
        if (uVar7 == *(volatile unsigned int *)(DAT_1a4 + 0x54c)) {
            if (*(volatile unsigned char *)DAT_1a8 == 0) {
                uVar5 = 0;
                goto LAB_18c;
            }
            goto BOTTOM;
        } else {
            uint64_t uVar9 = FUN_0102cfec();
            unsigned char *puVar4 = (unsigned char *)(uintptr_t)(uVar9 >> 32);
            int base = (int)(uVar9 & 0xffffffffu);
            *(volatile unsigned int *)(base + 0x54c) = uVar7;
            if (local_18 <= DAT_1ac) {
                unsigned int diff = (uVar7 - *(volatile unsigned int *)(base + 0x504)) & 0xffffffu;
                if (DAT_1b8 < diff - 3) {
                    *puVar4 = 0;
                    uVar5 = 0;
                    goto LAB_18c;
                }
            }
            *puVar4 = 1;
        }
    }

BOTTOM:
    *(volatile unsigned int *)(DAT_1b0 + 0x1ac) = *(volatile unsigned int *)(DAT_1b0 + 0x1ac) | 0x80000000u;
    if (*(volatile int *)(DAT_1a4 + 0x14c) != 0) {
        uVar5 = 1;
        goto LAB_18c;
    } else {
        *(volatile int *)(DAT_1b4 + 4) = 1;
        if (*(volatile int *)(DAT_1a4 + 0x14c) != 0) {
            *(volatile int *)(DAT_1b4 + 0) = 1;
        }
    }
    uVar5 = 1;
LAB_18c:
    *(volatile unsigned char *)DAT_1bc = uVar5;
    return;
}
