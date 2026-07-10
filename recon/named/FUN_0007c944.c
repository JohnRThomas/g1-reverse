/* named: FUN_0007c944 */
/* Reconstructed FUN_0007c944 @ 0x7c944  (parity: 300/300 trials, PROVEN) */

extern unsigned int ipc_ept_op_b_locked_retry(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

unsigned int FUN_0007c944(unsigned int param_1, int param_2)
{
    if (param_2 != 0) {
        return ipc_ept_op_b_locked_retry(param_1, 0x20, param_2, 1);
    }
    return 0xffffffea;
}

