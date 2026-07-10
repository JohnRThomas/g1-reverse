/* net-core FUN_0101f934 @ 0x101f934  (parity 300 trials PROVEN) */

extern unsigned char FUN_01028486(unsigned char a);
extern void FUN_0100efc8(void *a, unsigned int b, unsigned int c);

void FUN_0101f934(int param_1, unsigned char param_2)
{
    unsigned char *base = *(unsigned char **)(param_1 + 4);
    unsigned short v0 = *(unsigned short *)(base + 0);
    unsigned char r;
    *(unsigned char *)(base + 0x20b) = param_2;
    *(unsigned short *)(base + 0x20c) = v0;
    r = FUN_01028486(*(unsigned char *)(base + 0x6e));
    *(unsigned char *)(base + 0x20e) = r;
    r = FUN_01028486(*(unsigned char *)(base + 0x6f));
    *(unsigned char *)(base + 0x20f) = r;
    FUN_0100efc8(base + 0x202, 0x01029e3d, 2);
    *(unsigned char *)(base + 0x16c) = 0;
}

