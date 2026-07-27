/* Reconstructed FUN_00056654 @ 0x56654  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(unsigned long, ...);

int FUN_00056654(int param_1)
{
    int *counter;
    int old_value;
    if (param_1 == 0) {
        FUN_0007e2fa(0x00099cbd, 0x000f3ebd, 0x000f3a5d, 0x509);
        FUN_0007e2ec(0x000f3a5d, 0x509);
        return 0x509;
    }
    counter = (int *)(param_1 + 0xd0);
    for (;;) {
        old_value = __atomic_load_n(counter, __ATOMIC_ACQUIRE);
        if (old_value == 0)
            return 0;
        {
            int expected = old_value;
            if (__atomic_compare_exchange_n(counter, &expected, old_value + 1,
                                            1, __ATOMIC_ACQ_REL,
                                            __ATOMIC_ACQUIRE))
                return param_1;
        }
    }
}
