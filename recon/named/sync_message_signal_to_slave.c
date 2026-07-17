/* readable reconstruction; identity: FUN_0002c224 @ 0x0002c224
 * public-name: sync_message_signal_to_slave
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_uptime_get_2                           <= FUN_0007ce40 @ 0x0007ce40
 * address symbols (name @ address):
 *   rodata_a26ae                             @ 0x000a26ae
 *   rodata_a3a24                             @ 0x000a3a24
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed sync_message_signal_to_slave @ 0x2c224  (parity: 300/300 trials, PROVEN) */

extern unsigned long long k_uptime_get_2(void);
extern unsigned int get_device_info(void);
extern unsigned int sync_to_slave(unsigned int, int, void*, int, unsigned int);
extern void log_message(unsigned int, ...);
extern void debug_print(void);

unsigned int sync_message_signal_to_slave(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    struct sync_message {
        unsigned int signal;
        unsigned int value;
    } message = { param_2, param_3 };
    unsigned int uVar2, uVar4;
    unsigned int iVar3;
    unsigned long long lVar7, uVar8;

    uVar4 = param_1;
    lVar7 = k_uptime_get_2();
    message.signal = (message.signal & 0xffff0000U) | (param_1 & 0xff);
    uVar2 = get_device_info();
    uVar2 = sync_to_slave(uVar2, 7, &message.signal, 1, uVar4);
    iVar3 = get_device_info();
    uVar4 = 0xa2690;
    if (*(volatile unsigned char*)(iVar3 + 0x105a) == 2) {
        uVar4 = 0xa269c;
    }
    if (*(volatile unsigned int*)0x20007554UL == 0) {
        log_message(uVar4, 0xa3a24);
    } else {
        debug_print();
    }
    uVar8 = k_uptime_get_2();
    if ((long long)(lVar7 + 3000) < (long long)uVar8) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            log_message(0xa26ae);
        } else {
            debug_print();
        }
    }
    return uVar2;
}
