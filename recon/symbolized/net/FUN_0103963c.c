#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103963c @ 0x0103963c
 * public-name: FUN_0103963c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   __memcpy_chk                             <= FUN_0103b53a @ 0x0103b53a
 */
/* net-core FUN_0103963c @ 0x103963c  (parity 300 trials PROVEN) */

extern void FUN_0103b62e(void*, int, int);
extern void __memcpy_chk(void*, unsigned int, unsigned int, int);
extern void FUN_0102a698(void*);
extern void FUN_0102a4b0(void);
unsigned int FUN_0103963c(unsigned int param_1, unsigned int param_2)
{
  unsigned char buf[248];
  unsigned int local = 0;
  FUN_0103b62e(buf, 0, 0xf8);
  __memcpy_chk(&local, param_1, param_2, 0xfc);
  FUN_0102a698(&local);
  FUN_0102a4b0();
  return 0;
}
