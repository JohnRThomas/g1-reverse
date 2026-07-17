#include "g1_net_symbols.h"
/* net-core FUN_0101fc14 @ 0x101fc14 — true CFG extent 22 bytes (ends 0x101fc2a) */

extern void FUN_0102023c(void);
extern void FUN_01020054(void);
extern void FUN_0101fc2c(void);
extern void controller_radio_request_state_clear(void); /* FUN_0101fdc0@0x0101fdc0 */

void FUN_0101fc14(void)
{
  FUN_0102023c();
  FUN_01020054();
  FUN_0101fc2c();
  controller_radio_request_state_clear();
  return;
}
