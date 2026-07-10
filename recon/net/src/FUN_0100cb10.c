/* net-core FUN_0100cb10 @ 0x100cb10  (parity 300 trials PROVEN) */

extern int FUN_0101fd20(void);
extern unsigned int FUN_0101fd8c(void);

unsigned int FUN_0100cb10(void)
{
    int r = FUN_0101fd20();
    if (r == 0) return 0xff;
    return FUN_0101fd8c();
}

