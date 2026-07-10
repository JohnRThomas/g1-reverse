/* Reconstructed FUN_0007efd4 @ 0x7efd4  (parity: 300/300 trials, PROVEN) */

typedef unsigned int (*fn_t)(int, int);
unsigned int FUN_0007efd4(int param_1, int param_2, int param_3)
{
    if (param_2 >= 0 && (unsigned int)(param_3 + param_2) <= *(unsigned int*)(param_1 + 8)) {
        int a = *(int*)(param_1 + 0xc);
        int b = *(int*)(a + 8);
        fn_t f = *(fn_t*)(b + 8);
        return f(*(int*)(param_1 + 0xc), param_2 + *(int*)(param_1 + 4));
    }
    return 0xffffffea;
}

