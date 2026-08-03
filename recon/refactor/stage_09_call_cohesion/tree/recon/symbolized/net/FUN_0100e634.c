#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100e634 @ 0x0100e634
 * public-name: FUN_0100e634
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103c190                           @ 0x0103c190
 */
/* net-core FUN_0100e634 @ 0x100e634  (CFG-directed candidate) */
extern __attribute__((noreturn)) void sdc_assertion_fail(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int); /* FUN_01008d00 @ 0x01008d00 */

void FUN_0100e634(unsigned char *out, unsigned int value, unsigned int a2, unsigned int a3)
{
    out[3] = (unsigned char)value;
    if (value <= 0x2a) {
        out[1] = *(const volatile unsigned char *)(((unsigned long)&rodata_103c190) /*=0x103c190*/ + value);
        return;
    }
    if (value == 0xff) {
        out[1] = 1;
        return;
    }
    sdc_assertion_fail(0x2a, 0x474, a2, a3, a3);
}
