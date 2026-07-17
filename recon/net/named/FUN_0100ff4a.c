/* readable reconstruction; identity: FUN_0100ff4a @ 0x0100ff4a
 * public-name: FUN_0100ff4a
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_procedure_reference_release   <= FUN_0100f7b0 @ 0x0100f7b0
 */
/* net-core FUN_0100ff4a @ 0x100ff4a  (parity 300 trials PROVEN) */

extern void controller_procedure_reference_release(void);

unsigned int FUN_0100ff4a(int param_1)
{
    controller_procedure_reference_release();
    *(volatile unsigned char *)(*(int *)(param_1 + 4) + 0xc6) = 0x1d;
    return 0;
}
