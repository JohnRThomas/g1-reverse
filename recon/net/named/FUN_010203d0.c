/* readable reconstruction; identity: FUN_010203d0 @ 0x010203d0
 * public-name: FUN_010203d0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_010203d0 @ 0x10203d0  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01025b5c(void);

#define DAT_4b0 0xe000e100u
#define DAT_4b4 0x41008000u
#define DAT_4b8 0x01ff0000u
#define DAT_4bc 0xfffff000u
#define DAT_4c0 0x210015f0u
#define DAT_4c4 0x4100c000u
#define DAT_4c8 0x8000000au
#define DAT_4cc 0x80000003u
#define DAT_4d0 0x4100f000u

void FUN_010203d0(void)
{
    unsigned int uVar5 = DAT_4bc;
    unsigned int iVar4 = DAT_4b8;
    unsigned int uVar2 = DAT_4b4;
    unsigned int uVar3;
    int iVar8;
    unsigned int iVar7 = 0;
    void (*jt)(void);

    *(volatile unsigned int *)(DAT_4b0 + 0x80) = 0x100;
    /* DataSynchronizationBarrier / InstructionSynchronizationBarrier -- inline, no-op */

    iVar8 = 0;
    *(volatile unsigned int *)(DAT_4b4 + 0xffc) = 0;
    *(volatile unsigned int *)(uVar2 + 0xffc) = 1;
    do {
        iVar7 = iVar4 + (unsigned int)iVar8 * 8;
        iVar8 = iVar8 + 1;
        if ((*(volatile unsigned int *)(iVar7 + 0x300) & uVar5) == uVar2) {
            *(volatile unsigned int *)(*(volatile unsigned int *)(iVar7 + 0x300)) =
                *(volatile unsigned int *)(iVar7 + 0x304);
        }
        uVar3 = DAT_4b4;
    } while (iVar8 != 0x20);

    *(volatile unsigned int *)(DAT_4b4 + 0x534) = 0x103;
    *(volatile unsigned int *)(uVar3 + 0x538) = 0x65b;
    iVar4 = DAT_4b8;
    *(volatile unsigned int *)(uVar3 + 0x530) = 1;
    *(volatile unsigned int *)(uVar3 + 0x510) = 3;
    iVar7 = DAT_4c0;
    *(volatile unsigned char *)(iVar7 + 0x18) = 1;
    *(volatile unsigned int *)(uVar3 + 0x588) = *(volatile unsigned int *)(iVar4 + 0x80);
    *(volatile unsigned int *)(uVar3 + 0x650) = 0x201;
    *(volatile unsigned int *)(uVar3 + 0x200) = 0x100000;

    FUN_01025b5c();

    {
        unsigned int iVar6 = DAT_4cc;
        unsigned int iVar8b = DAT_4c8;
        unsigned int iVar4b = DAT_4c4;
        *(volatile unsigned int *)(DAT_4c4 + 0x1c0) = DAT_4c8;
        *(volatile unsigned int *)(uVar3 + 0x1a8) = iVar6;
        *(volatile unsigned int *)(iVar4b + 200) = iVar8b - 4;
        *(volatile unsigned int *)(iVar4b + 0xc4) = iVar6 + 2;
    }
    *(volatile unsigned int *)(DAT_4d0 + 0x504) = 0x1df8;

    *(volatile unsigned int *)(iVar7 + 0x14) = *(volatile unsigned int *)(uVar3 + 0x900);
    *(volatile unsigned short *)(iVar7 + 0x1c) = 0x96;
    *(volatile unsigned short *)(iVar7 + 0x28) = 0;
    *(volatile unsigned int *)(iVar7 + 0x24) = 0;
    *(volatile unsigned char *)(iVar7 + 0x35) = 0;
    *(volatile unsigned char *)(iVar7 + 0x44) = 0;
    jt = *(void (* volatile *)(void))(iVar7 + 0x48);
    *(volatile unsigned int *)(DAT_4b0 + 0x180) = 0x100;
    *(volatile unsigned int *)(uVar3 + 0x304) = 0x10;
    *(volatile unsigned int *)DAT_4b0 = 0x100;

    if (jt != 0) {
        jt();
        return;
    }
    return;
}
