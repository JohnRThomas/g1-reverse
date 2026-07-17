/* Reconstructed get_glassbox_charge_status @ 0x32784  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int,unsigned int);
extern void FUN_00019c70(unsigned int,unsigned int,unsigned int,unsigned int);
unsigned char get_glassbox_charge_status(void){
    volatile unsigned char *pbVar1 = (volatile unsigned char*)0x20019ef4UL;
    if(*(volatile int*)0x2000230cUL > 2){
        unsigned int sink = *(volatile unsigned int*)0x20007554UL;
        if(sink == 0){
            DEBUG_PRINT(0x000a7411UL, 0x000a7751UL,
                        (unsigned int)(*pbVar1 >> 7),sink);
        } else {
            FUN_00019c70(0x000a7411UL, 0x000a7751UL,
                         (unsigned int)(*pbVar1 >> 7),sink);
        }
    }
    return *pbVar1 >> 7;
}
