/* readable reconstruction; identity: FUN_01024b20 @ 0x01024b20
 * public-name: FUN_01024b20
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   REG_41005000                             @ 0x41005000
 */
/* net-core FUN_01024b20 @ 0x1024b20  (parity 300 trials PROVEN) */

unsigned int FUN_01024b20(unsigned char param_1)
{
    volatile unsigned int *base = (volatile unsigned int *)0x41005000;
    unsigned int a = base[0x418/4];
    unsigned int b = base[0x418/4];
    unsigned int uVar1 = a & 0x10000;
    if (uVar1 != 0) {
        uVar1 = (unsigned int)((b & 3) == (unsigned int)param_1);
    }
    return uVar1;
}
