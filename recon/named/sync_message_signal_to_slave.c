/* named: sync_message_signal_to_slave */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed sync_message_signal_to_slave @ 0x2c224  (parity: 300/300 trials, PROVEN) */

extern unsigned long long k_uptime_get_2(void);
extern unsigned int get_device_info(void);
extern unsigned int sync_to_slave(unsigned int, int, void*, int, unsigned int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);

unsigned int sync_message_signal_to_slave(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int uVar2, uVar4;
    unsigned int local_1c;
    unsigned int iVar3;
    unsigned long long lVar7, uVar8;

    uVar4 = param_1;
    local_1c = param_2;
    lVar7 = k_uptime_get_2();
    local_1c = (param_2 & 0xffff0000U) | (param_1 & 0xff);
    uVar2 = get_device_info();
    uVar2 = sync_to_slave(uVar2, 7, &local_1c, 1, uVar4);
    iVar3 = get_device_info();
    uVar4 = 0xa2690;
    if (*(volatile unsigned char*)(iVar3 + 0x105a) == 2) {
        uVar4 = 0xa269c;
    }
    if (*(volatile unsigned int*)0x20007554UL == 0) {
        DEBUG_PRINT(uVar4, 0xa3a24);
    } else {
        debug_print();
    }
    uVar8 = k_uptime_get_2();
    if ((long long)(lVar7 + 3000) < (long long)uVar8) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT(0xa26ae, 0xa3a24);
        } else {
            debug_print();
        }
    }
    return uVar2;
}

