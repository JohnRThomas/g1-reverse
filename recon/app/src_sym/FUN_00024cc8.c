/* Reconstructed FUN_00024cc8 @ 0x24cc8  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007ca24(int a, void *b);
extern void FUN_0007c99e(int a, void *b);

char FUN_00024cc8(int param_1)
{
    char local_19;
    int local_18;
    int local_14;

    local_19 = 0;
    FUN_0007ca24(*(volatile int *)0x20007a44UL /* device_info.gap_1030+24 */, &local_19);
    if (local_19 == 0) {
        if (param_1 == 0) goto LAB_00024cf4;
        local_14 = 0;
        local_18 = 0;
    } else {
        if ((local_19 != 1) || (param_1 != 0)) goto LAB_00024cf4;
        local_18 = 0x12345678;
        local_14 = 0x12345678 + 0xf00000;
    }
    FUN_0007c99e(*(volatile int *)0x20007a44UL /* device_info.gap_1030+24 */, &local_18);
LAB_00024cf4:
    FUN_0007ca24(*(volatile int *)0x20007a44UL /* device_info.gap_1030+24 */, &local_19);
    return local_19;
}

