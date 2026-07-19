#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083002 @ 0x00083002
 * public-name: bt_conn_security_sufficient
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   atomic_test_bit                          <= FUN_00082ff6 @ 0x00082ff6
 *   bt_conn_security_sufficient              <= FUN_00083002 @ 0x00083002
 */
/* Reconstructed FUN_00083002 @ 0x83002  (parity: 300/300 trials, PROVEN) */

extern int atomic_test_bit(int a, int b, int c, int d, unsigned int e);
unsigned char bt_conn_security_sufficient(int param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  int iVar1;
  unsigned char bVar2;
  if ((param_2 != 0) && ((*(volatile unsigned short *)(param_2 + 0xe) & 0x24) != 0)) {
    bVar2 = *(volatile unsigned char *)(param_1 + 0x14);
    if (*(volatile unsigned char *)(param_1 + 0xd) <= *(volatile unsigned char *)(param_1 + 0x14)) {
      bVar2 = *(volatile unsigned char *)(param_1 + 0xd);
    }
    if ((bVar2 < *(volatile unsigned char *)(param_2 + 0xc)) ||
       (((int)((unsigned int)*(volatile unsigned short *)(param_2 + 0xe) << 0x1a) < 0 &&
        (iVar1 = atomic_test_bit(param_1 + 4,5,param_2,param_1,param_4), iVar1 == 0)))) {
      return 0;
    }
    if ((int)((unsigned int)*(volatile unsigned char *)(param_2 + 0xd) << 0x1f) < 0) {
      if (*(volatile char *)(param_1 + 8) == 0) {
        return 0;
      }
      return 1;
    }
  }
  return 1;
}
