#include "g1_net_symbols.h"
/* net-core FUN_0101da18 @ 0x101da18  (parity 10 trials PROVEN) */
/* net-core FUN_0101da18 @ 0x101da18  (parity 4 trials PROVEN) */
/* net-core FUN_0101da18 @ 0x101da18  (parity 7 trials PROVEN) */
#include <stdint.h>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

extern void FUN_01008d00(uint, uint);
extern void FUN_0100d14c(void *, uint);
extern int FUN_0100d3c0(void *, uint, uchar, uint, uint);
extern ushort FUN_0100d5d0(uint);
extern void FUN_0100efc8(void *, uint, uint);
extern void FUN_0101bdd4(void *, uint);

#define DAT_101dbe4 ((uintptr_t)&g_net_link_ctx_b) /*=0x21001124*/
#define DAT_101dbe0 ((uintptr_t)&rodata_10101cd) /*=0x10101cd*/
#define DAT_101dbdc ((uintptr_t)&rodata_10109cd) /*=0x10109cd*/

void FUN_0101da18(ushort *param_1, int param_2, uint param_3, uint param_4)
{
    uint iVar3;
    uint uVar1;
    uint uVar2;
    int iVar5;
    ushort uVar4;
    uint uVar6;
    char *pcVar7;
    short sVar8;
    uint uVar9;
    uint uVar10;

    iVar3 = DAT_101dbe4;
    uVar2 = DAT_101dbe0;
    uVar1 = DAT_101dbdc;
    if (param_2 == 0) {
        return;
    }
    uVar10 = ((uint)param_2 - 1U) & 0xffff;
    do {
        param_1[0x181] = param_1[0x181] + 1;
        param_1[0x7b] = param_1[0x7b] + 1;
        if ((*(volatile char *)((int)param_1 + 0xcb) != 0) ||
            ((iVar5 = FUN_0100d3c0(param_1 + 0x54, 6, *(volatile uchar *)((int)param_1 + 0xc5), 0, param_4)),
             iVar5 != 0)) {
            uVar6 = *(volatile uint *)(param_1 + 0x76);
            uVar9 = *(volatile int *)(param_1 + 0x74) + 1;
            *(volatile uint *)(param_1 + 0x74) = uVar9;
            if ((uVar6 < uVar9) || (uVar6 - uVar9 <= (ushort)param_1[0xe] + 5)) {
                *(volatile uchar *)(param_1 + 0x7a) = 1;
            }
            if (uVar6 <= uVar9) {
                *(volatile uint *)(param_1 + 0x74) = 0;
                FUN_0100efc8((char *)param_1 + 0x1c5, uVar1, 2);
            }
        }
        if (*(volatile char *)(param_1 + 0x80) != 0) {
            param_1[0x7e] = param_1[0x7e] + 1;
        }
        if (*(volatile char *)(param_1 + 0x82) != 0) {
            param_1[0x81] = param_1[0x81] + 1;
        }
        if ((*(volatile char *)(param_1 + 0xb0) != 0) ||
            ((iVar5 = FUN_0100d3c0(param_1 + 0x54, 1, *(volatile uchar *)((int)param_1 + 199), 0, param_4)),
             iVar5 != 0)) {
            param_1[0x7d] = param_1[0x7d] + 1;
        }
        uVar6 = (uint)*(volatile uchar *)((int)param_1 + 0xc5);
        sVar8 = param_1[0x5e];
        if (uVar6 - 0xc < 2) {
            sVar8 = sVar8 + 1;
            if ((short)param_1[0x18b] == sVar8) {
                *(volatile uint *)(param_1 + 0x67) = *(volatile uint *)(*(volatile int *)(param_1 + 0x188) + 1);
                *(volatile uchar *)(param_1 + 0x69) = *(volatile uchar *)(*(volatile int *)(param_1 + 0x188) + 5);
                FUN_0100d14c(param_1, 3);
                if (**(volatile char **)(param_1 + 0x188) == 0) {
                    FUN_01008d00(0x36, 0x21e);
                    return;
                }
                if (*(volatile char *)(*(volatile int *)(iVar3 + 4) + 0x14e) != 1) {
                    pcVar7 = *(volatile char **)(*(volatile int *)(iVar3 + 4) + 0x310);
                    *pcVar7 = *pcVar7 + (char)-1;
                }
                *(volatile uchar *)((int)param_1 + 0xc5) = 0;
                sVar8 = param_1[0x5e];
                *(volatile uchar *)(param_1 + 0x8f) = 0xff;
                uVar6 = (uint)*(volatile uchar *)((int)param_1 + 0xc5);
                goto LAB_0101da86;
            }
        } else {
        LAB_0101da86:
            sVar8 = sVar8 + 1;
            if ((uVar6 - 0xe < 2) && ((short)param_1[399] == sVar8)) {
                param_1[0x117] = *param_1;
                uVar4 = FUN_0100d5d0(*(volatile uint *)(param_1 + 0x194));
                param_1[0x118] = uVar4;
                param_1[0x119] = param_1[0x196];
                *(volatile uchar *)((int)param_1 + 0x22d) = 0;
                param_1[0x11a] = param_1[0x197];
                FUN_0100efc8(param_1 + 0x112, uVar2, 2);
                *(volatile uchar *)(param_1 + 0x18e) = 0;
                FUN_0100d14c(param_1, 2);
                FUN_0101bdd4(param_1, 3);
                *(volatile uchar *)((int)param_1 + 0xc5) = 0;
                sVar8 = param_1[0x5e] + 1;
            }
        }
        param_1[0x5e] = sVar8;
        uVar10 = (uVar10 - 1) & 0xffff;
        if (uVar10 == 0xffff) {
            return;
        }
    } while (1);
}



