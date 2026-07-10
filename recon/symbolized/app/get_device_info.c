#include "g1_app_symbols.h"
/* named: get_device_info */
/* globals referenced:
//   0x200069fc  device_info                  
*/
/* Reconstructed get_device_info @ 0x167a8  (parity: 300/300 trials, PROVEN) */

unsigned int get_device_info(void){
    return *(unsigned int*)((uintptr_t)&device_info) /*=0x200069fc*/;
}

