/* named: dev_channel_dispatch_range */
/* Reconstructed dev_channel_dispatch_range @ 0x84068  (parity: 300/300 trials, PROVEN) */

int dev_channel_dispatch_range(int *param_1, int param_2, int param_3)
{
    int *r6 = *(int**)((char*)param_1 + 4);
    unsigned int fptr = *(volatile unsigned int*)((char*)(*(volatile int*)((char*)param_1 + 8)) + 0x10);
    if (fptr == 0) {
        return 0xffffffa8;
    }
    if (param_2 <= r6[1] && r6[0] <= param_3) {
        return ((int(*)(int*,int,int))fptr)(param_1, param_2, param_3);
    }
    return 0xffffffea;
}

