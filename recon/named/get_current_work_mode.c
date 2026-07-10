/* named: get_current_work_mode */
/* globals referenced:
//   0x200069fc  device_info                  
*/
/* Reconstructed get_current_work_mode @ 0x16940  (parity: 300/300 trials, PROVEN) */
typedef unsigned char u8;typedef unsigned int u32;u8 get_current_work_mode(void){return *(volatile u8*)((*(volatile u32*)0x200069fcUL)+1);}
