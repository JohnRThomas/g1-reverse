/* Reconstructed init_dmic_msgq @ 0x2ebd8  (parity: 300/300 trials, PROVEN) */

extern int z_impl_k_msgq_alloc_init(unsigned int,int,int);
extern void DEBUG_PRINT(unsigned int,unsigned int);
extern void debug_print(void);
int init_dmic_msgq(void){
    int iVar1 = z_impl_k_msgq_alloc_init(0x20007b7cUL /* device_info+0x1180 (k_msgq: dmic audio queue object) */,200,8);
    if(iVar1!=0 && *(volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */>0){
        if(*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */==0){
            DEBUG_PRINT(0x000a3ee4UL,0x000a41ffUL);
        } else { debug_print(); }
    }
    return iVar1;
}

