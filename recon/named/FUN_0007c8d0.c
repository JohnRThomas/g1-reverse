/* named: FUN_0007c8d0 */
/* Reconstructed FUN_0007c8d0 @ 0x7c8d0  (parity: 300/300 trials, PROVEN) */

extern int ipc_ept_op_c_locked_retry(int a,int b,void*c,int d,int e,int f);
void FUN_0007c8d0(int param_1, int param_2) {
    unsigned char local = (unsigned char)param_2;
    ipc_ept_op_c_locked_retry(param_1, 0, &local, 1, param_1, param_2);
}

