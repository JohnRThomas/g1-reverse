/* Reconstructed FUN_0007c456 @ 0x7c456  (parity: 300/300 trials, PROVEN) */

int FUN_0007c456(unsigned char *param_1, int *param_2)
{
    if (param_1 == 0 || param_2 == 0) return 7;
    if (!(param_2[0] != 0 || param_2[1] == 0)) return 7;
    unsigned char b = *(volatile unsigned char*)param_1;
    b = b & 0xef;
    *(volatile unsigned char*)param_1 = b;
    unsigned int p1 = *(volatile unsigned int*)((char*)param_2+4);
    unsigned int flag = (p1 > 0xff) ? 0 : 1;
    b = (b & 0xef) | (flag << 4);
    *(volatile unsigned char*)param_1 = b;
    *(volatile unsigned int*)((char*)param_1+0xc) = *(volatile unsigned int*)param_2;
    *(volatile unsigned int*)((char*)param_1+0x10) = *(volatile unsigned int*)((char*)param_2+4);
    return 0;
}

