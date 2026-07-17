/* readable reconstruction; identity: FUN_0100d840 @ 0x0100d840
 * public-name: FUN_0100d840
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100d840 @ 0x100d840  (CFG-directed candidate) */
extern unsigned int FUN_0100f6e8(unsigned int);

void FUN_0100d840(volatile unsigned char *dst, const volatile unsigned char *src)
{
    unsigned int i;
    unsigned char flags;
    if (dst + 1 != src) {
        *(volatile unsigned int *)(dst + 1) = *(const volatile unsigned int *)src;
        dst[5] = src[4];
    }
    flags = dst[5];
    dst[11] = 0;
    dst[5] = flags & 0x1f;
    for (i = 0; i != 5; ++i) {
        unsigned char v = (unsigned char)FUN_0100f6e8(dst[1 + i]);
        dst[6 + i] = v;
        dst[11] = (unsigned char)(dst[11] + v);
    }
}
