/* named: init_msgq_uid */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20006a38  g_uid_pipe                   
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed init_msgq_uid @ 0x18e04  (parity: 300/300 trials, PROVEN) */

extern int z_impl_k_msgq_alloc_init(unsigned int,int,int);
extern void DEBUG_PRINT(unsigned int,unsigned int);
extern void debug_print(void);
int init_msgq_uid(void){
    int iVar1 = z_impl_k_msgq_alloc_init(0x20006a38UL,8,10);
    if(iVar1!=0 && *(volatile int*)0x2000230cUL>0){
        if(*(volatile unsigned int*)0x20007554UL==0){
            DEBUG_PRINT(0x0009a949UL,0x0009b182UL);
        } else { debug_print(); }
    }
    return iVar1;
}

