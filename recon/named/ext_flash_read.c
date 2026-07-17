/* readable reconstruction; identity: FUN_0002e398 @ 0x0002e398
 * public-name: ext_flash_read
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   ext_flash_read                           <= FUN_0002e398 @ 0x0002e398
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 * address symbols (name @ address):
 *   rodata_a3a5a                             @ 0x000a3a5a
 *   rodata_a3ab6                             @ 0x000a3ab6
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ext_flash_mutex                        @ 0x20007b54
 *   g_ext_flash_dev                          @ 0x20007b68
 */
/* Reconstructed FUN_0002e398 @ 0x2e398  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned a, unsigned b);
extern void debug_print(unsigned a, unsigned b);
extern void k_mutex_lock(unsigned a, int b, unsigned c, unsigned d);
extern void k_mutex_unlock(unsigned a);
extern void FUN_0007c080(void);
extern void FUN_0007c082(void);
int ext_flash_read(int param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    volatile unsigned char *r5 = (volatile unsigned char*)(param_1 + 0x1000);
    int iVar2 = (int)((unsigned)*(volatile unsigned short*)(r5 + 0x5c) << 0x1b);
    if (iVar2 >= 0) FUN_0007c080();
    volatile int *g = (volatile int*)0x20007b68;
    if (*g == 0){
        int t = (int)((unsigned)*(volatile unsigned short*)(r5 + 0x5c) << 0x1b);
        if (t >= 0) FUN_0007c082();
        return 0;
    }
    k_mutex_lock(0x20007b54, iVar2, 0xffffffffu, 0xffffffffu);
    int r0v = *g;
    int r3v = *(volatile int*)(r0v + 8);
    typedef int (*fn_t)(int, unsigned, unsigned, unsigned);
    fn_t f = *(volatile fn_t*)(r3v + 0);
    int res = f(r0v, param_2, param_3, param_4);
    k_mutex_unlock(0x20007b54);
    int t2 = (int)((unsigned)*(volatile unsigned short*)(r5 + 0x5c) << 0x1b);
    if (t2 >= 0) FUN_0007c082();
    if (res == 0) return 0;
    if (*(volatile int*)0x2000230c < 1) return res;
    if (*(volatile int*)0x20007554 != 0){
        debug_print(0x000a3a5aUL, 0x000a3ab6UL);
        return res;
    }
    DEBUG_PRINT(0x000a3a5aUL, 0x000a3ab6UL);
    return res;
}
