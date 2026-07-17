/* net-core FUN_0100e634 @ 0x100e634  (CFG-directed candidate) */
extern __attribute__((noreturn)) void sdc_assertion_fail(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int); /* FUN_01008d00 @ 0x01008d00 */

void FUN_0100e634(unsigned char *out, unsigned int value, unsigned int a2, unsigned int a3)
{
    out[3] = (unsigned char)value;
    if (value <= 0x2a) {
        out[1] = *(const volatile unsigned char *)(0x0103c190u + value);
        return;
    }
    if (value == 0xff) {
        out[1] = 1;
        return;
    }
    sdc_assertion_fail(0x2a, 0x474, a2, a3, a3);
}
