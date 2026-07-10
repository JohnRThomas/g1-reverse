#include "g1_app_symbols.h"
/* named: rproc_virtio_negotiate_features */
/* Reconstructed rproc_virtio_negotiate_features @ 0x7c34a  (parity: 300/300 trials, PROVEN) */

extern void build_and_send_device_status_report(void);
extern void FUN_0007c28e(unsigned int, unsigned int);

unsigned int rproc_virtio_negotiate_features(unsigned int param_1, unsigned int param_2)
{
    build_and_send_device_status_report();
    FUN_0007c28e(param_1, param_2);
    return 0;
}

