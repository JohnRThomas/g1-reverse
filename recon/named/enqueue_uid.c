/* readable reconstruction; identity: FUN_00018e48 @ 0x00018e48
 * public-name: enqueue_uid
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 * address symbols (name @ address):
 *   rodata_9aa2f                             @ 0x0009aa2f
 *   rodata_9aa4b                             @ 0x0009aa4b
 *   rodata_9aa64                             @ 0x0009aa64
 *   rodata_9b176                             @ 0x0009b176
 *   g_log_level                              @ 0x2000230c
 *   g_uid_pipe                               @ 0x20006a38
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed enqueue_uid @ 0x18e48  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned a, ...);
extern void debug_print(unsigned a, ...);
extern void k_msgq_get(unsigned a, void*b, int c, int d);
extern int  k_msgq_put(unsigned a, void*b, int c, int d);
int enqueue_uid(unsigned *param_1, unsigned param_2, unsigned param_3){
    unsigned local[3];
    local[0]=0; local[1]=0; local[2]=param_3;
    volatile int *g = (volatile int*)0x20006a38;
    if (g[0x10/4] == 0) return 1;
    int iVar2;
    if (g[0x24/4] == 10){
        k_msgq_get(0x20006a38, local, 0, 0);
        if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0x0009aa2f);
        else debug_print(0x0009aa2f);
    }
    local[0] = param_1[0];
    local[1] = param_1[1];
    if (*(volatile int*)0x2000230c > 0){
        if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0x0009aa4b,0x0009b176,local[0]);
        else debug_print(0x0009aa4b,0x0009b176,local[0]);
    }
    iVar2 = k_msgq_put(0x20006a38, local, 0, 0);
    if (iVar2 != 0 && *(volatile int*)0x2000230c > 0){
        if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0x0009aa64,0x0009b176);
        else debug_print(0x0009aa64,0x0009b176);
    }
    return iVar2;
}
