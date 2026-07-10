/* net-core FUN_010091a8 @ 0x10091a8  (parity 300 trials PROVEN) */

extern void FUN_010294be(void);
volatile unsigned char *const FUN_010091a8_base_p = (volatile unsigned char *)0x21000a30;
unsigned int FUN_010091a8(void)
{
    if (FUN_010091a8_base_p[0x2d] == 0 && FUN_010091a8_base_p[0x2c] == 0) {
        FUN_010294be();
        return 0;
    }
    return 0xffffffff;
}

