/* Reconstructed navigation_direction_img_display @ 0x3dff8  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007d3ee(void);
extern int FUN_0007d446(void);
extern void FUN_00043484(int a, int b, int c, int d, int e, int f, int g);
extern void FUN_00019c70(unsigned long, ...);
extern void DEBUG_PRINT(unsigned long, ...);

void navigation_direction_img_display(int param_1, int param_2, int param_3)
{
    unsigned int uVar1;
    int iVar2;

    if ((unsigned int)(param_1 - 1) < 0x23) {
        uVar1 = FUN_0007d3ee();
        iVar2 = FUN_0007d446();
        FUN_00043484(param_1 + 0x55, uVar1, iVar2 + 0x39, 0, 0, 0, param_3);
    } else if (1 < *(volatile int *)0x2000230cUL) {
        if (*(volatile int *)0x20007554UL != 0) {
            FUN_00019c70(0xa9e91, 0xaa466);
        } else {
            DEBUG_PRINT(0xa9e91, 0xaa466);
        }
    }
}
