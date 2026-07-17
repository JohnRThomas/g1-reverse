/* readable reconstruction; identity: FUN_01016828 @ 0x01016828
 * public-name: FUN_01016828
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 */
/* Reconstructed net-core assertion wrapper @ 0x01016828. */
extern void sdc_assertion_fail(unsigned int module, unsigned int line);

void FUN_01016828(void)
{
    sdc_assertion_fail(0x32, 0x439);
}
