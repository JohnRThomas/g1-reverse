/* readable reconstruction; identity: FUN_0101aee0 @ 0x0101aee0
 * public-name: FUN_0101aee0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_101b321                           @ 0x0101b321
 *   g_net_session_state_block                @ 0x210010a0
 */
/* net-core FUN_0101aee0 @ 0x101aee0  (parity 6 trials PROVEN) */
#include <stdint.h>

extern void FUN_01008d00(unsigned int a, unsigned int b);
extern void *FUN_01019204(void);
extern int FUN_0101a130(void);
extern int FUN_0101a38c(void *a, int b, int c, unsigned int d);
extern int FUN_01022e34(unsigned int a, int b);
extern int FUN_010231c8(unsigned char a, void *b);

#define PCVAR2 ((volatile char *)0x210010a0u)
#define DAT_afa4 (0x0101b321u)

unsigned int FUN_0101aee0(int param_1, unsigned int param_2)
{
    volatile char *pcVar2;
    volatile unsigned char *puVar3;
    int iVar4;
    int iVar6;
    unsigned int iVar5;
    char cVar1;
    unsigned int uVar7, uVar8;
    unsigned char auStack_30[24];

    pcVar2 = PCVAR2;
    if (*pcVar2 != 0) {
        return 0xc;
    }
    puVar3 = (volatile unsigned char *)FUN_01019204();
    cVar1 = *(volatile char *)(param_1 + 0x300);
    *(volatile int *)(pcVar2 + 0x28) = param_1;
    if (cVar1 != 0)
        goto fatal_300;

    pcVar2[1] = 0;
    pcVar2[0x2e] = 0;
    *pcVar2 = 5;
    *(volatile uint16_t *)(pcVar2 + 0x74) = 0;
    pcVar2[0x2c] = 0;
    iVar4 = FUN_0101a130();
    iVar5 = 0;
    uVar7 = 0;
    uVar8 = 0;
    do {
        iVar6 = uVar7 + 2;
        uVar8 = uVar8 + 1;
        uVar7 = uVar8 & 0xff;
        iVar5 = iVar5 + iVar4 + *(int *)(pcVar2 + iVar6 * 4);
    } while (uVar7 <= (unsigned char)pcVar2[0x2f]);
    *(volatile int *)(pcVar2 + 0x58) = iVar5;

    iVar5 = FUN_01022e34(DAT_afa4, 0);
    *puVar3 = (unsigned char)iVar5;
    if (iVar5 == 0x20) {
        goto fatal_30e;
    }

    iVar5 = FUN_0101a38c(auStack_30, 1, 0, param_2);
    if (iVar5 == 0) {
        goto fatal_311;
    }

    iVar5 = FUN_010231c8(*puVar3, auStack_30);
    if (iVar5 != 0) {
        return 0;
    }
    FUN_01008d00(0x21, 0x312);
    return 0;
fatal_311:
    FUN_01008d00(0x21, 0x311);
    return 0;
fatal_30e:
    FUN_01008d00(0x21, 0x30e);
    return 0;
fatal_300:
    FUN_01008d00(0x21, 0x300);
    return 0;
}
