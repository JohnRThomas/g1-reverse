/* Reconstructed FUN_00055bf8 @ 0x55bf8  (parity: 300/300 trials, PROVEN) */
extern int FUN_00053e74(void*, int);
extern long long thunk_FUN_00074f68(void);
extern int FUN_00080692(unsigned, void*, int, void*, int);
extern void FUN_0004d944(unsigned, int, void*, int);
int FUN_00055bf8(void){
    unsigned char auStack_30[36];
    unsigned local_50, uStack_4c, local_38, local_34;
    int iVar1 = FUN_00053e74(auStack_30, 0x20);
    if (iVar1 == 0){
        long long lVar3 = thunk_FUN_00074f68();
        unsigned long long prod = (unsigned long long)(lVar3 * 1000);
        uStack_4c = (unsigned)(prod >> 32);
        local_50 = ((unsigned)prod >> 0xf) | (uStack_4c << 17);
        uStack_4c = uStack_4c >> 0xf;
        int iVar2 = FUN_00080692(0x20006000, auStack_30, 0x20, &local_50, 8);
        if (iVar2 == 0){
            local_34 = 0xf394f;
            local_38 = 2;
            iVar1 = -5;
            FUN_0004d944(0x88148, 0x1040, &local_38, 0);
        }
    }
    (void)uStack_4c; (void)local_34;
    return iVar1;
}

