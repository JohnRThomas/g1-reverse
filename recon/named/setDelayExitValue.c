/* named: setDelayExitValue */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x2000a094  g_delay_exit_value           [g_obj_2000a018.f_7c]
*/
/* Reconstructed setDelayExitValue @ 0x49000  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int);
extern void debug_print(void);
unsigned int setDelayExitValue(unsigned int param_1){
    if(*(volatile int*)0x2000230cUL > 2){
        if(*(volatile unsigned int*)0x20007554UL==0){
            DEBUG_PRINT(0x000efb0eUL,0x000f01c1UL,param_1);
        } else {
            debug_print();
        }
    }
    *(volatile unsigned int*)0x2000a094UL = param_1;
    return 0;
}

