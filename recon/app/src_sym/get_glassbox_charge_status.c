/* Reconstructed get_glassbox_charge_status @ 0x32784  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int);
extern void debug_print(void);
unsigned char get_glassbox_charge_status(void){
    volatile unsigned char *pbVar1 = (volatile unsigned char*)0x20019ef4UL;
    if(*(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */ > 2){
        if(*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0){
            DEBUG_PRINT(0x000a7411UL, 0x000a7751UL, (unsigned int)(*pbVar1 >> 7));
        } else {
            debug_print();
        }
    }
    return *pbVar1 >> 7;
}

