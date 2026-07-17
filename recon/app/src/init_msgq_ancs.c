/* Reconstructed init_msgq_ancs @ 0x18b6c  (parity: 300/300 trials, PROVEN) */

extern int FUN_00086448(unsigned int,int,int);
extern void DEBUG_PRINT(unsigned int,unsigned int);
extern void FUN_00019c70(unsigned int,...);
int init_msgq_ancs(void){
    int iVar1 = FUN_00086448(0x20006a6cUL,0x1b4,10);
    if(iVar1!=0 && *(volatile int*)0x2000230cUL>0){
        if(*(volatile unsigned int*)0x20007554UL==0){
            DEBUG_PRINT(0x0009a949UL,0x0009b1aaUL);
        } else { FUN_00019c70(0x0009a949UL,0x0009b1aaUL); }
    }
    return iVar1;
}
