/* named: FUN_0007c6a0 */
/* Reconstructed FUN_0007c6a0 @ 0x7c6a0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int opt_node_value_len(int);
extern int opt_node_total_len(int);
extern int FUN_0007c5ba(int, void*);
extern int FUN_0007c670(int, void*, int);
extern void memcpy(int, int);

int FUN_0007c6a0(int param_1, int *param_2){
    if (param_1==0 || param_2==0 || *param_2==0) return 7;
    unsigned uVar6 = param_2[1];
    unsigned uVar1 = opt_node_total_len(0);
    if (uVar6 < uVar1){
        int iv = opt_node_total_len(param_1);
        param_2[1] = iv;
        return 1;
    }
    int local_30 = *param_2;
    int local_2c = param_2[1];
    volatile int lbuf[2];
    int iVar3 = FUN_0007c5ba(param_1, &local_30);
    int iVar2 = local_2c;
    if (iVar3 != 0) return iVar3;
    if (*(char*)(param_1+1) != 0){
        memcpy(*param_2 + local_2c, *(int*)(param_1+4));
        iVar2 = iVar2 + *(unsigned char*)(param_1+1);
    }
    if (*(char*)(param_1+2) != 0){
        memcpy(*param_2 + iVar2, *(int*)(param_1+8));
        iVar2 = iVar2 + *(unsigned char*)(param_1+2);
    }
    int iVar7 = *param_2;
    int iVar3b = param_2[1];
    uVar1 = opt_node_value_len(param_1);
    if ((unsigned)(iVar3b - iVar2) < uVar1){
        return 1;
    }
    int acc = 0;
    int uVar5 = 1;
    while (1){
        int iVar4 = FUN_0007c670(param_1, &lbuf[0], uVar5);
        if (iVar4 == 0) break;
        if (lbuf[1] != 0){
            memcpy(iVar2 + acc + iVar7, lbuf[0]);
        }
        uVar5 = 0;
        acc = acc + lbuf[1];
    }
    param_2[1] = iVar2 + acc;
    return 0;
}

