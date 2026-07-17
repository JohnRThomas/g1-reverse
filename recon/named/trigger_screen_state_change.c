/* readable reconstruction; identity: FUN_0002bc2c @ 0x0002bc2c
 * public-name: trigger_screen_state_change
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   rodata_a2470                             @ 0x000a2470
 *   rodata_a2486                             @ 0x000a2486
 *   rodata_a254a                             @ 0x000a254a
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed trigger_screen_state_change @ 0x2bc2c  (parity: 300/300 trials, PROVEN) */

extern void k_sem_give(unsigned int);
extern void log_message(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, ...);

unsigned int trigger_screen_state_change(unsigned int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    if ((unsigned int)(*(volatile unsigned char*)(param_2 + 0xfe8)) == param_3) {
        if (1 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                log_message(0xa2470, 0xa254a, param_1, *(volatile unsigned char*)(param_2 + 0xfe8), param_4);
            } else {
                debug_print(0xa2470, 0xa254a, param_1,
                             *(volatile unsigned char*)(param_2 + 0xfe8), param_4);
            }
        }
        param_3 = 0xffffffff;
    } else {
        if (param_3 == 0) {
            *(volatile unsigned char*)(param_2 + 0xfe8) = 0;
        } else {
            *(volatile unsigned char*)(param_2 + 0xfe8) = 1;
            k_sem_give(param_2 + 0x50);
        }
        if (1 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                log_message(0xa2486, 0xa254a, param_1, *(volatile unsigned char*)(param_2 + 0xfe8), param_4);
            } else {
                debug_print(0xa2486, 0xa254a, param_1,
                             *(volatile unsigned char*)(param_2 + 0xfe8), param_4);
            }
        }
    }
    return param_3;
}
