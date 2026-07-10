#include "g1_app_symbols.h"
/* named: get_glassbox_charge_percent */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20019ef4  g_glassbox_charge_status_byte 
*/
/* Reconstructed get_glassbox_charge_percent @ 0x327c4  (parity: 300/300 trials, PROVEN) */
typedef unsigned char u8;typedef unsigned int u32;extern int DEBUG_PRINT();extern void debug_print(void);u8 get_glassbox_charge_percent(void){if(2<*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/){if(*(volatile u32*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/==0)DEBUG_PRINT();else debug_print();}return *(volatile u8*)((uintptr_t)&g_glassbox_charge_status_byte) /*=0x20019ef4*/ & 0x7f;}
