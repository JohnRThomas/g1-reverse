/* readable reconstruction; identity: FUN_0100ebb8 @ 0x0100ebb8
 * public-name: FUN_0100ebb8
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 */
/* net-core FUN_0100ebb8 @ 0x100ebb8 */

extern void sdc_assertion_fail(unsigned int, unsigned int, unsigned int, unsigned int);

void FUN_0100ebb8(unsigned int unused_1, unsigned int unused_2,
                  unsigned int arg_3, unsigned int arg_4)
{
    for (;;)
        sdc_assertion_fail(0x10, 0x2bf, arg_3, arg_4);
}
