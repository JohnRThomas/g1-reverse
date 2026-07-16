/* Reconstructed FUN_00071358 @ 0x71358  (parity: 300/300 trials, PROVEN) */
extern int FUN_00070e28(int a0,int a1,int a2,void *a3,void *a4);
extern int FUN_00070f74(int a0,int a1,int a2,int a3,int a4,int a5,int a6);
extern void FUN_0008557c(int *a0,unsigned int a1,int a2,int a3);
extern int FUN_0008567c(int a0,void *a1,int a2,int a3,int a4);
extern void FUN_000857b2(int a0);
extern int FUN_00085aee(int a0,int a1);
extern void FUN_00086534(int a0,int a1);
extern void FUN_00086c78(int a0,int a1,int a2);

typedef int (*fn1_t)(int);
typedef int (*fn2_t)(int,int);

int FUN_00071358(int param_1,int param_2,int param_3,int *param_4,int param_5,int *param_6)
{
    int uVar1, uVar3, iVar4, iVar6;
    unsigned int uVar2, uVar5;
    int local_38, local_34, local_30, local_2c, local_28, local_24;

    if (param_1 == 0) return (int)0xfffff82d;
    if (param_2 == 0) return (int)0xfffff82d;
    if (param_4 == (int*)0) return (int)0xfffff82d;

    FUN_00086c78(param_1, 0, 0x94);
    FUN_00086534(param_1 + 0x58, 1);
    uVar1 = 0x00071295;
    *(int*)(param_1 + 0xa0) = param_2;
    *(int*)(param_1 + 0x70) = param_3;
    *(int*)(param_2 + 0x24) = param_1;
    *(int*)(param_1 + 0x78) = uVar1;
    iVar6 = *(int*)(param_1 + 0xa0);
    *(int*)(param_1 + 0x7c) = 0x000859a3;
    *(int*)(param_1 + 0x80) = 0x00085a9d;
    *(int*)(param_1 + 0x84) = 0x00085b0d;
    *(int*)(param_1 + 0x88) = 0x000710b5;
    *(int*)(param_1 + 0x8c) = 0x000859c3;
    iVar4 = *(int*)(iVar6 + 0x18);
    if (iVar4 == 0) {
        if (param_6 == (int*)0) return (int)0xfffff82d;
        uVar1 = param_6[1];
        uVar3 = param_6[2];
        /* The firmware copies this descriptor in ascending word order with
         * one LDM/STM pair.  Keep that observable order even on a later
         * faulting path; ordinary stores may be freely reordered by C. */
        *(volatile int*)(param_1 + 0x94) = *param_6;
        *(volatile int*)(param_1 + 0x98) = uVar1;
        *(volatile int*)(param_1 + 0x9c) = uVar3;
    }
    {
        fn1_t fp = *(fn1_t*)((*(int*)(iVar6 + 0x20)) + 0x10);
        uVar1 = fp(iVar6);
    }
    *(int*)(param_2 + 0x10) = uVar1;
    *(int*)(param_2 + 0x14) = 0;
    *(unsigned char*)(param_1 + 0x90) = (unsigned char)((unsigned int)uVar1 & 1);
    if (iVar4 == 0) {
        iVar6 = param_5;
        if (*(char*)(param_6 + 2) != 0) iVar6 = param_5 + 0xc;
        *(int*)(param_1 + 0xb0) = iVar6;
        if (param_5 == 0) return (int)0xfffff82d;
        if (*(int*)(param_5 + 8) == 0) return (int)0xfffff82e;
        if (*(int*)(iVar6 + 8) == 0) return (int)0xfffff82e;
        local_38 = 0x000f7c28;
        local_34 = 0x000f7c2e;
        local_30 = 0x0007118d;
        local_2c = 0x000859b1;
        *(int*)(param_1 + 0xa4) = **(int**)(param_2 + 0x2c);
        *(int*)(param_1 + 0xa8) = *(int*)(*(int*)(param_2 + 0x2c) + 0x18);
    }
    *(int*)(param_1 + 0xb4) = param_1 + 0xb4;
    *(int*)(param_1 + 0xb8) = param_1 + 0xb4;
    *(int**)(param_1 + 0xac) = param_4;
    iVar6 = FUN_00070e28(*(int*)(param_1 + 0xa0), 0, 2, &local_38, &local_30);
    if (iVar6 != 0) return iVar6;
    FUN_000857b2(*(int*)(param_1 + 0xa8));
    *(int**)(**(int**)(param_2 + 0x2c) + 0x28) = param_4;
    *(int**)(*(int*)(*(int*)(param_2 + 0x2c) + 0x18) + 0x28) = param_4;
    if (iVar4 == 0) {
        local_24 = *(int*)(param_1 + 0x98);
        (void)local_24;
        for (uVar5 = 0; uVar5 < *(unsigned short*)(*(int*)(param_1 + 0xa4) + 0xa); uVar5 = uVar5 + 1) {
            iVar6 = FUN_00085aee(param_5, *(int*)(param_1 + 0x98));
            if (iVar6 == 0) return (int)0xfffff82e;
            uVar2 = (unsigned int)iVar6 - (unsigned int)(*param_4);
            if ((unsigned int)param_4[2] <= uVar2) uVar2 = 0xffffffff;
            local_28 = iVar6;
            FUN_0008557c(param_4, uVar2, 0, *(int*)(param_1 + 0x98));
            iVar6 = FUN_0008567c(*(int*)(param_1 + 0xa4), &local_28, 0, 1, iVar6);
            if (iVar6 != 0) return iVar6;
        }
        *(int*)param_1 = param_1;
        *(int*)(param_1 + 4) = param_1;
        if (*(char*)(param_1 + 0x90) == 0) goto LAB_00071498;
    } else {
        *(int*)param_1 = param_1;
        *(int*)(param_1 + 4) = param_1;
        if (*(char*)(param_1 + 0x90) == 0) return 0;
    }
    FUN_00070f74(param_1, param_1 + 8, 0x000f7c34, 0x35, 0x35, 0x00085a05, 0);
    if (iVar4 != 0) return 0;
LAB_00071498:
    {
        fn2_t fp2 = *(fn2_t*)((*(int*)(*(int*)(param_1 + 0xa0) + 0x20)) + 0xc);
        fp2(*(int*)(param_1 + 0xa0), 4);
    }
    return 0;
}
