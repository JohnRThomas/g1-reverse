/* named: FUN_0007c8e8 */
/* Reconstructed FUN_0007c8e8 @ 0x7c8e8  (parity: 300/300 trials, PROVEN) */

extern unsigned int ipc_ept_op_b_locked_retry(unsigned int a, unsigned int b, unsigned int c);

unsigned int FUN_0007c8e8(unsigned int param_1, int param_2)
{
    if (param_2 != 0) {
        return ipc_ept_op_b_locked_retry(param_1, 1, param_2);
    }
    return 0xffffffea;
}

