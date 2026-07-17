/* readable reconstruction; identity: FUN_00025458 @ 0x00025458
 * public-name: is_box_field_timer_expired
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   refresh_box_field_timer                  <= FUN_0002542c @ 0x0002542c
 *   is_box_field_timer_expired               <= FUN_00025458 @ 0x00025458
 * address symbols (name @ address):
 *   g_box_field_timer                        @ 0x20007a24
 */
/* Reconstructed FUN_00025458 @ 0x25458  (parity: 300/300 trials, PROVEN) */

extern void refresh_box_field_timer(void);

unsigned int is_box_field_timer_expired(void)
{
    refresh_box_field_timer();
    return (*(volatile unsigned int*)0x20007a24UL) > 0x13ec;
}
