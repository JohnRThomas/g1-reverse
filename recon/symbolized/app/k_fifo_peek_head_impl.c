#include "g1_app_symbols.h"
/* named: k_fifo_peek_head_impl */
/* Reconstructed k_fifo_peek_head_impl @ 0x8652c  (parity: 300/300 trials, PROVEN) */

extern void z_queue_node_peek(unsigned int, unsigned int);
void k_fifo_peek_head_impl(unsigned int *param_1)
{
    z_queue_node_peek(*param_1, 0);
}

