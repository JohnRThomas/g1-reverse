/* readable reconstruction; identity: FUN_010208b0 @ 0x010208b0
 * public-name: FUN_010208b0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_010208b0 @ 0x10208b0  (parity 300 trials PROVEN) */

#define DAT_010208c8 ((unsigned int)0x41008000)

void FUN_010208b0(void)
{
    unsigned int iVar1 = DAT_010208c8;
    *(volatile unsigned int *)(DAT_010208c8 + 0x200) = *(volatile unsigned int *)(DAT_010208c8 + 0x200) & 0xffffffbf;
    *(volatile unsigned int *)(iVar1 + 0x560) = 0;
    return;
}
