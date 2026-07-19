/* readable reconstruction; identity: FUN_0004fa1c @ 0x0004fa1c
 * public-name: aes_sub_bytes
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   aes_sub_bytes                            <= FUN_0004fa1c @ 0x0004fa1c
 * address symbols (name @ address):
 *   rodata_f1968                             @ 0x000f1968
 */
/* Reconstructed FUN_0004fa1c @ 0x4fa1c  (parity: 300/300 trials, PROVEN) */

void aes_sub_bytes(unsigned char *param_1)
{
    unsigned char *pbVar2 = param_1 - 1;
    do {
        pbVar2 = pbVar2 + 1;
        *pbVar2 = *(volatile unsigned char*)(0xf1968UL + *pbVar2);
    } while (pbVar2 != param_1 + 0xf);
}
