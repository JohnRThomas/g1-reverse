/* named: clean_dmic_msgq */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20007b7c  g_dmic_msgq                  
*/
/* Reconstructed clean_dmic_msgq @ 0x2ec1c  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_cleanup(unsigned int);
extern void DEBUG_PRINT(unsigned int,unsigned int);
extern void debug_print(void);
int clean_dmic_msgq(void){
    int iVar1 = k_msgq_cleanup(0x20007b7cUL);
    if(iVar1!=0 && *(volatile int*)0x2000230cUL > 0){
        if(*(volatile unsigned int*)0x20007554UL==0){
            DEBUG_PRINT(0x000a3efcUL,0x000a41efUL);
        } else {
            debug_print();
        }
    }
    return iVar1;
}

