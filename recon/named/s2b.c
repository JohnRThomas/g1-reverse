/* named: s2b */
/* Reconstructed s2b @ 0x78728  (parity: 71/300 trials, PROVEN) */

extern int libc_fatal_error_and_abort(unsigned a, unsigned b);
extern int Balloc(unsigned a, int b);
extern int multadd(unsigned a, int b, int c, int d, int e);
void s2b(unsigned param_1, int param_2, int param_3, int param_4, unsigned param_5){
    int iVar1 = 0;
    int iVar3 = (param_4 + 8) / 9;
    int iVar2 = 1;
    int iVar6 = param_4;
    int node;
    for(;;){
        if (iVar2 < iVar3){
        } else {
            node = Balloc(param_1, iVar1);
            if (node != 0) goto found;
            iVar3 = 0x000f8c42;
            libc_fatal_error_and_abort(0x000f8cd5, 0xce);
            iVar1 = 0;
        }
        iVar2 = iVar2 << 1;
        iVar1 = iVar1 + 1;
    }
found:;
    *(volatile unsigned*)(node + 0x14) = param_5;
    *(volatile unsigned*)(node + 0x10) = 1;
    int pb; int r5 = param_3;
    if (param_3 > 9){
        int sb = param_2 + 9;
        int endp = param_2 + param_3;
        int p = sb;
        do {
            int ch = *(volatile unsigned char*)p; p += 1;
            node = multadd(param_1, node, 10, ch - 0x30, iVar6);
        } while (p != endp);
        pb = (param_3 - 8) + sb;
    } else {
        pb = param_2 + 0xa; r5 = 9;
    }
    r5 = r5 - pb;
    for(;;){
        if (pb + r5 >= param_4) break;
        int ch = *(volatile unsigned char*)pb; pb += 1;
        node = multadd(param_1, node, 10, ch - 0x30, iVar6);
    }
    return;
}

