/* readable reconstruction; identity: FUN_01012c08 @ 0x01012c08
 * public-name: sdc_conn_timing_fault
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_conn_timing_fault                    <= FUN_01012c08 @ 0x01012c08
 */
/* net-core FUN_01012c08 @ 0x1012c08 */

extern void sdc_assertion_fail(unsigned int, unsigned int, unsigned int, unsigned int);

void sdc_conn_timing_fault(unsigned int unused_1, unsigned int unused_2,
                  unsigned int arg_3, unsigned int arg_4)
{
    for (;;)
        sdc_assertion_fail(6, 0x35b, arg_3, arg_4);
}
