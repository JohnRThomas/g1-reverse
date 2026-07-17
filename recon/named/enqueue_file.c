/* readable reconstruction; identity: FUN_00023514 @ 0x00023514
 * public-name: enqueue_file
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 * address symbols (name @ address):
 *   rodata_9e824                             @ 0x0009e824
 *   rodata_9e840                             @ 0x0009e840
 *   rodata_9e8f6                             @ 0x0009e8f6
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_file_msg_pipe                          @ 0x200079a0
 */
/* Reconstructed enqueue_file @ 0x23514  (parity: 300/300 trials, PROVEN) */

extern void k_msgq_get(unsigned int, void*, int, int);
extern void FUN_00086c1e(void*, unsigned int, unsigned int, int);
extern int k_msgq_put(unsigned int, void*, int, int);
extern void log_message(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, ...);

int enqueue_file(unsigned int param_1, unsigned int param_2)
{
    int iVar1;
    unsigned char buf[201];

    if (*(volatile int*)(0x200079a0UL + 0x24) == 0x1e) {
        k_msgq_get(0x200079a0UL, buf, 0, 0);
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                log_message(0x9e824, 0x9e8f6);
            } else {
                debug_print(0x9e824, 0x9e8f6);
            }
        }
    }
    FUN_00086c1e(buf, param_1, param_2, 0xc9);
    buf[200] = (unsigned char)param_2;
    iVar1 = k_msgq_put(0x200079a0UL, buf, 0, 0);
    if ((iVar1 != 0) && (0 < *(volatile int*)0x2000230cUL)) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            log_message(0x9e840, 0x9e8f6);
        } else {
            debug_print(0x9e840, 0x9e8f6);
        }
    }
    return iVar1;
}
