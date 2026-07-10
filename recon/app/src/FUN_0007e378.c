/* Reconstructed FUN_0007e378 @ 0x7e378  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007e35c(int a,int b,int c);
void FUN_0007e378(int *param_1, int param_2) {
    char *base = (char*)param_1;
    int v = *(int*)(base + 0xc);
    int r = FUN_0007e35c((int)param_1, v, param_2);
    *(int*)(base + 0xc) = r;
    unsigned int u = *(unsigned int*)(base + 0x10);
    *(unsigned int*)(base + 0x10) = u & 0xfffffff7u;
}

