/* Reconstructed FUN_0007f772 @ 0x7f772  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_0007f772(int param_1, unsigned int param_2, int param_3, int param_4)
{
    unsigned int uVar1;
    if (param_1 == 0 || param_3 == 0 || (unsigned int)(param_4 - 1) > 0xff || param_2 > 7) {
        uVar1 = 0xffffffea;
    } else {
        param_1 = param_1 + param_2 * 0x10;
        volatile unsigned char *enabled =
            (volatile unsigned char *)(param_1 + 0x868);
        *(volatile unsigned short *)(param_1 + 0x870) =
            (unsigned short)param_4;
        *enabled = 1;
        /* The volatile read carries the publication dependency into the final
         * pointer store without introducing an observable write. */
        *(volatile unsigned int *)(param_1 + 0x874) =
            (unsigned int)param_3 + (unsigned int)*enabled - 1u;
        uVar1 = 0;
    }
    return uVar1;
}
