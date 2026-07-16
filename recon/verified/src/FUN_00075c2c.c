/* Reconstructed FUN_00075c2c @ 0x75c2c  (parity: 300/300 trials, PROVEN) */
extern int FUN_00075f88(void);
extern int FUN_000868ee(float);
extern int* thunk_FUN_00071678(void);
extern float FUN_00076a88(unsigned int descriptor);
float FUN_00075c2c(float param_1){
    int uVar1 = FUN_00075f88();
    (void)uVar1;
    signed char c = *(volatile signed char*)0x200035afUL;
    if ((c + 1) != 0 && !(param_1 != param_1)){
        FUN_000868ee(param_1);
        if (param_1 > 1.0f){
            int* p = thunk_FUN_00071678();
            *p = 0x21;
            return FUN_00076a88(0x000a8ea0u);
        }
    }
    return param_1;
}
