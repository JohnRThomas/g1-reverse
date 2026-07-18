/* readable reconstruction; identity: FUN_0004df34 @ 0x0004df34
 * public-name: FUN_0004df34
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_output_dropped_process               <= FUN_0004de68 @ 0x0004de68
 * address symbols (name @ address):
 *   rodata_8ad08                             @ 0x0008ad08
 */
/* Reconstructed FUN_0004df34 @ 0x4df34  owned extent: 0x8 bytes */

extern void log_output_dropped_process(void *stream);

void FUN_0004df34(void)
{
    log_output_dropped_process((void *)0x0008ad08u);
}
