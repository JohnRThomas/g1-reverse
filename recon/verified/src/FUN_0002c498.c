/* Reconstructed FUN_0002c498 @ 0x2c498  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned char undefined1;
extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_0002bc2c(unsigned a, byte *b, uint c);
extern void FUN_0002bffc(byte *a, int b, int c);
extern void FUN_0002c0e8(byte *a);
extern void FUN_0002c180(void);
extern void FUN_0002c1fc(void);
extern void FUN_0002c224(int a);
extern unsigned char FUN_0002c30c(byte a, int b);
extern void FUN_00033d58(int a);
extern int FUN_00033c4c(int a);
extern void FUN_0003439c(void);
extern void FUN_0003443c(int a);
extern void FUN_00036030(void);
extern void sync_to_slave(byte *a, int b, int c);
extern void FUN_0007ce5c(int a, int b);

undefined1 FUN_0002c498(byte *param_1, int param_2, char *param_3, unsigned *param_4)
{
    volatile int *piVar1 = (volatile int *)0x2000230c;
    volatile int *piVar2 = (volatile int *)0x20007554;
    undefined1 uVar3;
    int iVar4, iVar6;
    int *piVar5;
    char cVar7;
    uint uVar8, uVar9;
    int bVar10;

    uVar3 = FUN_0002c30c(param_1[0xfea], 0xf);
    *(volatile undefined1 *)(param_2 + 7) = uVar3;
    FUN_0003443c(2);
    iVar4 = FUN_000167a8();
    uVar9 = 0;
    piVar5 = (int *)FUN_00033c4c(*(volatile byte *)(iVar4 + 0xdd) - 1);
    iVar4 = *piVar5;
    do {
        if (((param_1[1] == 1) || (iVar6 = FUN_000167a8(), *(volatile char *)(iVar6 + 1) == '\b')) ||
            (iVar6 = FUN_000167a8(), *(volatile char *)(iVar6 + 0xfea) == '\f')) {
            if (2 < *piVar1) {
                if (*piVar2 == 0) DEBUG_PRINT(0x000a2768u, 0x000a39efu, (uint)*(volatile byte *)(param_2 + 1), *piVar2);
                else FUN_00019c70(0x000a2768u, 0x000a39efu, (uint)*(volatile byte *)(param_2 + 1), *piVar2);
            }
            FUN_0002c0e8(param_1);
            *param_4 = 0xa2795;
            goto LAB_0002c4ec;
        }
        iVar6 = iVar4;
        if (*param_1 == 1) {
            iVar6 = FUN_000167a8();
            piVar5 = (int *)FUN_00033c4c(*(volatile byte *)(iVar6 + 0xdd) - 1);
            iVar6 = *piVar5;
            if (iVar6 != iVar4) {
                uVar3 = FUN_0002c30c(param_1[0xfea], 0xf);
                *(volatile undefined1 *)(param_2 + 7) = uVar3;
            }
        }
        if (*(volatile char *)(param_2 + 1) != '\x05') {
            if (*piVar1 < 1) return 0xb;
            if (*piVar2 != 0) { FUN_00019c70(0x000a27b1u, 0x000a39efu, (uint)*(volatile byte *)(param_2 + 1), *piVar2); return 0xb; }
            DEBUG_PRINT(0x000a27b1u, 0x000a39efu, (uint)*(volatile byte *)(param_2 + 1), *piVar2);
            return 0xb;
        }
        if ((*param_3 == '\x02') || (param_1[0xfea] == 0xb)) {
            if (2 < *piVar1) { if (*piVar2 == 0) DEBUG_PRINT(0, 0); else FUN_00019c70(0, 0); }
            FUN_00036030();
            if (2 < *piVar1) { if (*piVar2 == 0) DEBUG_PRINT(0, 0); else FUN_00019c70(0, 0); }
            if (param_1[0xb0d] == 1) {
                FUN_0002bffc(param_1, 8, 2);
                FUN_0003443c(4);
                return 0xb;
            }
            if ((*(volatile char *)(param_2 + 1) == '\x05') && (uVar8 = (uint)*param_1, uVar8 == 1)) {
                FUN_0002c224(1);
                FUN_00033d58(0);
                FUN_0002c1fc();
                FUN_0003439c();
                FUN_0002bffc(param_1, 4, 2);
                FUN_0002bc2c(0xa0a7b, param_1, uVar8);
                if (*piVar1 < 1) return 0xb;
                if (*piVar2 != 0) { FUN_00019c70(0); return 0xb; }
                DEBUG_PRINT(0, 0);
                return 0xb;
            }
        }
        uVar9 = uVar9 + 1;
        if (((uVar9 & 0xf) == 0) && (2 < *piVar1)) {
            if (*piVar2 == 0) DEBUG_PRINT(0, 0, (uint)*(volatile byte *)(param_2 + 7));
            else FUN_00019c70(0, 0, (uint)*(volatile byte *)(param_2 + 7));
        }
        FUN_0007ce5c(0x667, 0);
        if (*param_1 == 1) {
            uVar8 = uVar9 * -0x33333333;
            bVar10 = (uVar8 >> 2 | uVar9 * 0x40000000) <= 0xccccccc;
            if (bVar10) uVar8 = (uint)*(volatile byte *)(param_2 + 7);
            cVar7 = (char)uVar8;
            if (bVar10) cVar7 = cVar7 + -1;
            if (bVar10) *(volatile char *)(param_2 + 7) = cVar7;
        }
        iVar4 = iVar6;
    } while (*(volatile char *)(param_2 + 7) != '\0');
    param_1[0xb0d] = 0;
    uVar3 = 0;
    if (*(volatile char *)(param_2 + 7) == '\0') {
        if (2 < *piVar1) { if (*piVar2 == 0) DEBUG_PRINT(0, 0, (uint)*(volatile byte *)(param_2 + 1)); else FUN_00019c70(0, 0, (uint)*(volatile byte *)(param_2 + 1)); }
        *param_4 = 0xa28d4;
        sync_to_slave(param_1, 8, 0);
        if (*param_3 == '\x02') FUN_0002c180();
        else FUN_0002c0e8(param_1);
        FUN_0003443c(6);
LAB_0002c4ec:
        uVar3 = 10;
    }
    return uVar3;
}
