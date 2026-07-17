/* readable reconstruction; identity: FUN_00034808 @ 0x00034808
 * public-name: FUN_00034808
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   msg_content_used_count                   <= FUN_00033cdc @ 0x00033cdc
 *   is_msg_expiration                        <= FUN_0003444c @ 0x0003444c
 *   msg_content_check_timeout_state          <= FUN_000347cc @ 0x000347cc
 * address symbols (name @ address):
 *   g_message_pending_state                  @ 0x2001a229
 */
/* Reconstructed FUN_00034808 @ 0x34808  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int msg_content_used_count(void);
extern int is_msg_expiration(void);
extern int msg_content_check_timeout_state(void);

int FUN_00034808(void)
{
  int iVar2 = msg_content_used_count();
  volatile char *pcVar1 = (volatile char*)0x2001a229UL;
  if (iVar2 != 0) {
    if (*pcVar1 == 5) {
      iVar2 = is_msg_expiration();
      if (iVar2 == 1) return 1;
    }
    if (*pcVar1 == 3) {
      iVar2 = msg_content_check_timeout_state();
      return iVar2 == 1;
    }
  }
  return 0;
}
