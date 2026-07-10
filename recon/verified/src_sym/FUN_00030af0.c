/* Reconstructed FUN_00030af0 @ 0x30af0  (parity: 300/300 trials, PROVEN) */

extern int FUN_000302f8(int,unsigned int*,int,int,int);
extern void FUN_00030224(void);

void FUN_00030af0(int param_1, int param_2, int param_3)
{
    unsigned int local_c = 0;
    int iVar1 = FUN_000302f8(0x4410, &local_c, param_3, 0, param_1);
    if (iVar1 >= 0) {
        if ((int)(local_c << 0x1d) < 0) {
            *(volatile unsigned char*)0x20019dacUL = 2;
        }
        if ((local_c & 2) != 0) {
            *(volatile unsigned char*)0x20019dacUL = 1;
        }
        if ((local_c & 1) != 0) {
            FUN_00030224();
            return;
        }
    }
}

