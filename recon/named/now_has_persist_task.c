/* readable reconstruction; identity: FUN_0002be64 @ 0x0002be64
 * public-name: now_has_persist_task
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_persist_task_status_lock               @ 0x20018d9c
 */
/* Reconstructed now_has_persist_task @ 0x2be64  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007cdf8(void);
extern void DEBUG_PRINT(void);
extern void debug_print(void);

unsigned char now_has_persist_task(unsigned char *param_1, unsigned int param_2)
{
    volatile unsigned char *pcVar1 = (volatile unsigned char*)0x20018d9cUL;
    while (*pcVar1 != 0) {
        FUN_0007cdf8();
    }
    int *p = *(int**)(param_1 + 0x1054);
    unsigned int uVar3 = *((unsigned char*)p + 4);
    unsigned char uVar2 = 0;
    if (uVar3 > 1) {
        if (*(volatile int*)0x2000230cUL > 3) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT();
            } else {
                debug_print();
            }
        }
        uVar2 = 1;
    }
    return uVar2;
}
