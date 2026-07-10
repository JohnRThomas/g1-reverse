/* named: dequeue_ancs */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20006a6c  g_ancs_msgq                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed dequeue_ancs @ 0x18d94  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int fmt, unsigned int arg);
extern void debug_print(void);
extern int k_msgq_get(void *a, void *b, unsigned int c, unsigned int d);
extern void memcpy(void *dst, void *src, unsigned int len);
extern void memset_bytes(void *dst, int val, unsigned int len);

int dequeue_ancs(void *param_1)
{
    unsigned char buf[0x1b4];
    memset_bytes(buf, 0, 0x1b4);

    volatile unsigned char *base = (volatile unsigned char *)0x20006a6cUL;
    if (*(volatile unsigned int *)(base + 0x10) == 0) {
        return 1;
    }

    int iVar1 = k_msgq_get((void *)base, buf, 0, 0);
    if (iVar1 == 0) {
        memcpy(param_1, buf, 0x1b4);
    } else if (*(volatile int *)0x2000230cUL > 0) {
        if (*(volatile int *)0x20007554UL == 0) {
            DEBUG_PRINT(0x9aa1fU, 0x9b190U);
        } else {
            debug_print();
        }
    }
    return iVar1;
}

