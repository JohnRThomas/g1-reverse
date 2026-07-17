/* readable reconstruction; identity: FUN_01017658 @ 0x01017658
 * public-name: FUN_01017658
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01017658 @ 0x1017658  (parity 300 trials PROVEN) */
#include <stdint.h>

extern unsigned int FUN_0100aaac(unsigned int a, unsigned int b);
extern unsigned int FUN_0100bc04(int a);
extern unsigned int FUN_0100ca68(unsigned int a);
extern unsigned int FUN_0100cad4(unsigned int a);
extern unsigned int FUN_0100cb10(void);
extern int FUN_010199cc(void);
extern unsigned int thunk_FUN_0101fd20(void);

#define DAT_773c 0x21000f90u

void FUN_01017658(int param_1, unsigned int param_2, char *param_3, unsigned char *param_4)
{
    int iVar2 = DAT_773c;
    unsigned int uVar8 = (unsigned int)(*(volatile unsigned char *)(DAT_773c + 0x7d) ^ 1);
    unsigned char uVar7 = (unsigned char)uVar8;
    int bVar1;
    signed char cVar3;
    unsigned int uVar4;
    int iVar5;

    if (*(volatile signed char *)(param_1 + 0x12) == 1 &&
        (*(volatile unsigned char *)(*(volatile int *)(param_1 + 8) + 5) & 0xc0) == 0x40) {
        bVar1 = 1;
    } else {
        bVar1 = 0;
    }

    cVar3 = *(volatile signed char *)(DAT_773c + 0x7c);
    if (cVar3 == 0) {
        goto LAB_be;
    }

    if (*(volatile signed char *)(DAT_773c + 0x54) == 3 &&
        *(volatile signed char *)(DAT_773c + 0x4d) != 0) {
        cVar3 = *(volatile signed char *)(DAT_773c + 0x7b);
        goto LAB_90;
    } else {
        if (*(volatile int *)(param_1 + 4) != 0) {
        LAB_8c:
            cVar3 = *(volatile signed char *)(iVar2 + 0x78);
            goto LAB_90;
        }
        iVar5 = FUN_010199cc();
        if (iVar5 != 0) {
            goto LAB_8c;
        }
        goto LAB_dc;
    }

LAB_90:
    if (cVar3 == -1 || cVar3 == 8) {
        goto LAB_dc;
    }
    uVar4 = FUN_0100bc04(cVar3);
    if (uVar4 != 0) {
        uVar8 = uVar4;
    }
    uVar7 = (unsigned char)uVar8;
    if (bVar1) {
        if (*(volatile signed char *)(iVar2 + 0x81) == 0) {
            unsigned int uVar6 = FUN_0100ca68((unsigned char)cVar3);
            cVar3 = (signed char)FUN_0100aaac(uVar6, *(volatile unsigned int *)(param_1 + 8));
        } else {
            cVar3 = (signed char)thunk_FUN_0101fd20();
            *(volatile unsigned char *)(iVar2 + 0x81) = 0;
        }
        goto LAB_be;
    }
    goto LAB_zero;

LAB_dc:
    if (bVar1 && *(volatile signed char *)(iVar2 + 0x80) == 0) {
        iVar5 = FUN_0100cad4(*(volatile unsigned int *)(param_1 + 8));
        cVar3 = (signed char)iVar5;
        *(volatile signed char *)(iVar2 + 0x7c) = cVar3;
        if (iVar5 != 0) {
            iVar5 = FUN_0100cb10();
            if (iVar5 == 0xff) {
                cVar3 = 0;
            } else {
                *(volatile signed char *)(iVar2 + 0x78) = (signed char)iVar5;
            }
        }
        goto LAB_be;
    }

LAB_zero:
    cVar3 = 0;
LAB_be:
    *param_3 = cVar3;
    *(volatile unsigned char *)param_2 = (unsigned char)bVar1;
    *param_4 = uVar7;
    return;
}
