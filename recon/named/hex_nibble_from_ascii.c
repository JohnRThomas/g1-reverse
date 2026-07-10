/* named: hex_nibble_from_ascii */
/* Reconstructed hex_nibble_from_ascii @ 0x87340  (parity: 300/300 trials, PROVEN) */

char hex_nibble_from_ascii(int param_1)
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

