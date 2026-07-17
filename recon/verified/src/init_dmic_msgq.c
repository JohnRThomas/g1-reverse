/* Reconstructed init_dmic_msgq @ 0x2ebd8  (parity: 300/300 trials, PROVEN) */

extern int FUN_00086448(unsigned int,int,int);
extern void DEBUG_PRINT(unsigned int,unsigned int);
extern void FUN_00019c70(unsigned int,...);
int init_dmic_msgq(void){
    int iVar1 = FUN_00086448(0x20007b7cUL,200,8);
    if(iVar1!=0 && *(volatile int*)0x2000230cUL>0){
        if(*(volatile unsigned int*)0x20007554UL==0){
            DEBUG_PRINT(0x000a3ee4UL,0x000a41ffUL);
        } else { FUN_00019c70(0x000a3ee4UL,0x000a41ffUL); }
    }
    return iVar1;
}
