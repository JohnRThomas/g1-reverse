/* Reconstructed sett_init @ 0x22518  (parity: 300/300 trials, PROVEN) */

extern int FUN_0004e744(void);
extern int FUN_0004e494(unsigned int);
extern void FUN_0007dda4(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

void sett_init(int *param_1)
{
    int iVar2;
    volatile int *piVar1;
    unsigned int format_string;
    int iVar3;

    iVar2 = FUN_0004e744();
    piVar1 = (volatile int*)0x2000230cUL;
    if (iVar2 == 0) {
        iVar2 = FUN_0004e494(0x20002368UL);
        if (iVar2 == 0) {
            if (1 < *piVar1) {
                if (*(volatile unsigned int*)0x20007554UL == 0) {
                    FUN_0007dda4(0x9e2cb, 0x9e549);
                } else {
                    FUN_00019c70(0x9e2cb, 0x9e549);
                }
            }
            iVar2 = 1;
            goto LAB;
        }
        if (*piVar1 < 2) goto LAB;
        iVar3 = *(volatile int*)0x20007554UL;
        format_string = 0x9e2a0;
    } else {
        if (*piVar1 < 2) goto LAB;
        iVar3 = *(volatile int*)0x20007554UL;
        format_string = 0x9e266;
    }
    if (iVar3 == 0) {
        FUN_0007dda4(format_string, 0x9e549, iVar2);
    } else {
        FUN_00019c70(format_string, 0x9e549, iVar2);
    }
LAB:
    param_1[0] = iVar2;
    param_1[1] = 0x22169;
    param_1[2] = 0x7c26b;
    param_1[3] = 0x22121;
}
