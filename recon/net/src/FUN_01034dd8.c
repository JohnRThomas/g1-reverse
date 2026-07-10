/* net-core FUN_01034dd8 @ 0x1034dd8  (parity 300 trials PROVEN) */

extern int FUN_01039bbe(int a, int b, int c);
extern void FUN_01039bb0(int a, int b) __attribute__((noreturn));

void FUN_01034dd8(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    if (param_1 == 0) {
        FUN_01039bbe(0x103d2a7, 0x103e700, 0x46);
        FUN_01039bb0(0x103e700, 0x46);
        return;
    }
    volatile unsigned char *p48 = (volatile unsigned char*)0x21004aec;
    if (p48[4] == 1) {
        volatile unsigned int *dst = (volatile unsigned int*)0x41012000;
        int iVar5;
        for (iVar5 = 0; iVar5 != 0x10; iVar5++) {
            unsigned int v = *(unsigned int*)(param_1 + iVar5 * 4);
            dst[iVar5 + 0x144] = v;
        }
        int iVar6;
        int *puVar4 = (int*)(param_1 + 0x3c);
        for (iVar6 = 0; iVar6 != 0x10; iVar6++) {
            puVar4++;
            unsigned int v = *puVar4;
            dst[iVar6 + 0x164] = v;
        }
        dst[0xc1] = *(unsigned int*)(param_1 + 0x80);
        return;
    }
    FUN_01039bbe(0x103d2a7, 0x103e700, 0x47);
    FUN_01039bb0(0x103e700, 0x47);
}

