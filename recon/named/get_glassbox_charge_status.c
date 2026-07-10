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
    volatile unsigned char *pbVar1 = (volatile unsigned char*)0x20019ef4UL;
    if(*(volatile int*)0x2000230cUL > 2){
        if(*(volatile unsigned int*)0x20007554UL == 0){
            DEBUG_PRINT(0x000a7411UL, 0x000a7751UL, (unsigned int)(*pbVar1 >> 7));
        } else {
            debug_print();
        }
    }
    return *pbVar1 >> 7;
}

