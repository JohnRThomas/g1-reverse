/* named: enqueue_file */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x200079a0  g_file_msg_pipe              
*/
/* Reconstructed enqueue_file @ 0x23514  (parity: 300/300 trials, PROVEN) */

extern void k_msgq_get(unsigned int, void*, int, int);
extern void FUN_00086c1e(void*, unsigned int, unsigned int, int);
extern int k_msgq_put(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);

int enqueue_file(unsigned int param_1, unsigned int param_2)
{
    int iVar1;
    unsigned char buf[200];

    if (*(volatile int*)(0x200079a0UL + 0x24) == 0x1e) {
        k_msgq_get(0x200079a0UL, buf, 0, 0);
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x9e824, 0x9e8f6);
            } else {
                debug_print();
            }
        }
    }
    FUN_00086c1e(buf, param_1, param_2, 0xc9);
    buf[200-4] = (unsigned char)param_2;
    iVar1 = k_msgq_put(0x200079a0UL, buf, 0, 0);
    if ((iVar1 != 0) && (0 < *(volatile int*)0x2000230cUL)) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x9e840, 0x9e8f6);
        } else {
            debug_print();
        }
    }
    return iVar1;
}

