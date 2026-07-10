/* named: FUN_0007c932 */
/* Reconstructed FUN_0007c932 @ 0x7c932  (parity: 300/300 trials, PROVEN) */

extern unsigned int ipc_ept_op_b_locked_retry(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

unsigned int FUN_0007c932(unsigned int param_1, int param_2)
{
    if (param_2 != 0) {
        return ipc_ept_op_b_locked_retry(param_1, 0x18, param_2, 8);
    }
    return 0xffffffea;
}

