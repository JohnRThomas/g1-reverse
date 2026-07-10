#include "g1_app_symbols.h"
/* named: ipc_rpmsg_deinit */
/* Reconstructed ipc_rpmsg_deinit @ 0x7ed2a  (parity: 300/300 trials, PROVEN) */

extern void rpmsg_deinit_vdev(void *a);

int ipc_rpmsg_deinit(int *param_1, int param_2)
{
    int uVar1;
    if (param_1 == 0) {
        uVar1 = 0xffffffea;
    } else {
        rpmsg_deinit_vdev((char*)param_1 + 0xe0);
        if (param_2 == 0) {
            *(int*)((char*)param_1 + 0x19c) = 0;
            *(int*)((char*)param_1 + 0x1a0) = 0;
            *(int*)((char*)param_1 + 0x1a4) = 0;
        }
        uVar1 = 0;
    }
    return uVar1;
}

