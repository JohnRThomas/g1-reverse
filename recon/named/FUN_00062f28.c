/* named: FUN_00062f28 */
/* Reconstructed FUN_00062f28 @ 0x62f28  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00074844(int,int);
extern void FUN_0008496c(int,int,int);
extern unsigned long long is_tx_ready(int,...);
extern int k_is_in_isr(void);
extern void thunk_FUN_00086384(int);

void FUN_00062f28(int param_1, unsigned char param_2){
    int iVar6 = *(int*)(param_1+0x10);
    int *piVar7 = 0;
    int iVar3 = k_is_in_isr();
    if (iVar3 != 0 || *(char*)0x2001d564 == 0){
        while (1){
            piVar7 = *(int**)(param_1+4);
            unsigned long long uVar8 = is_tx_ready((int)(intptr_t)piVar7, 0);
            if ((int)uVar8 != 0) break;
        }
        iVar3 = *(int*)(iVar6+0xc);
        if (iVar3 != 0 && *(int*)(iVar3+0xc) != 0 && *(int*)(iVar3+0xbc) < 0){
            *(int*)(iVar3+0xbc) = *(int*)(*piVar7+0x54c);
        }
        goto LAB;
    }
    do {
        int cnt = 100;
        do {
            int iVar4 = (int)is_tx_ready(*(int*)(param_1+4));
            if (iVar4 != 0){
                unsigned long long uVar8 = is_tx_ready(*(int*)(param_1+4), 0);
                if ((int)uVar8 != 0) goto LAB;
                break;
            }
            thunk_FUN_00086384(1);
            cnt = cnt - 1;
        } while (cnt != 0);
        FUN_00074844(0x21, 0);
    } while (1);
  LAB:
    *(*(unsigned char**)(iVar6+0x14)) = param_2;
    FUN_0008496c(param_1, *(int*)(iVar6+0x14), 1);
}

