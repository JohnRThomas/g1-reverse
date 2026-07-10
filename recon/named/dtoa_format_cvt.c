/* named: dtoa_format_cvt */
/* Reconstructed dtoa_format_cvt @ 0x86cda  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern char* FUN_00014b60(double, uint32_t, int, int, int*, void*, void*);
extern int __aeabi_dcmpeq(uint32_t,int,int,int);

char* dtoa_format_cvt(double in_d0, uint32_t param_1, int param_2, uint32_t param_3,
                   uint8_t* param_4, int* param_5, uint32_t param_6, int* param_7){
    union { double d; uint32_t w[2]; } U; U.d = in_d0;
    uint32_t lo = U.w[0], hi = U.w[1];
    int iVar6 = (int)hi;
    uint32_t uVar3 = param_3;
    int iVar5 = iVar6;
    int neg = ((int)hi < 0);
    union { uint32_t w[2]; double d; } A; A.w[0]=lo; A.w[1]= neg ? (hi - 0x80000000U) : hi;
    double dabs = A.d;
    uint8_t uVar4;
    if (neg){ iVar5 = iVar6 - 0x80000000; uVar3 = lo; }
    if (neg){ uVar4 = 0x2d; } else { uVar4 = 0; iVar5 = iVar6; uVar3 = lo; }
    *param_4 = uVar4;
    uint32_t uVar8 = param_6 & 0xffffffdf;
    int uVar2;
    if (uVar8 == 0x46) uVar2 = 3;
    else { if (uVar8 == 0x45) param_2 = param_2 + 1; uVar2 = 2; }
    uint32_t auStack_30; char* local_2c[2];
    char* pcVar1 = FUN_00014b60(dabs, param_1, uVar2, param_2, param_5, &auStack_30, local_2c);
    char* pcVar7;
    if (param_6 == 0x67 || param_6 == 0x47){
        if ((param_3 & 1) == 0) goto L_d5e;
        pcVar7 = pcVar1 + param_2;
    } else {
        pcVar7 = pcVar1 + param_2;
        if (uVar8 == 0x46){
            if (*pcVar1 == '0' && __aeabi_dcmpeq(uVar3, iVar5, 0, 0) == 0){
                *param_5 = 1 - param_2;
            }
            pcVar7 = pcVar7 + *param_5;
        }
    }
    if (__aeabi_dcmpeq(uVar3, iVar5, 0, 0) != 0){
        local_2c[0] = pcVar7;
    }
    while ((uintptr_t)local_2c[0] < (uintptr_t)pcVar7){ *local_2c[0] = '0'; local_2c[0] = local_2c[0] + 1; }
  L_d5e:
    *param_7 = (int)(uintptr_t)local_2c[0] - (int)(uintptr_t)pcVar1;
    return pcVar1;
}

