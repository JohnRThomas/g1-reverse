/* Reconstructed clean_dmic_msgq @ 0x2ec1c  (parity: 300/300 trials, PROVEN) */

extern int FUN_00086480(unsigned int);
extern void DEBUG_PRINT(unsigned int,unsigned int);
extern void FUN_00019c70(void);
int clean_dmic_msgq(void){
    int iVar1 = FUN_00086480(0x20007b7cUL);
    if(iVar1!=0 && *(volatile int*)0x2000230cUL > 0){
        if(*(volatile unsigned int*)0x20007554UL==0){
            DEBUG_PRINT(0x000a3efcUL,0x000a41efUL);
        } else {
            FUN_00019c70();
        }
    }
    return iVar1;
}

