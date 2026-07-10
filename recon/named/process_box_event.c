/* named: process_box_event */
/* globals referenced:
//   0x20007a24  g_box_field_timer            
*/
/* Reconstructed process_box_event @ 0x254d8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0007c830(int);
extern int get_device_info(void);
extern void FUN_0002538c(int,char*);
void process_box_event(int param_1, char* param_2){
    FUN_0007c830(param_1+8);
    *(volatile uint32_t*)0x20007a24 = *(volatile uint32_t*)(param_1+8);
    int iVar4;
    iVar4=get_device_info(); *(volatile uint8_t*)(param_2+0x15)=(uint8_t)((*(volatile uint8_t*)(iVar4+0xfc4)+0xc8)>>8);
    iVar4=get_device_info(); *(volatile uint8_t*)(param_2+0x13)=*(volatile uint8_t*)(iVar4+0xfc0);
    iVar4=get_device_info(); *(volatile uint8_t*)(param_2+0x34)=*(volatile uint8_t*)(iVar4+0xfc0);
    get_device_info();
    *(volatile uint8_t*)(param_2+2)=0;
    FUN_0002538c(param_1,param_2);
}

