/* Reconstructed check_battery_critical @ 0x2bed0  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007cdf8(void);
unsigned int check_battery_critical(int param_1){
    volatile unsigned char *pcVar1 = (volatile unsigned char*)0x20018d9cUL /* unknown global 0x20018d9c */;
    while(*pcVar1 != 0){
        FUN_0007cdf8();
    }
    return (unsigned int)(1 < *(unsigned char*)(param_1+0xd5));
}

