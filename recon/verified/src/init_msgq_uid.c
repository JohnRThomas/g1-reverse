/* Reconstructed init_msgq_uid @ 0x18e04  (parity: 300/300 trials, PROVEN) */

extern int FUN_00086448(unsigned int,int,int);
extern void DEBUG_PRINT(unsigned int,unsigned int);
extern void FUN_00019c70(void);
int init_msgq_uid(void){
    int iVar1 = FUN_00086448(0x20006a38UL,8,10);
    if(iVar1!=0 && *(volatile int*)0x2000230cUL>0){
        if(*(volatile unsigned int*)0x20007554UL==0){
            DEBUG_PRINT(0x0009a949UL,0x0009b182UL);
        } else { FUN_00019c70(); }
    }
    return iVar1;
}

