/* Reconstructed clean_dmic_msgq @ 0x2ec1c  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_cleanup(unsigned int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
int clean_dmic_msgq(void){
    int iVar1 = k_msgq_cleanup(0x20007b7cUL /* device_info+0x1180 (unnamed) */);
    if(iVar1!=0 && *(volatile int*)0x2000230cUL /* unknown global 0x2000230c */ > 0){
        if(*(volatile unsigned int*)0x20007554UL /* device_info.is_debug (+0xb58) */==0){
            DEBUG_PRINT(0x000a3efcUL,0x000a41efUL);
        } else {
            debug_print(0x000a3efcUL,0x000a41efUL);
        }
    }
    return iVar1;
}

