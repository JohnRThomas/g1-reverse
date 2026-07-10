/* named: ext_flash_read */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20007b54  g_ext_flash_mutex            
//   0x20007b68  g_ext_flash_dev              
*/
/* Reconstructed ext_flash_read @ 0x2e398  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned a, unsigned b);
extern void debug_print(void);
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
    if (*(volatile int*)0x20007554 != 0){ debug_print(); return res; }
    DEBUG_PRINT(0, 0);
    return res;
}

