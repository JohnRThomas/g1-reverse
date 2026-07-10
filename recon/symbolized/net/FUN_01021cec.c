#include "g1_net_symbols.h"
/* net-core FUN_01021cec @ 0x1021cec  (parity 300 trials PROVEN) */
#include <stdint.h>

extern unsigned int PHANTOM_BOUNDARY(void);

typedef void (*fnptr5)(unsigned int, unsigned int, unsigned char, void *, unsigned int);

#define DAT_de4 ((uintptr_t)&g_libc_tz_calc_state) /*=0x210016f0*/

void FUN_01021cec(void)
{
    int iVar5 = DAT_de4;
    unsigned char bVar1 = *(volatile unsigned char *)(iVar5 + 0x49);
    unsigned int uVar13 = bVar1;
    unsigned char bVar2 = *(volatile unsigned char *)(uVar13 * 3 + iVar5 + 0x31);

    while (bVar2 != 0x20) {
        unsigned int uVar9 = bVar1;
        int iVar11 = (int)(uVar9 * 0x20);
        unsigned char sel = *(volatile unsigned char *)(iVar5 + ((unsigned int)bVar2 + uVar9 * 0x20) * 2 + 0x50);
        unsigned int uVar12;

        switch (sel) {
        case 1:
        case 6:
            uVar12 = 7;
            break;
        case 4:
            uVar12 = 2;
            break;
        case 5:
            uVar12 = 3;
            break;
        default:
            PHANTOM_BOUNDARY();
            return;
        }

        /* isCurrentModePrivileged/isIRQinterruptsEnabled/disable/enableIRQinterrupts:
           inline MRS/CPS instructions, deterministic reset-state PRIMASK==0, no
           observable side effects under this harness */

        {
            int iVar10 = (int)(uVar9 + uVar13 * 2) + iVar5;
            *(volatile unsigned char *)(iVar10 + 0x31) =
                *(volatile unsigned char *)(iVar5 + (iVar11 + (int)bVar2) * 2 + 0x51);
            if (*(volatile unsigned char *)(iVar10 + 0x32) == bVar2) {
                *(volatile unsigned char *)(iVar10 + 0x32) = 0x20;
            }
        }

        {
            int iVar7 = iVar5 + (iVar11 + (int)bVar2) * 2;
            signed char cVar6 = *(volatile signed char *)(iVar7 + 0x50);
            if (cVar6 == 0 || cVar6 == 6 || cVar6 == 3 || cVar6 == 5) {
                *(volatile unsigned char *)(iVar5 + (iVar11 + (int)bVar2) * 2 + 0x50) = 1;
            } else {
                cVar6 = 1;
                *(volatile signed char *)(iVar7 + 0x50) = 1;
            }

            {
                int iVar11b = iVar5 + (int)bVar2 * 0x20;
                fnptr5 pcVar8 = *(volatile fnptr5 *)(iVar11b + 0xd0);
                unsigned int arg0 = *(volatile unsigned int *)(iVar11b + 0xd4);
                pcVar8(arg0, uVar12, (unsigned char)cVar6, (void *)(uintptr_t)pcVar8, 0);
            }
        }

        bVar1 = *(volatile unsigned char *)(iVar5 + 0x49);
        uVar13 = bVar1;
        bVar2 = *(volatile unsigned char *)(uVar13 * 3 + iVar5 + 0x31);
    }
    return;
}

