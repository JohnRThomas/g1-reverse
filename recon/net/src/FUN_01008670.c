/* net-core FUN_01008670 @ 0x1008670  (parity 300 trials PROVEN) */
unsigned long long FUN_01008670(unsigned int param_1, unsigned int *param_2)
{
    unsigned int a[8];
    for (int i = 0; i < 8; i++) a[i] = param_2[i];
    unsigned int r[16];
    for (int i = 0; i < 16; i++) r[i] = 0;

    for (int i = 0; i < 8; i++) {
        unsigned long long c = 0;
        for (int j = 0; j < 8; j++) {
            unsigned long long p = (unsigned long long)a[i] * (unsigned long long)a[j] + r[i+j] + c;
            r[i+j] = (unsigned int)p;
            c = p >> 32;
        }
        int k = i + 8;
        while (c) {
            unsigned long long p = (unsigned long long)r[k] + c;
            r[k] = (unsigned int)p;
            c = p >> 32;
            k++;
        }
    }
    return ((unsigned long long)r[15] << 32) | (unsigned long long)r[14];
}

