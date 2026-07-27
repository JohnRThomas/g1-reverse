/* Reconstructed FUN_00025850 @ 0x25850  (parity: 300/300 trials, PROVEN) */
extern void FUN_0007c872(unsigned,unsigned,unsigned,unsigned);
extern int FUN_0007c882(int,unsigned,unsigned,int);
extern void FUN_0007c876(unsigned);
extern unsigned long long FUN_0007c87a(void);
extern void DEBUG_PRINT(unsigned long, ...);
int FUN_00025850(int param_1, unsigned param_2, unsigned param_3, int param_4){
    int iVar1;
    if (param_4 == 0){ iVar1 = 0; }
    else {
        int iVar3 = 0x14;
        int iVar4 = *(int*)(param_1 + 4);
        unsigned uVar5 = *(unsigned*)(param_1 + 0x10);
        unsigned lock_arg = param_2;
        while (1){
            FUN_0007c872(uVar5, lock_arg, 0xffffffff, 0xffffffff);
            iVar1 = FUN_0007c882(iVar4, param_2, param_3, param_4);
            FUN_0007c876(uVar5);
            if (iVar1 == 0) break;
            iVar3 = iVar3 - 1;
            if (iVar3 == 0){
                DEBUG_PRINT(0x9f2be, (*(unsigned short*)(iVar4 + 8)) | 4, param_2, iVar1);
                return iVar1;
            }
            lock_arg = (unsigned)(FUN_0007c87a() >> 32);
        }
    }
    return iVar1;
}
