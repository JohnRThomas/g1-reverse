/* Reconstructed init_msgq_ancs @ 0x18b6c  (parity: 300/300 trials, PROVEN) */

extern int z_impl_k_msgq_alloc_init(unsigned int,int,int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);
int init_msgq_ancs(void){
    int iVar1 = z_impl_k_msgq_alloc_init(0x20006a6cUL /* device_info+0x070  (k_msgq: ANCS notification queue object) */,0x1b4,10);
    if(iVar1!=0 && *(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */>0){
        if(*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */==0){
            DEBUG_PRINT(0x0009a949UL,0x0009b1aaUL);
        } else { debug_print(0x0009a949UL,0x0009b1aaUL); }
    }
    return iVar1;
}

