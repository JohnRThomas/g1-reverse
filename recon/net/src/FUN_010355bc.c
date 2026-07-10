/* net-core FUN_010355bc @ 0x10355bc  (parity 300 trials PROVEN) */

extern int FUN_010353ec(unsigned int, unsigned int, unsigned int);
extern void FUN_01039bb0(unsigned int, unsigned int);
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);
extern int FUN_0103ab0e(void *, unsigned int, void *, unsigned int);
extern unsigned int FUN_0103ac46(unsigned int, unsigned int);
extern void FUN_0103acca(unsigned int);
extern void FUN_0103aec6(void *);
extern void FUN_0103aec2(void *);

unsigned int FUN_010355bc(int param_1, unsigned int param_2, unsigned int param_3, int param_4, unsigned int param_5)
{
    unsigned int uVar5 = *(volatile unsigned int *)(param_4 - 8);
    volatile int *piVar1 = *(volatile int **)(param_1 + 0xac);
    unsigned int local_buf[8];
    unsigned int uVar4;
    unsigned int panic_code;
    int iVar2b;

    unsigned int uVar3 = (unsigned int)(param_4 - 0x10) - piVar1[0];
    if ((unsigned int)piVar1[2] <= uVar3) {
        uVar3 = 0xffffffff;
    }

    int iVar2 = FUN_0103ab0e((void *)piVar1, uVar3, local_buf, 0x10);
    uVar5 = uVar5 & 0xffff;

    if (iVar2 == 0x10) goto L_612;

    FUN_01039bbe(0x0103d2a7, 0x0103e889, 0x1af);
    panic_code = 0x1af;
    goto L_term;

L_term:
    FUN_01039bb0(0x0103e889, panic_code);
    /* falls through to success-path code physically */

L_612:
    FUN_0103aec6((void *)(param_1 + 0x58));
    uVar4 = FUN_0103ac46(*(volatile unsigned int *)(param_1 + 0xa8), uVar5);
    if (*(volatile int *)(*(volatile int *)(param_1 + 0xa0) + 0x18) != 1) {
        goto L_success;
    }
    iVar2b = FUN_010353ec(*(volatile unsigned int *)(param_1 + 0xa8), uVar5, uVar4);
    if (iVar2b == 0) goto L_success;

    FUN_01039bbe(0x0103d2a7, 0x0103e889, 0x1bc);
    panic_code = 0x1bc;
    goto L_term;

L_success:
    FUN_0103acca(*(volatile unsigned int *)(param_1 + 0xa8));
    FUN_0103aec2((void *)(param_1 + 0x58));
    return param_5;
}

