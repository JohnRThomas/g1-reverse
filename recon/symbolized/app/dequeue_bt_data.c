#include "g1_app_symbols.h"
/* named: dequeue_bt_data */
/* globals referenced:
//   0x200038f8  g_bt_data_pipe               
*/
/* Reconstructed dequeue_bt_data @ 0x181b8  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern int k_msgq_get(unsigned int, void*, int, int);
extern void memcpy(unsigned int, void*, int);

int dequeue_bt_data(unsigned int param_1)
{
    unsigned char buf[264];
    memset_bytes(buf, 0, 0x101);
    int iVar1 = k_msgq_get(((uintptr_t)&g_bt_data_pipe) /*=0x200038f8*/, buf, 0, 0);
    if (iVar1 == 0) {
        memcpy(param_1, buf, 0x101);
    }
    return iVar1;
}

