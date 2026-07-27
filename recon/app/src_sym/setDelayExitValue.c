/* Reconstructed setDelayExitValue @ 0x49000  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
unsigned int setDelayExitValue(unsigned int param_1){
    if(*(volatile int*)0x2000230cUL > 2){
        if(*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xb58 */==0){
            DEBUG_PRINT(0x000efb0eUL,0x000f01c1UL,param_1);
        } else {
            debug_print(0x000efb0eUL,0x000f01c1UL,param_1);
        }
    }
    *(volatile unsigned int*)0x2000a094UL = param_1;
    return 0;
}

