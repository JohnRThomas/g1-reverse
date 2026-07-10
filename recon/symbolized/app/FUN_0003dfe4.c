#include "g1_app_symbols.h"
/* named: FUN_0003dfe4 */
/* globals referenced:
//   0x20004bb8  g_ipc_or_evt_ctx             
*/
/* Reconstructed FUN_0003dfe4 @ 0x3dfe4  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(unsigned int a, unsigned int b, unsigned int c);
unsigned int FUN_0003dfe4(void) {
  memset_bytes((g_ipc_or_evt_ctx) /*=0x20004bb8*/, 0, 0x38);
  return 0;
}

