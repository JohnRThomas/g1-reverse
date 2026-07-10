/* named: enqueue_debug */
/* globals referenced:
//   0x2000751c  g_debug_msg_pipe             
*/
/* Reconstructed enqueue_debug @ 0x19bfc  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a);
extern int k_msgq_put(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void k_msgq_get(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void memcpy(unsigned int a, unsigned int b, unsigned int c);

int enqueue_debug(unsigned int param_1)
{
    int iVar1;
    if (*(volatile int*)(0x2000751cUL + 0x24) == 0x14) {
        k_msgq_get(0x2000751cUL, 0x20010257UL, 0, 0);
    }
    memcpy(0x20010257UL, param_1, 200);
    iVar1 = k_msgq_put(0x2000751cUL, 0x20010257UL, 0, 0);
    if (iVar1 != 0) {
        DEBUG_PRINT(0x0009b35aUL);
    }
    return iVar1;
}

