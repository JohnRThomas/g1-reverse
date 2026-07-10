#include "g1_app_symbols.h"
/* named: get_glassbox_charge_status */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20019ef4  g_glassbox_charge_status_byte 
*/
/* Reconstructed get_glassbox_charge_status @ 0x32784  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int);
extern void debug_print(void);
unsigned char get_glassbox_charge_status(void){
    volatile unsigned char *pbVar1 = (volatile unsigned char*)((uintptr_t)&g_glassbox_charge_status_byte) /*=0x20019ef4*/;
    if(*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2){
        if(*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
            DEBUG_PRINT("%s(): bIsCharging is :%d \n\n" /*=0xa7411*/, "get_glassbox_charge_status" /*=0xa7751*/, (unsigned int)(*pbVar1 >> 7));
        } else {
            debug_print();
        }
    }
    return *pbVar1 >> 7;
}

