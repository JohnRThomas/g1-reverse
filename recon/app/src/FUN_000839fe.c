/* Reconstructed FUN_000839fe @ 0x839fe  (parity: 300/300 trials, PROVEN) */
extern int FUN_000839dc(int a, int b);
extern int tail_61200(int a, int b);
extern void FUN_00086c04(int a, int b, int c);
unsigned FUN_000839fe(int param_1, int param_2, int param_3, int param_4){
    int iVar1 = FUN_000839dc(param_2, param_4);
    if (iVar1 == 0){
        return tail_61200(param_2, param_4);
    }
    if (param_4 != 0){
        FUN_00086c04(param_3, param_2, param_4);
    }
    return 0;
}

