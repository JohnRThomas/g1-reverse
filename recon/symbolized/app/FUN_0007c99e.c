#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c99e @ 0x0007c99e
 * public-name: FUN_0007c99e
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_ept_op_c_locked_retry                <= FUN_00025850 @ 0x00025850
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_0007c99e @ 0x7c99e  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int ipc_ept_op_c_locked_retry(int,int,void*,int);
extern int memset_bytes(void*,int,int);
void FUN_0007c99e(int param_1, uint32_t *param_2){
  uint8_t s[28];
  *(volatile uint32_t*)(s+0) = 0;
  memset_bytes(s+4, 0, 0xd);
  uint32_t uVar6 = param_2[0];
  uint32_t uVar5 = param_2[1];
  s[8] = 9;
  uint32_t shift = 0x18;
  int k=0;
  do {
    uint8_t A = (uint8_t)(uVar6 >> shift);
    uint8_t B = (uint8_t)(uVar5 >> shift);
    s[k]    = A;
    s[k+4]  = B;
    s[k+9]  = A;
    s[k+13] = B;
    shift -= 8;
    k++;
  } while(shift != 0xfffffff8);
  ipc_ept_op_c_locked_retry(param_1, 0x900, s, 0x11);
}
