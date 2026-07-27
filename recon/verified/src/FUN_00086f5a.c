/* Reconstructed FUN_00086f5a @ 0x86f5a  (parity: 300/300 trials, PROVEN) */
extern void FUN_00078598(int* a, int b, int c, int d);
extern int _write_r(int *, int, const void *, unsigned int);
void FUN_00086f5a(int* param_1, int param_2, int param_3, int param_4){
    unsigned short v = *(unsigned short*)(param_2 + 0xc);
    if ((int)((unsigned)v << 0x17) < 0){
        FUN_00078598(param_1, (int)*(short*)(param_2 + 0xe), 0, 2);
    }
    unsigned short w = *(unsigned short*)(param_2 + 0xc);
    short s = *(short*)(param_2 + 0xe);
    w = w & 0xefff;
    *(unsigned short*)(param_2 + 0xc) = w;
    _write_r(param_1, (int)s, param_3, param_4);
}
