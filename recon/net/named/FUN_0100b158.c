/* readable reconstruction; identity: FUN_0100b158 @ 0x0100b158
 * public-name: FUN_0100b158
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_drv_ctx                      @ 0x21000c48
 */
/* net-core FUN_0100b158 @ 0x100b158  (parity 300 trials PROVEN) */

#define DAT_0100b16c ((unsigned int)0x21000c48)

char FUN_0100b158(void)
{
    unsigned char uVar3 = *(volatile unsigned char *)(DAT_0100b16c + 0x44);
    if (uVar3 == 0) {
        *(volatile unsigned char *)(DAT_0100b16c + 0x18) = 0;
        return (char)uVar3;
    }
    return (char)0xc;
}
