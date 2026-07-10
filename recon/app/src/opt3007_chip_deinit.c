/* Reconstructed opt3007_chip_deinit @ 0x2e8b4  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void FUN_00019c70(void);
void opt3007_chip_deinit(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4){
    unsigned int v = *(volatile unsigned int*)0x20007b6cUL;
    if(v != 0){
        param_3 = 0;
        *(volatile unsigned int*)(v + 0x10) = 0;
    }
    if(*(volatile int*)0x2000230cUL > 2){
        if(*(volatile unsigned int*)0x20007554UL==0){
            DEBUG_PRINT(0x000a3cb9UL,0x000a3cdaUL,param_3,0,param_4);
        } else {
            FUN_00019c70();
        }
    }
    *(volatile unsigned char*)0x20018da1UL = 0;
}

