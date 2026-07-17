/* readable reconstruction; identity: FUN_0002542c @ 0x0002542c
 * public-name: refresh_box_field_timer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   refresh_box_field_timer                  <= FUN_0002542c @ 0x0002542c
 * address symbols (name @ address):
 *   g_box_field_timer                        @ 0x20007a24
 *   g_box_field_raw_timestamp                @ 0x20007a34
 */
/* Reconstructed FUN_0002542c @ 0x2542c  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007c830(unsigned int);
void refresh_box_field_timer(void)
{
  unsigned int *puVar1 = (unsigned int *)0x20007a34UL;
  FUN_0007c830(0x20007a34UL);
  *(volatile unsigned int *)0x20007a24UL = *(volatile unsigned int *)puVar1;
}
