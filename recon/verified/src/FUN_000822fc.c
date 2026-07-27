/* Reconstructed FUN_000822fc @ 0x822fc  (parity: 300/300 trials, PROVEN) */

extern void FUN_000822ae(unsigned long, unsigned long);
extern void FUN_0007350c(unsigned int, unsigned int, unsigned int, unsigned int);
extern void FUN_0005833c(int*);
void FUN_000822fc(int param_1,int *param_2,int param_3)
{
    int *piVar1 = param_2;
    if (param_3 == 0) {
        FUN_000822ae(param_1, param_2);
    }
    if (*(int*)(*param_2 + 0x124) != 0) {
        FUN_0007350c(*param_2 + 0x160, piVar1, 0xf0000, 0);
    }
    FUN_0005833c(param_2);
}

