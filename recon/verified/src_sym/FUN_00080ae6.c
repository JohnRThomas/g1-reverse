/* Reconstructed FUN_00080ae6 @ 0x80ae6  (parity: 300/300 trials, PROVEN) */

extern int FUN_000526e4(void);
extern void memcpy(int a, int b, int c);

int FUN_00080ae6(char *param_1, char *param_2)
{
    int iVar1;
    unsigned int fptr;
    iVar1 = FUN_000526e4();
    if (iVar1 != 0) {
        fptr = *(volatile unsigned int*)(param_2 + 0x34);
        if (fptr == 0) {
            memcpy(iVar1 + 0x18, (int)(long)(param_1 + 0x18), *(volatile signed char*)(param_1 + 0xb));
        } else {
            ((void(*)(int,char*))fptr)(iVar1, param_1);
        }
    }
    return iVar1;
}

