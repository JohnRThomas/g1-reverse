/* named: reset_all_static_info */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x2007fc00  g_dashboard_startup_mode_info_defaults 
*/
/* Reconstructed reset_all_static_info @ 0x16738  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int fmt, unsigned int a1, unsigned int a2, unsigned int a3);
extern void debug_print(void);
extern void memset_bytes(void *dst, int val, unsigned int len);

void reset_all_static_info(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    if (*(volatile int *)0x2000230cUL > 2) {
        if (*(volatile int *)0x20007554UL == 0) {
            DEBUG_PRINT(0x99707U, 0x99bd8U, param_3, 0U);
        } else {
            debug_print();
        }
    }
    volatile unsigned char *base = (volatile unsigned char *)0x2007fc00UL;
    *(volatile unsigned int *)(base + 8) = 0;
    *(volatile unsigned int *)(base + 0xc) = 0;
    *(volatile unsigned int *)(base + 0) = 0;
    *(volatile unsigned short *)(base + 4) = 0;
    *(volatile unsigned char *)(base + 0x5f) = 0;
    *(volatile unsigned short *)(base + 0x60) = 0;
    *(volatile unsigned char *)(base + 0x62) = 0;
    *(volatile unsigned char *)(base + 0x68) = 0;
    memset_bytes((void *)(base + 0x10), 0, 0x25);
    memset_bytes((void *)(base + 0x35), 0, 0x25);
    *(volatile unsigned int *)(base + 0x64) = 0;
}

