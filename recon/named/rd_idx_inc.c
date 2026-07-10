/* named: rd_idx_inc */
/* Reconstructed rd_idx_inc @ 0x7e378  (parity: 300/300 trials, PROVEN) */

extern int idx_inc(int a,int b,int c);
void rd_idx_inc(int *param_1, int param_2) {
    char *base = (char*)param_1;
    int v = *(int*)(base + 0xc);
    int r = idx_inc((int)param_1, v, param_2);
    *(int*)(base + 0xc) = r;
    unsigned int u = *(unsigned int*)(base + 0x10);
    *(unsigned int*)(base + 0x10) = u & 0xfffffff7u;
}

