#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01033d20 @ 0x01033d20
 * public-name: FUN_01033d20
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01033d20 @ 0x1033d20  (P4 iteration 25; parity 300/300 directed+randomized trials, 0 mismatches) */
/* Undo of FUN_01033cd0 @ 0x01033d20 (Ghidra-gap leaf, extent 0x2a): DPPIC
 * CHENCLR for g_net_radio_trx_ppi_ch_e and clear the three endpoints.
 */
void FUN_01033d20(void)
{
    unsigned int ch = *(volatile unsigned char *)((unsigned long)&g_net_radio_trx_ppi_ch_e) /*=0x2100645e*/;
    *(volatile unsigned int *)(0x4100f000u + 0x508u) = 1u << ch;
    *(volatile unsigned int *)(0x41019000u + 0x1c4u) = 0u;
    *(volatile unsigned int *)(0x41008000u + 0x80u) = 0u;
    *(volatile unsigned int *)(0x41014000u + 0x98u) = 0u;
}
