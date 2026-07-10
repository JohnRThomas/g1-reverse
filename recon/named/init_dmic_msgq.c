/* named: init_dmic_msgq */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20007b7c  g_dmic_msgq                  
*/
/* Reconstructed init_dmic_msgq @ 0x2ebd8  (parity: 300/300 trials, PROVEN) */

extern int z_impl_k_msgq_alloc_init(unsigned int,int,int);
extern void DEBUG_PRINT(unsigned int,unsigned int);
extern void debug_print(void);
int init_dmic_msgq(void){
    int iVar1 = z_impl_k_msgq_alloc_init(0x20007b7cUL,200,8);
    if(iVar1!=0 && *(volatile int*)0x2000230cUL>0){
        if(*(volatile unsigned int*)0x20007554UL==0){
            DEBUG_PRINT(0x000a3ee4UL,0x000a41ffUL);
        } else { debug_print(); }
    }
    return iVar1;
}

