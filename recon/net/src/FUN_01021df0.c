/* net-core FUN_01021df0 @ 0x1021df0  (parity 300 trials PROVEN) */
#include <stdint.h>

extern int FUN_01021b7c(unsigned int *a, unsigned char b, void *c, unsigned char *d);
extern int FUN_010245d8(void);
extern int FUN_010246d8(void);

#define DAT_edc 0x210016f0u

int FUN_01021df0(unsigned int param_1, unsigned int *param_2, unsigned int param_3, unsigned int param_4, unsigned char param_5)
{
    unsigned char uStack_2a;
    unsigned char local_29[5];

    unsigned int call0 = (unsigned int)FUN_010245d8();
    int iVar1 = DAT_edc;
    unsigned int uVar5 = call0 + param_3;
    unsigned int carry0 = (uVar5 < call0) ? 1u : 0u;
    unsigned int uVar2 = param_4 + carry0;
    uint64_t new64 = ((uint64_t)uVar2 << 32) | uVar5;
    uint64_t old64 = ((uint64_t)param_2[1] << 32) | param_2[0];

    if (new64 < old64) {
        return 0;
    }

    for (;;) {
        int iVar3 = FUN_01021b7c(param_2, param_5, &uStack_2a, local_29);
        if (iVar3 != 0) {
            return iVar3;
        }
        unsigned char idx = local_29[0];
        int addr = iVar1 + (int)idx * 0x20;
        unsigned int d8 = *(volatile unsigned int *)(addr + 0xd8);
        unsigned int dc = *(volatile unsigned int *)(addr + 0xdc);
        unsigned int e0 = *(volatile unsigned int *)(addr + 0xe0);
        unsigned short e6 = *(volatile unsigned short *)(addr + 0xe6);
        unsigned int uVar7 = e0 + d8;
        unsigned int carry1 = (uVar7 < e0) ? 1u : 0u;
        unsigned int uVar6 = dc + carry1;
        uint64_t cand64;

        if (e6 == 0 && *(volatile unsigned short *)((char *)param_2 + 0xe) != 0) {
            unsigned int saved_e0 = e0;
            int r0a = FUN_010246d8();
            int r3v;
            if (r0a == 0x356) r3v = 0x1d;
            else if (r0a == 0x5f5) r3v = 0x33;
            else if (r0a == 0x18c) r3v = 0xe;
            else r3v = 1;

            if (r3v <= (int)saved_e0) {
                cand64 = ((uint64_t)uVar6 << 32) | uVar7;
            } else {
                int r0b = FUN_010246d8();
                unsigned int r2v;
                if (r0b == 0x356) r2v = 0x1d;
                else if (r0b == 0x5f5) r2v = 0x33;
                else if (r0b == 0x18c) r2v = 0xe;
                else r2v = 1;

                unsigned char idx2 = local_29[0];
                int addr2 = iVar1 + (int)idx2 * 0x20;
                unsigned int d8b = *(volatile unsigned int *)(addr2 + 0xd8);
                unsigned int dcb = *(volatile unsigned int *)(addr2 + 0xdc);
                unsigned int fp2 = r2v + d8b;
                unsigned int carry2 = (fp2 < r2v) ? 1u : 0u;
                unsigned int sl2 = dcb + carry2;
                cand64 = ((uint64_t)sl2 << 32) | fp2;

                if (new64 < cand64) {
                    return 0;
                }
                param_2[0] = fp2;
                param_2[1] = sl2;
                continue;
            }
        } else {
            cand64 = ((uint64_t)uVar6 << 32) | uVar7;
        }

        if (new64 < cand64) {
            return 0;
        }
        param_2[0] = uVar7;
        param_2[1] = uVar6;
    }
}

