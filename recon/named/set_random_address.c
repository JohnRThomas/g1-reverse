/* named: set_random_address */
/* Reconstructed set_random_address @ 0x810f2  (parity: 300/300 trials, PROVEN) */
extern int tail_54d88(int a, int b, int c, int d);
int set_random_address(int param_1, int param_2, int param_3, int param_4){
    if (param_1 == 0 || param_2 == 0) return -0x16;
    return tail_54d88(param_2, param_2, param_3, param_4);
}

