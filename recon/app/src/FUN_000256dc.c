/* Reconstructed FUN_000256dc @ 0x256dc  (parity: 300/300 trials, PROVEN) */
extern void thunk_FUN_000723b8(unsigned,unsigned,unsigned,unsigned,int,unsigned);
extern int FUN_00025670(int,unsigned,unsigned,unsigned,int);
extern void thunk_FUN_00072558(unsigned);
extern unsigned long long FUN_0007c87a(void);
extern void DEBUG_PRINT(unsigned,unsigned,unsigned,int);
int FUN_000256dc(int param_1, unsigned param_2, unsigned param_3, int param_4){
    int iVar1;
    if (param_4 == 0){ iVar1 = 0; }
    else {
        int iVar4 = 0x14;
        int iVar3 = *(int*)(param_1 + 4);
        unsigned uVar5 = *(unsigned*)(param_1 + 0x10);
        unsigned lock_arg = param_2;
        while (1){
            thunk_FUN_000723b8(uVar5, lock_arg, 0xffffffff, 0xffffffff, param_1, param_2);
            iVar1 = FUN_00025670(iVar3, *(unsigned short*)(iVar3 + 8), param_2, param_3, param_4);
            thunk_FUN_00072558(uVar5);
            if (iVar1 == 0) break;
            iVar4 = iVar4 - 1;
            if (iVar4 == 0){
                DEBUG_PRINT(0x9f203, *(unsigned short*)(iVar3 + 8), param_2, iVar1);
                return iVar1;
            }
            lock_arg = (unsigned)(FUN_0007c87a() >> 32);
        }
    }
    return iVar1;
}
