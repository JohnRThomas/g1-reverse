/* Reconstructed FUN_0007d0aa @ 0x7d0aa  (parity: 300/300 trials, PROVEN) */

extern void FUN_000302f8(unsigned int, int*);

void FUN_0007d0aa(int *param_1)
{
    FUN_000302f8(0x1c04, param_1);
    *(volatile int*)param_1 = *(volatile int*)param_1 >> 10;
}

