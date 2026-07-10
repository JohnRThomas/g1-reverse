/* Reconstructed FUN_0005e3e0 @ 0x5e3e0  (parity: 300/300 trials, PROVEN) */

extern void FUN_00083074(unsigned int, int, void*);
extern void FUN_0005daf0(int, int);
extern void atomic_set_bit(int, int);

void smp_timeout(int param_1)
{
    unsigned int local_10_arr[2];
    local_10_arr[0] = 2;
    local_10_arr[1] = 0xf51ecUL;
    FUN_00083074(0x88180UL, 0x1040, local_10_arr);
    FUN_0005daf0(param_1 - 0x208, 8);
    atomic_set_bit(param_1 - 0x204, 4);
}

