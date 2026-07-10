#include "g1_app_symbols.h"
/* named: FUN_00034808 */
/* Reconstructed FUN_00034808 @ 0x34808  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int msg_content_used_count(void);
extern int is_msg_expiration(void);
extern int msg_content_check_timeout_state(void);

int FUN_00034808(void)
{
  int iVar2 = msg_content_used_count();
  volatile char *pcVar1 = (volatile char*)((uintptr_t)&g_message_pending_state) /*=0x2001a229*/;
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

