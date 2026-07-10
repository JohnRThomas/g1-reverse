/* Reconstructed FUN_00087340 @ 0x87340  (parity: 300/300 trials, PROVEN) */

char FUN_00087340(int param_1)
{
    char cVar1 = (char)param_1;
    if ((unsigned int)(param_1 - 0x30) < 10) {
        cVar1 = cVar1 - 0x20;
    } else if ((unsigned int)(param_1 - 0x61) < 6) {
        cVar1 = cVar1 - 0x47;
    } else if ((unsigned int)(param_1 - 0x41) < 6) {
        cVar1 = cVar1 - 0x27;
    } else {
        return 0;
    }
    return cVar1;
}

