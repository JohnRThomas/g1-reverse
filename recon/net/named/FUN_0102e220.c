/* readable reconstruction; identity: FUN_0102e220 @ 0x0102e220
 * public-name: FUN_0102e220
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103bfec                           @ 0x0103bfec
 *   rodata_103c0ec                           @ 0x0103c0ec
 */
/* net-core FUN_0102e220 @ 0x102e220  (parity 300 trials PROVEN) */

#define DAT_0102e234 ((unsigned int)0x0103bfec)
#define DAT_0102e238 ((unsigned int)0x0103c0ec)

unsigned int FUN_0102e220(unsigned int param_1, unsigned int param_2)
{
    unsigned int uVar1;
    if (param_2 < (unsigned int)(DAT_0102e238 - DAT_0102e234) >> 3) {
        uVar1 = *(volatile unsigned int *)(DAT_0102e234 + param_2 * 8);
    } else {
        uVar1 = 0;
    }
    return uVar1;
}
