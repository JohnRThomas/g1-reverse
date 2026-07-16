/* Reconstructed FUN_00057484 @ 0x57484  (parity: 300/300 trials, PROVEN) */
extern void FUN_00081746(unsigned,int,void*);
void FUN_00057484(int param_1){
    if (*(short*)(param_1 + 0x16) == 0){
        *(short*)(param_1 + 0x16) = 0x1f0;
    }
    unsigned uVar1 = *(unsigned short*)(param_1 + 0x16);
    unsigned uVar2 = uVar1;
    if (uVar1 >= 0x1f0) uVar2 = 0x1f0;
    *(short*)(param_1 + 0x18) = (short)(uVar2 + 2);
    if (*(int*)(*(int*)(param_1 + 4) + 0x10) == 0 && ((uVar2 + 2) & 0xffff) <= (uVar1 + 1)){
        unsigned local_10 = 2, local_c = 0xf3f11;
        (void)local_c;
        FUN_00081746(0x88160, 0x1080, &local_10);
        *(short*)(param_1 + 0x16) = *(short*)(param_1 + 0x18) - 2;
    }
    __atomic_exchange_n((unsigned int *)(param_1 + 0x1c), 1,
                        __ATOMIC_ACQ_REL);
}
