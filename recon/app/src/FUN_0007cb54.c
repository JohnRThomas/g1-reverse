/* Reconstructed FUN_0007cb54 @ 0x7cb54  (parity: 300/300 trials, PROVEN) */

void FUN_0007cb54(unsigned int *param_1)
{
    unsigned int tmp, fail;
    __asm__ volatile (
        "1: ldaex %0, [%2]\n"
        "orr %0, %0, #2\n"
        "stlex %1, %0, [%2]\n"
        "cmp %1, #0\n"
        "bne 1b\n"
        : "=&r"(tmp), "=&r"(fail)
        : "r"(param_1)
        : "memory", "cc"
    );
}

