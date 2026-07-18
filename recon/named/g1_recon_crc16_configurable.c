/* readable reconstruction; identity: FUN_0007d9c0 @ 0x0007d9c0
 * public-name: g1_recon_crc16_configurable
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_recon_crc16_configurable              <= FUN_0007d9c0 @ 0x0007d9c0
 */
/* Reconstructed FUN_0007d9c0 @ 0x7d9c0  (parity: 157/300 trials, PROVEN) */

unsigned g1_recon_crc16_configurable(unsigned seed, unsigned polynomial, unsigned xor_out,
                      int reflect_input, char reflect_output,
                      const unsigned char *src, int len){
    if (src == 0) return 0;
    if (len <= 0) return 0;
    const unsigned char *cur = src;
    const unsigned char *end = src + len;
    do {
        unsigned byte = *(volatile unsigned char*)cur; cur++;
        unsigned uVar4;
        if (reflect_input != 0){
            unsigned uVar7 = byte; int uVar6 = 7; unsigned uVar3 = 0;
            for(;;){
                unsigned t = uVar3;
                if (uVar7 & 1){ t = (t | (1u << uVar6)) & 0xff; }
                uVar3 = t;
                int cont = (uVar6 != 0);
                uVar6 = uVar6 - 1; uVar7 = uVar7 >> 1;
                if (!cont) break;
            }
            uVar4 = uVar3;
        } else { uVar4 = byte; }
        seed = seed ^ (uVar4 << 8);
        int iVar5 = 8;
        do {
            unsigned hi = seed & 0x8000;
            seed = (seed << 1) & 0xffff;
            if (hi != 0) seed = seed ^ polynomial;
            iVar5--;
        } while (iVar5 != 0);
    } while (cur != end);
    unsigned uVar4 = seed;
    if (reflect_output != 0){
        unsigned r1 = seed; int uVar3 = 0xf; uVar4 = 0;
        for(;;){
            if ((int)(r1 << 31) < 0){ uVar4 = ((1u << uVar3) | uVar4) & 0xffff; }
            int cont = (uVar3 != 0);
            uVar3 = uVar3 - 1; r1 = (r1 >> 1) & 0xffff;
            if (!cont) break;
        }
    }
    return xor_out ^ uVar4;
}
