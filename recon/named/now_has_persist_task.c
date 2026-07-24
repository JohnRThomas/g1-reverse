/* readable reconstruction; identity: FUN_0002be64 @ 0x0002be64
 * public-name: now_has_persist_task
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   signal_persist_task_event                <= FUN_0007cdf8 @ 0x0007cdf8
 * address symbols (name @ address):
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_persist_task_status_lock               @ 0x20018d9c
 */
/* Reconstructed now_has_persist_task @ 0x2be64  (parity: CFG state-case proven, 4/4 cases) */

extern void signal_persist_task_event(void);
extern void log_message(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern void debug_print(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

unsigned char now_has_persist_task(unsigned char *param_1, unsigned int param_2)
{
    volatile unsigned char *pcVar1 = (volatile unsigned char*)0x20018d9cUL;
    while (*pcVar1 != 0) {
        signal_persist_task_event();
    }
    int *p = *(int**)(param_1 + 0x1054);
    unsigned int uVar3 = *((unsigned char*)p + 4);
    unsigned char uVar2 = 0;
    if (uVar3 > 1) {
        if (*(volatile int*)0x2000230cUL > 3) {
            unsigned int b = *(unsigned char*)(param_1 + 0xd5);
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                log_message(0xa2566U, 0xa267bU, uVar3, param_2, b);
            } else {
                debug_print(0xa2566U, 0xa267bU, uVar3, param_2, b);
            }
        }
        uVar2 = 1;
    }
    return uVar2;
}
