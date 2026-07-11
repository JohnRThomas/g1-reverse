/* Reconstructed memset_bytes @ 0x86c78  (parity: 300/300 trials, PROVEN) */

void memset_bytes(unsigned char *param_1, unsigned char param_2, int param_3){
    unsigned char *end = param_1 + param_3;
    unsigned char *p = param_1;
    while (p != end) {
        *p = param_2;
        p = p + 1;
    }
}
