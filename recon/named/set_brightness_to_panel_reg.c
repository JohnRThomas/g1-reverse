/* readable reconstruction; identity: FUN_00046e3c @ 0x00046e3c
 * public-name: set_brightness_to_panel_reg
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   thunk_FUN_0007d77c                       <= FUN_0007d63e @ 0x0007d63e
 *   projector_send_cmd1                      <= FUN_0007d642 @ 0x0007d642
 *   projector_send_cmd_0x46                  <= FUN_0007d67e @ 0x0007d67e
 *   net_pkt_write_be16                       <= FUN_0007d696 @ 0x0007d696
 *   delay_ms                                 <= FUN_0007d772 @ 0x0007d772
 * address symbols (name @ address):
 *   rodata_d7251                             @ 0x000d7251   [INLINED -- G6 literal batch]
 *   rodata_d7310                             @ 0x000d7310   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed set_brightness_to_panel_reg @ 0x46e3c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void log_message(uint32_t, ...);
extern void *get_device_info(void);
extern void debug_print(uint32_t, ...);
extern void projector_send_cmd1(int, int);
extern void projector_send_cmd_0x46(unsigned int);
extern void net_pkt_write_be16(int);
extern void delay_ms(int);
extern void thunk_FUN_0007d77c(int);

void set_brightness_to_panel_reg(unsigned int param_1)
{
    unsigned int uVar1;
    short sVar2;
    int iVar3;
    unsigned int uVar4;
    int iVar5;

    if (2 < *(volatile int*)0x2000230cUL) {
        if (*(volatile int*)0x20007554UL == 0) {
            log_message(0x000d7251UL, 0x000d7310UL, param_1);
        } else {
            debug_print(0x000d7251UL, 0x000d7310UL, param_1);
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
    uVar1 = ((unsigned int)*(unsigned short*)(intptr_t)(iVar3 + 0xed8) << 1) / 9;
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
