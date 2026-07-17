/* readable reconstruction; identity: FUN_0003cf34 @ 0x0003cf34
 * public-name: clear_notification_display_buffer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   clear_notification_display_buffer        <= FUN_0003cf34 @ 0x0003cf34
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_notification_display_buffer            @ 0x20004988
 */
/* Reconstructed FUN_0003cf34 @ 0x3cf34  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void memset_bytes(void*,int,int);
void clear_notification_display_buffer(void)
{
  memset_bytes((void*)0x20004988UL,0,0x230);
  return;
}
