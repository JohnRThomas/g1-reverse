/* Reconstructed FUN_00019bfc @ 0x19bfc  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a);
extern int FUN_000720d0(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void FUN_00072240(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void FUN_00086c04(unsigned int a, unsigned int b, unsigned int c);

int FUN_00019bfc(unsigned int param_1)
{
    int iVar1;
    if (*(volatile int*)(0x2000751cUL + 0x24) == 0x14) {
        FUN_00072240(0x2000751cUL, 0x20010257UL, 0, 0);
    }
    FUN_00086c04(0x20010257UL, param_1, 200);
    iVar1 = FUN_000720d0(0x2000751cUL, 0x20010257UL, 0, 0);
    if (iVar1 != 0) {
        DEBUG_PRINT(0x0009b35aUL);
    }
    return iVar1;
}

