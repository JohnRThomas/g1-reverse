#include "g1_net_symbols.h"
/* net-core FUN_0101b15c @ 0x101b15c  (parity 8 trials PROVEN) */
#include <stdint.h>

extern void FUN_01008d00(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern int FUN_01019204(void);
extern int FUN_0101a218(void);
extern int thunk_FUN_01025034(void);

#define LIT_22C ((uintptr_t)&g_net_session_state_block) /*=0x210010a0*/

int FUN_0101b15c(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int iVar1;
    int iVar2;
    int iVar3;
    unsigned int uVar4;
    int bVar5;
    int iVar6;

    iVar1 = LIT_22C;
    iVar2 = thunk_FUN_01025034();
    iVar6 = *(volatile int *)(iVar1 + 0x18);
    iVar3 = FUN_01019204();
    uVar4 = (unsigned int)*(volatile unsigned char *)(iVar3 + 1);

    switch (param_1) {
    case 0:
        if (uVar4 == 8) {
            iVar3 = 0x728;
            break;
        }
        if (uVar4 == 4) {
            iVar3 = 0x140;
            goto LAB_0101b1f4;
        } else {
            if (uVar4 == 2) {
                iVar3 = 0x48;
                goto LAB_ADD_B0;
            } else {
                switch (uVar4) {
                case 1:
                    iVar3 = 0x150;
                    break;
                default:
                    for (;;) {
                        FUN_01008d00(5, 0x104, uVar4 - 1, uVar4, param_4);
                    }
                case 4:
                case 8:
                    iVar3 = 0xa0;
                    if (uVar4 == 4) {
                        goto LAB_0101b1f4;
                    }
                    break;
                }
                if (uVar4 != 2) {
                    iVar3 = iVar3 + 0xc0;
                    break;
                }
            }
        LAB_0101b1f4:
            iVar3 = iVar3 + 0x216;
            break;
        LAB_ADD_B0:
            iVar3 = iVar3 + 0xb0;
            break;
        }
        break;
    case 1:
    case 2:
    case 5:
    case 6:
        return 1;
    case 3:
        if ((*(volatile unsigned char *)(iVar3 + 1) & 0xc) == 0) {
            iVar3 = 0x35c;
        } else {
            iVar3 = 900;
        }
        break;
    case 4:
        iVar3 = 0x1f8;
        break;
    default:
        for (;;) {
            FUN_01008d00(0x21, 0x3d9, 0, 0, 0);
        }
    }

    uVar4 = (unsigned int)(iVar2 - iVar6) + (unsigned int)iVar3;
    if (uVar4 < (unsigned int)(*(volatile int *)(iVar1 + 0x38) - 0x11a)) {
        bVar5 = 1;
    } else {
        bVar5 = 0;
        iVar2 = FUN_0101a218();
        if (iVar2 != 0) {
            return uVar4 < (unsigned int)(*(volatile int *)(iVar1 + 0x38) - 0x11a);
        }
    }
    return bVar5;
}

