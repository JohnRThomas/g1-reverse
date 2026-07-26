/* net-core FUN_01033968 @ 0x1033968  (parity 300 trials PROVEN) */
#include "../../headers/g1_nrf_regs.h"
extern void FUN_01033bf0(int a, int b);
extern void FUN_01032908(void);

unsigned int FUN_01033968(void)
{
    volatile unsigned char *pcVar1 = (volatile unsigned char *)0x21006458;
    unsigned int iVar2 = G1_NRF_RADIO_NS_BASE;
    unsigned int uVar3;

    if (*pcVar1 == 4 || *pcVar1 == 5) {
        FUN_01033bf0(1, 0);
        FUN_01032908();
        *(volatile unsigned int *)(iVar2 + 0x200) = 0;
        *(volatile unsigned int *)(iVar2 + 0x308) = 0xffffffff;
        *(volatile unsigned int *)0x210049a0 = 0;
        *(volatile unsigned int *)(iVar2 + 0x110) = 0;
        *(volatile unsigned int *)(iVar2 + 0x10) = 1;
        while (*(volatile unsigned int *)(iVar2 + 0x110) == 0) {
        }
        uVar3 = 0;
        *(volatile unsigned int *)(iVar2 + 0x110) = 0;
        *pcVar1 = 0;
    } else {
        uVar3 = 0xffffffea;
    }
    return uVar3;
}


