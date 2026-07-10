/* Reconstructed pend_locked @ 0x73f3c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00073ec0(void);
extern void FUN_00074bf4(int, unsigned int, int, int);

void pend_locked(int param_1, unsigned int param_2, int param_3, int param_4)
{
    FUN_00073ec0();
    if (param_4 != -1 || param_3 != -1) {
        FUN_00074bf4(param_1 + 0x18, 0x86661U, param_3, param_4);
        return;
    }
    return;
}

