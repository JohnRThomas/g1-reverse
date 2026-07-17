#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100e95c @ 0x0100e95c
 * public-name: FUN_0100e95c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   g_sdc_max_frag_len                       @ 0x21000eae
 */
/* net-core FUN_0100e95c @ 0x100e95c  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void sdc_assertion_fail(unsigned int, unsigned int) __attribute__((noreturn));
extern int FUN_0100cfc0(unsigned short, void*);
extern int FUN_0100a17c(unsigned short);
extern void FUN_0100ec40(void);
extern int FUN_010269ce(int, unsigned short);
extern void FUN_0102709e(int, int, void*);
extern void FUN_0100e5dc(void*, unsigned int);
extern void FUN_01025998(void*, unsigned int, unsigned short);
extern int FUN_01026acc(int, unsigned short);
extern void FUN_01013da8(void);

#define G_LEN (*(volatile unsigned short *)((unsigned long)&g_sdc_max_frag_len) /*=0x21000eae*/)

int FUN_0100e95c(unsigned int *param_1)
{
    struct { unsigned char b0; unsigned char pad[3]; int ctx; } locA, locB;
    unsigned short *ptrA, *ptrB;
    unsigned short uVar1, uVar2;
    unsigned int uVar8;
    int iVar3, iVar4, iVar5, iVar6;
    unsigned int uVar7;
    char tag = *(volatile char *)(param_1 + 2);

    if (tag == 0) {
        uVar1 = *(volatile unsigned short *)(param_1 + 1);
        uVar2 = *(volatile unsigned short *)((char *)param_1 + 6);
        uVar8 = *param_1;
        iVar3 = FUN_0100cfc0(uVar1, &locA);
        if (iVar3 != 0) return 1;
        iVar3 = locA.ctx + 0xa8;
        if (uVar2 == 0) {
            *(volatile unsigned char *)(iVar3 + 0x24) = 1;
            return 1;
        }
        iVar6 = FUN_0100a17c(uVar1);
        if (iVar6 == 0) sdc_assertion_fail(0x2b, 0x67);
        iVar4 = FUN_010269ce(iVar6, uVar2);
        if (iVar4 == 0 || G_LEN < uVar2) { FUN_0100ec40(); return 1; }
        FUN_0102709e(iVar6, iVar4, &ptrA);
        *ptrA = 0;
        *((unsigned char *)ptrA + 2) = 0;
        FUN_0100e5dc(ptrA, 2);
        FUN_01025998((char *)ptrA + 3, uVar8, uVar2);
        iVar6 = FUN_01026acc(iVar6, uVar2);
        if (iVar6 == 0) sdc_assertion_fail(0x2b, 0x7c);
        if (locA.b0 != 0) {
            int local_24 = locA.ctx;
            if (*(volatile unsigned char *)(local_24 + 0x2ea) != 0) {
                *(volatile unsigned char *)(local_24 + 0x2ea) = 0;
                FUN_01013da8();
                local_24 = locA.ctx;
            }
            *(volatile unsigned short *)(local_24 + 0x2e2) = 0;
        }
        *(volatile unsigned char *)(iVar3 + 0x24) = 0;
        return iVar6;
    } else {
        if (tag != 1) return 0;
        uVar1 = *(volatile unsigned short *)(param_1 + 1);
        uVar2 = *(volatile unsigned short *)((char *)param_1 + 6);
        uVar8 = *param_1;
        iVar3 = FUN_0100cfc0(uVar1, &locB);
        iVar6 = locB.ctx;
        if (iVar3 != 0) return 1;
        iVar3 = locB.ctx + 0xa8;
        if (uVar2 == 0) {
            *(volatile unsigned char *)(iVar3 + 0x24) = 1;
            return 1;
        }
        iVar4 = FUN_0100a17c(uVar1);
        if (iVar4 == 0) sdc_assertion_fail(0x2b, 0x67);
        iVar5 = FUN_010269ce(iVar4, uVar2);
        if (iVar5 == 0 || G_LEN < uVar2) { FUN_0100ec40(); return 1; }
        FUN_0102709e(iVar4, iVar5, &ptrB);
        *ptrB = 0;
        *((unsigned char *)ptrB + 2) = 0;
        if (*(volatile unsigned char *)(iVar6 + 0xcc) == 0) uVar7 = 1;
        else uVar7 = 2;
        FUN_0100e5dc(ptrB, uVar7);
        FUN_01025998((char *)ptrB + 3, uVar8, uVar2);
        iVar6 = FUN_01026acc(iVar4, uVar2);
        if (iVar6 == 0) sdc_assertion_fail(0x2b, 0x7c);
        if (locB.b0 != 0) {
            if (*(volatile unsigned char *)(locB.ctx + 0x2ea) != 0) {
                *(volatile unsigned char *)(locB.ctx + 0x2ea) = 0;
                FUN_01013da8();
            }
            *(volatile unsigned short *)(locB.ctx + 0x2e2) = 0;
        }
        *(volatile unsigned char *)(iVar3 + 0x24) = 0;
        return iVar6;
    }
}
