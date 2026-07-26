/* readable reconstruction; identity: FUN_0101fd20 @ 0x0101fd20
 * public-name: FUN_0101fd20
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   g_net_ccm_op_status                      @ 0x210014d8
 *   REG_4100e000                             @ 0x4100e000
 */
#include "../../headers/g1_nrf_regs.h"
/* net-core FUN_0101fd20 @ 0x101fd20  (parity 300 trials PROVEN) */

extern void sdc_assertion_fail(unsigned int, unsigned int) __attribute__((noreturn));

unsigned int FUN_0101fd20(void)
{
    volatile unsigned char *base = (volatile unsigned char*)0x210014d8;
    unsigned char flagset = base[0];
    unsigned char val = base[1];
    unsigned int r0 = val;
    if (flagset != 0) r0 = 2;
    unsigned int r4 = (r0 == 2) ? 1u : 0u;

    if (flagset == 0) {
        unsigned char r3 = 0xc8;
        while (1) {
            r3 = (unsigned char)(r3 - 1);
            if (r3 == 0) break;
            if (r4 == 0) break;
        }
        if (r0 == 2) {
            sdc_assertion_fail(0x3b, 0x104);
        }
        return (r0 == 1) ? 1u : 0u;
    } else {
        volatile unsigned char *e000 = (volatile unsigned char*)G1_NRF_AAR_NS_BASE;
        unsigned char r3 = 0xc8;
        while (1) {
            r3 = (unsigned char)(r3 - 1);
            unsigned int v100 = *(volatile unsigned int*)(e000 + 0x100);
            if (v100 != 0) {
                unsigned int uVar2 = *(volatile unsigned int*)(e000 + 0x104);
                if (uVar2 != 0) {
                    uVar2 = (*(volatile unsigned int*)(e000 + 0x108) == 0) ? 1u : 0u;
                }
                return uVar2;
            }
            if (r3 == 0 || r4 == 0) break;
        }
        sdc_assertion_fail(0x3b, 0x104);
    }
}
