/* named: ipc_ept_op_b_locked_retry */
/* Reconstructed ipc_ept_op_b_locked_retry @ 0x257ec  (parity: 300/300 trials, PROVEN) */
extern void thunk_FUN_000723b8(unsigned,unsigned,unsigned,unsigned);
extern int json_arr_encode(int,unsigned,unsigned,int);
extern void thunk_FUN_00072558(unsigned);
extern void sleep_fixed_33_ticks(void);
extern void DEBUG_PRINT(unsigned,unsigned,unsigned,int);
int ipc_ept_op_b_locked_retry(int param_1, unsigned param_2, unsigned param_3, int param_4){
    int iVar1;
    if (param_4 == 0){ iVar1 = 0; }
    else {
        int iVar3 = 0x14;
        int iVar4 = *(int*)(param_1 + 4);
        unsigned uVar5 = *(unsigned*)(param_1 + 0x10);
        while (1){
            thunk_FUN_000723b8(uVar5, param_2, 0xffffffff, 0xffffffff);
            iVar1 = json_arr_encode(iVar4, param_2, param_3, param_4);
            thunk_FUN_00072558(uVar5);
            if (iVar1 == 0) break;
            iVar3 = iVar3 - 1;
            if (iVar3 == 0){
                DEBUG_PRINT(0x9f285, (*(unsigned short*)(iVar4 + 8)) | 4, param_2, iVar1);
                return iVar1;
            }
            sleep_fixed_33_ticks();
        }
    }
    return iVar1;
}

