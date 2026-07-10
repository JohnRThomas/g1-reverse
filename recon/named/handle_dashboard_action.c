/* named: handle_dashboard_action */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20004950  g_dashboard_widget_state     
//   0x20007554  g_log_use_alt_sink           
//   0x2001b815  g_stocks_widget_index_raw    
*/
/* Reconstructed handle_dashboard_action @ 0x37108  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int);
extern void debug_print(unsigned int,unsigned int);
unsigned int handle_dashboard_action(unsigned char param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4){
    *(volatile unsigned char*)(0x20004950UL+3) = param_1;
    *(volatile unsigned char*)0x2001b815UL = param_1;
    if(*(volatile int*)0x2000230cUL > 2){
        if(*(volatile unsigned int*)0x20007554UL == 0){
            DEBUG_PRINT(0x000a8ff3UL, 0x000a95c9UL);
        } else {
            debug_print(0x000a8ff3UL, 0x000a95c9UL);
        }
    }
    return 0;
}

