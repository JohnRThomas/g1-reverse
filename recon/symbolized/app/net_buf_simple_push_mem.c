#include "g1_app_symbols.h"
/* named: net_buf_simple_push_mem */
/* Reconstructed net_buf_simple_push_mem @ 0x850dc  (parity: 300/300 trials, PROVEN) */

extern void FUN_00064f48(void);
extern void nrfx_gppi_task_endpoint_setup(unsigned int, unsigned int);

void net_buf_simple_push_mem(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    FUN_00064f48();
    nrfx_gppi_task_endpoint_setup(param_1, param_3);
}

