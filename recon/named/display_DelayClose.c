/* named: display_DelayClose */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed display_DelayClose @ 0x498c0  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void *dst, int val, unsigned int len);
extern int k_msgq_put(void *obj, void *msg, unsigned int a, unsigned int b);
extern void DEBUG_PRINT(unsigned int fmt, unsigned int arg);
extern void debug_print(void);

unsigned int display_DelayClose(unsigned int param_1)
{
    unsigned char buf[0x18];
    memset_bytes(buf + 1, 0, 0x17);
    buf[0] = 4;
    *(unsigned short *)(buf + 2) = 4;
    *(unsigned int *)(buf + 4) = param_1;

    void *obj = (void *)0x200038c4UL;
    int iVar1 = k_msgq_put(obj, buf, 0, 0);
    unsigned int uVar2;

    if (iVar1 == 0) {
        uVar2 = 0;
        if (*(volatile int *)0x2000230cUL > 2) {
            if (*(volatile int *)0x20007554UL == 0) {
                DEBUG_PRINT(0xf008cU, 0xf0164U);
            } else {
                debug_print();
            }
        }
    } else {
        DEBUG_PRINT(0xef058U, 0xf0164U);
        uVar2 = 0xffffffffU;
    }
    return uVar2;
}

