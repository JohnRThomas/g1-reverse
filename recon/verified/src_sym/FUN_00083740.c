/* Reconstructed FUN_00083740 @ 0x83740  (parity: 300/300 trials, PROVEN) */

extern int FUN_0005f5d0(int a, int b);
extern void memcpy(int a, int b, int c, int d);
void net_buf_simple_push_mem(int param_1, int param_2, int param_3, int param_4) {
    int uVar1 = FUN_0005f5d0(param_1, param_3);
    memcpy(uVar1, param_2, param_3, param_4);
}

