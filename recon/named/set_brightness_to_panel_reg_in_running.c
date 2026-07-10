/* named: set_brightness_to_panel_reg_in_running */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed set_brightness_to_panel_reg_in_running @ 0x47058  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void DEBUG_PRINT();
extern int get_device_info(void);
extern void debug_print(void);
extern void panel_write_xy_reg_cached(int,int);
extern void projector_send_cmd1(int,int);
extern void thunk_FUN_0007d77c(int);
extern void delay_ms(int);
void set_brightness_to_panel_reg_in_running(uint param_1){
    if(*(volatile int*)0x2000230c > 2){
        if(*(volatile int*)0x20007554 == 0) DEBUG_PRINT(); else debug_print();
    }
    int iVar2=get_device_info();
    if(*(volatile int*)(iVar2+0xec8)==0) return;
    short sVar4=0; uint uVar5=0;
    if(param_1>5){
        iVar2=get_device_info();
        sVar4=(short)((*(volatile short*)(iVar2+0xed8)+1)*0x6f);
        uVar5=(param_1-6)&0xff;
    } else {
        iVar2=get_device_info();
        uint64_t uVar1=((uint64_t)*(volatile uint16_t*)(iVar2+0xed8)<<1)/9;
        int iv=(int)uVar1;
        int need96=(iv==0);
        if(!need96){
            int iVar3=get_device_info();
            if(*(volatile uint16_t*)(iVar3+0xed8)<6) need96=1;
            else{ iVar3=get_device_info();
                sVar4=(short)((short)(((int)(param_1*((uint)*(volatile uint16_t*)(iVar3+0xed8)-iv))/6)+(short)uVar1)*0x6f); }
        }
        if(need96){ iVar2=get_device_info();
            sVar4=(short)(((short)((param_1*0x6f)/6)+1)*(*(volatile short*)(iVar2+0xed8)+1)); }
        uVar5=0;
    }
    thunk_FUN_0007d77c(6); thunk_FUN_0007d77c(0xa9);
    panel_write_xy_reg_cached(sVar4,uVar5); projector_send_cmd1(0x31,4);
    thunk_FUN_0007d77c(0xa3); thunk_FUN_0007d77c(0x97);
    delay_ms(1);
}

