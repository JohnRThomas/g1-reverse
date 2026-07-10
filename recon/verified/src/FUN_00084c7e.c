/* Reconstructed FUN_00084c7e @ 0x84c7e  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00083dc8(unsigned int, unsigned int, unsigned int, unsigned int);

unsigned int FUN_00084c7e(void *param_1, int param_2)
{
    unsigned int *p = *(volatile unsigned int**)((char*)param_1 + 4);
    if (param_2 == 0) {
        return FUN_00083dc8(*(volatile unsigned int*)p, 7, 4, 1);
    }
    return 0xffffffea;
}

