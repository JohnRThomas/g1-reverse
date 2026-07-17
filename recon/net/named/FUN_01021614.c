/* readable reconstruction; identity: FUN_01021614 @ 0x01021614
 * public-name: FUN_01021614
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103c5c4                           @ 0x0103c5c4
 */
/* net-core FUN_01021614 @ 0x1021614  (parity 300 trials PROVEN) */

#define DAT_0102162c ((unsigned int)0x0103c5c4)
#define DAT_01021630 ((unsigned int)0x10624dd3)

int FUN_01021614(int param_1, int param_2)
{
    unsigned short v = *(volatile unsigned short *)(DAT_0102162c + param_2 * 2);
    unsigned long long prod = (unsigned long long)DAT_01021630 * (unsigned long long)(v + 1000);
    return param_1 + (unsigned int)(prod >> 0x26);
}
