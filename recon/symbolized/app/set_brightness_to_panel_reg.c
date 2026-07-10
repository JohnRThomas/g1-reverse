#include "g1_app_symbols.h"
/* named: set_brightness_to_panel_reg */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed set_brightness_to_panel_reg @ 0x46e3c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, ...);
extern void *get_device_info(void);
extern void debug_print(uint32_t, ...);
extern void projector_send_cmd1(int, int);
extern void projector_send_cmd_0x46(unsigned int);
extern void net_pkt_write_be16(int);
extern void delay_ms(int);
extern void thunk_FUN_0007d77c(int);

void set_brightness_to_panel_reg(unsigned int param_1)
{
    unsigned long long uVar1;
    short sVar2;
    int iVar3;
    unsigned int uVar4;
    int iVar5;

    if (2 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): set brightness level = %d\n" /*=0xd7251*/, "set_brightness_to_panel_reg" /*=0xd7310*/, param_1);
        } else {
            debug_print("%s(): set brightness level = %d\n" /*=0xd7251*/, "set_brightness_to_panel_reg" /*=0xd7310*/, param_1);
        }
    }
    thunk_FUN_0007d77c(6);
    thunk_FUN_0007d77c(0xa9);
    if (5 < param_1) {
        iVar3 = (int)(intptr_t)get_device_info();
        net_pkt_write_be16((int)((*(short*)(intptr_t)(iVar3 + 0xed8) + 1) * 0x6f));
        uVar4 = (param_1 - 6) & 0xff;
        goto LAB_00046ea0;
    }
    iVar3 = (int)(intptr_t)get_device_info();
    uVar1 = ((unsigned long long)*(unsigned short*)(intptr_t)(iVar3 + 0xed8) << 1) / 9;
    iVar3 = (int)uVar1;
    if (iVar3 == 0) {
LAB_00046e7a:
        iVar3 = (int)(intptr_t)get_device_info();
        sVar2 = (short)(((short)((param_1 * 0x6f) / 6) + 1) * (*(short*)(intptr_t)(iVar3 + 0xed8) + 1));
    } else {
        iVar5 = (int)(intptr_t)get_device_info();
        if (*(unsigned short*)(intptr_t)(iVar5 + 0xed8) < 6) goto LAB_00046e7a;
        iVar5 = (int)(intptr_t)get_device_info();
        sVar2 = (short)(((short)((int)(param_1 * ((unsigned int)*(unsigned short*)(intptr_t)(iVar5 + 0xed8) - iVar3)) / 6) + (short)uVar1) * 0x6f);
    }
    net_pkt_write_be16(sVar2);
    uVar4 = 0;
LAB_00046ea0:
    projector_send_cmd_0x46(uVar4);
    projector_send_cmd1(0x31, 4);
    thunk_FUN_0007d77c(0xa3);
    thunk_FUN_0007d77c(0x97);
    delay_ms(1);
    return;
}

