/* readable reconstruction; identity: FUN_01029d76 @ 0x01029d76
 * public-name: FUN_01029d76
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_conn_window_admit                    <= FUN_010231c8 @ 0x010231c8
 */
/* net-core FUN_01029d76 @ 0x1029d76  (parity 300 trials PROVEN) */
#include <stdint.h>

extern int FUN_010219c4(unsigned char *a);
extern void FUN_01021a1c(void);
extern int sdc_conn_window_admit(unsigned char a, void *b);
extern int FUN_01023ea8(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void FUN_010256dc(unsigned int a, unsigned int b);
extern void FUN_01029d68(unsigned char *a, unsigned int b);
extern unsigned int PHANTOM_BOUNDARY(void);

unsigned char FUN_01029d76(unsigned char *param_1, unsigned char *param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned char uVar5;
    int iVar1;

    if (param_2 == 0) {
    switchD_default:
        param_1[0x29] = 1;
    LAB_e00:
        FUN_01021a1c();
        uVar5 = 2;
        return uVar5;
    }

    uVar5 = *param_2;
    switch (uVar5) {
    case 0:
        uVar5 = 2;
        return uVar5;
    case 1:
        if (*(volatile unsigned int *)(param_2 + 4) < 200) {
            uVar5 = 0;
        } else {
            iVar1 = FUN_01023ea8(*(volatile unsigned int *)(param_2 + 4), 3, param_3, param_4, param_4);
            if (iVar1 != 0) {
                uVar5 = 0;
            } else {
                FUN_01029d68(param_1, *(volatile unsigned int *)(param_2 + 4));
            }
        }
        return uVar5;
    case 2:
        FUN_01021a1c();
        return uVar5;
    case 3: {
        unsigned char r7 = param_1[0x24];
        if (r7 != 0) {
            goto LAB_e00;
        }
        {
            unsigned char *pcVar6 = *(volatile unsigned char **)(param_2 + 4);
            iVar1 = FUN_010219c4(pcVar6);
            if (iVar1 == 0) {
                goto switchD_default;
            }
            if (*pcVar6 == 0) {
                unsigned short uVar3;
                param_1[0xb] = 0;
                *param_1 = 1;
                uVar3 = (pcVar6[4] == 0) ? 0x2b : 0;
                *(volatile unsigned short *)(param_1 + 8) = uVar3;
                if (pcVar6[5] == 0) {
                    uVar5 = 2;
                }
                param_1[10] = uVar5;
                *(volatile int *)(param_1 + 4) = *(volatile int *)(pcVar6 + 8) + 0x73;
                {
                    unsigned int uVar4 = *(volatile unsigned int *)(pcVar6 + 0xc);
                    param_1[0x25] = 1;
                    *(volatile unsigned int *)(param_1 + 0x10) = uVar4;
                }
                param_1[0x26] = 3;
            } else {
                if (param_1[0x26] != 5) {
                    FUN_010256dc(0x6a, 0x17c);
                    /* falls through to r7==0 continuation (real hardware) */
                }
                {
                    unsigned short uVar3;
                    *param_1 = r7;      /* r7 == 0 on this reachable path */
                    param_1[0xb] = r7;
                    uVar3 = (pcVar6[4] == 0) ? 0x2b : 0;
                    *(volatile unsigned short *)(param_1 + 8) = uVar3;
                    if (pcVar6[5] == 0) {
                        uVar5 = 2;
                    }
                    param_1[10] = uVar5;
                    {
                        unsigned int uVar2 = *(volatile unsigned int *)(pcVar6 + 8);
                        *(volatile int *)(param_1 + 4) = *(volatile int *)(pcVar6 + 0xc) + 0x73;
                        {
                            int64_t base = *(volatile int64_t *)(param_1 + 0x18);
                            int64_t addend = (int64_t)(int32_t)uVar2;
                            int64_t sum = base + addend;
                            *(volatile int64_t *)(param_1 + 0x10) = sum;
                        }
                    }
                    param_1[0x26] = 4;
                    iVar1 = sdc_conn_window_admit(param_1[0x27], param_1);
                    if (iVar1 == 0) {
                        return (unsigned char)PHANTOM_BOUNDARY();
                    }
                }
            }
        }
        goto LAB_e00;
    }
    default:
        goto switchD_default;
    }
}
