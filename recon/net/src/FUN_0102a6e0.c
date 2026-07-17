/* net-core FUN_0102a6e0 @ 0x102a6e0  (parity 300 trials PROVEN) */

extern void FUN_0103b614(void *dst, void *src, unsigned int n);
extern int FUN_010362d0(unsigned int a, void *b, int c, int d);

int FUN_0102a6e0(void *param_1)
{
    /* The protocol work area is 251 bytes; keeping its true extent also
       preserves the compiler's aligned stack slot used by the firmware. */
    unsigned char buf[251];
    int iVar1;
    FUN_0103b614(buf, (void*)0x0103c798, 0xfb);
    if (*(volatile int *)(0x210045b0 + 0x10) == 0) {
        iVar1 = 1;
    } else {
        iVar1 = FUN_010362d0(0x210045b0, buf, 0, 0);
        if (iVar1 == 0) {
            FUN_0103b614(param_1, buf, 0xfb);
        }
    }
    return iVar1;
}
