#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010119ac @ 0x010119ac
 * public-name: FUN_010119ac
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_radio_transition_schedule     <= FUN_01020a6c @ 0x01020a6c
 * address symbols (name @ address):
 *   g_net_own_addr_info                      @ 0x21000f20
 *   g_21000f24                               @ 0x21000f24
 */
/* net-core FUN_010119ac @ 0x10119ac  (parity 400 trials PROVEN) */
extern void sdc_assertion_fail(int,int);
extern int FUN_0100dfbc(void*,int);
extern int FUN_0100e008(void*,void*);
extern int FUN_0100e028(void*,void*);
extern int FUN_0100e038(void*,int);
extern int FUN_0100e054(void*,int);
extern int FUN_0100e06c(void*,unsigned int,int);
extern int FUN_010129e8(void*);
extern int FUN_010129f4(void*);
extern int FUN_01012ad4(void*);
extern int FUN_01012b24(void*);
extern int FUN_01012b48(void);
extern int FUN_01012b98(int);
extern int FUN_01012ba4(int,int,int);
extern int FUN_010204f4(void);
extern int FUN_010202fc(int,int);
extern int FUN_01020764(void*);
extern int controller_radio_transition_schedule(int,int,int);
extern int FUN_010208f0(int,int,int);
extern int FUN_01021108(int,int);
extern void FUN_01011664(void*);
extern int FUN_01020820(int);

void FUN_010119ac(unsigned char *param_1, int param_2)
{
    volatile unsigned int *puVar9 = (volatile unsigned int *)((unsigned long)&g_net_own_addr_info) /*=0x21000f20*/;
    unsigned short *puVar5;
    unsigned char *pbVar6;
    int iVar7, iVar8;
    char cVar3, cVar4;
    unsigned char *puVar10;

    if (param_2 != 0) {
        puVar10 = param_1 + 0x28;
        iVar7 = FUN_01012ad4(puVar10);
        if (iVar7 == 0) {
            unsigned short uVar2 = *(unsigned short *)(param_1 + 2);
            if ((int)((unsigned)uVar2 << 0x1c) >= 0) {
                FUN_01011664(param_1);
                return;
            }
            cVar3 = (char)FUN_01012b24(puVar10);
            cVar4 = (char)FUN_01012ad4(puVar10);
            iVar8 = FUN_01012b98((unsigned char)(cVar3 - cVar4));
            puVar9[2] = puVar9[2] + iVar8;
            FUN_010129e8(puVar10);
        }
        FUN_010129f4(puVar10);
        FUN_010204f4();
        FUN_010202fc(0x25, param_1[4]);
    }

    puVar5 = (unsigned short *)*puVar9;
    cVar3 = (char)param_1[0x6e];
    *puVar5 = 0;
    switch (*(unsigned short *)(param_1 + 2)) {
    case 0x10:
        FUN_0100dfbc(puVar5, 2);
        pbVar6 = (unsigned char *)*puVar9;
        break;
    case 0x12:
        FUN_0100dfbc(puVar5, 6);
        pbVar6 = (unsigned char *)*puVar9;
        break;
    case 0x13:
        FUN_0100dfbc(puVar5, 0);
        pbVar6 = (unsigned char *)*puVar9;
        *pbVar6 = (*pbVar6 & 0xdf) | 0x20;
        break;
    case 0x15:
    case 0x1d:
        FUN_0100dfbc(puVar5, 1);
        pbVar6 = (unsigned char *)*puVar9;
        *pbVar6 = (*pbVar6 & 0xdf) | 0x20;
        if (cVar3 == 0) {
            FUN_0100e028(pbVar6, param_1 + 0x68);
            FUN_0100e054((void *)*puVar9, param_1[0x67]);
            pbVar6 = (unsigned char *)*puVar9;
        } else {
            FUN_0100e028(pbVar6, param_1 + 0x6f);
            FUN_0100e054((void *)*puVar9, 1);
            pbVar6 = (unsigned char *)*puVar9;
        }
        break;
    default:
        sdc_assertion_fail(0x2d, 0x64a);
        __builtin_unreachable();
    }

    FUN_0100e008(pbVar6, param_1 + 0x61);
    FUN_0100e038((void *)*puVar9, param_1[0x60]);
    if ((*(unsigned short *)(param_1 + 2) & 0xfff7) != 0x15) {
        FUN_0100e06c((void *)*puVar9, *(unsigned int *)(param_1 + 0x48), param_1[0x4c]);
    }
    FUN_01020764((void *)*puVar9);
    *(volatile unsigned char *)((unsigned long)&g_21000f24) /*=0x21000f24*/ = 4;

    if (param_2 != 0) {
        if (*(unsigned short *)(param_1 + 2) == 0x10) {
            FUN_01021108(0, param_1[4]);
        } else {
            iVar7 = (int)puVar9[3];
            cVar3 = (char)FUN_01012b24(param_1 + 0x28);
            cVar4 = (char)FUN_01012ad4(param_1 + 0x28);
            iVar8 = FUN_01012ba4((unsigned char)((cVar3 - 1) - cVar4),
                                 *(unsigned short *)(param_1 + 2), 0x28);
            iVar7 = iVar7 + iVar8;
            if ((int)((unsigned)*(unsigned short *)(param_1 + 2) << 0x1c) < 0) {
                iVar7 = iVar7 + (int)puVar9[2];
                iVar8 = FUN_01012b48();
                *(int *)(param_1 + 0x110) = iVar8 + iVar7;
            }
            iVar8 = controller_radio_transition_schedule(0, iVar7, param_1[4]);
            if (iVar8 == 0) {
                sdc_assertion_fail(0x2d, 0xd65);
            }
        }
    }

    switch (*(unsigned short *)(param_1 + 2)) {
    case 0x10:
        return;
    case 0x12:
    case 0x13:
    case 0x15:
    case 0x1d:
        FUN_010208f0(0, 1, param_1[4]);
        return;
    default:
        sdc_assertion_fail(0x2d, 0xd79);
    }
}
