/* readable reconstruction; identity: FUN_0100e808 @ 0x0100e808
 * public-name: FUN_0100e808
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100e808 @ 0x100e808  (CFG-directed candidate) */
void FUN_0100e808(unsigned char *dst, const unsigned int *src)
{
    unsigned int *out = (unsigned int *)(dst + 4);
    unsigned int i;
    for (i = 0; i != 8; i += 4) {
        out[i] = src[i];
        out[i + 1] = src[i + 1];
        out[i + 2] = src[i + 2];
        out[i + 3] = src[i + 3];
    }
    *(unsigned short *)(out + 8) = *(const unsigned short *)(src + 8);
}
