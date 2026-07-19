#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00016940 @ 0x00016940
 * public-name: get_current_work_mode
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   device_info                              @ 0x200069fc
 */
/* Reconstructed get_current_work_mode @ 0x16940  (parity: 300/300 trials, PROVEN) */
typedef unsigned char u8;typedef unsigned int u32;u8 get_current_work_mode(void){return *(volatile u8*)((*(volatile u32*)((unsigned long)&device_info) /*=0x200069fc*/)+1);}
