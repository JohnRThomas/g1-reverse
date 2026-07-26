/* readable reconstruction; identity: FUN_01033a20 @ 0x01033a20
 * public-name: FUN_01033a20
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_crc_scratch                  @ 0x21000684
 *   g_net_radio_busy_flag                    @ 0x21006458
 *   REG_41008000                             @ 0x41008000
 */
#include "../../headers/g1_nrf_regs.h"
/* net-core FUN_01033a20 @ 0x1033a20  (parity 300 trials PROVEN) */

extern unsigned long long FUN_0103a80c(unsigned int*, int, int, unsigned int, int);
int FUN_01033a20(unsigned int *param_1, int param_2, int param_3, int param_4)
{
  volatile unsigned char *flag = (volatile unsigned char*)0x21006458;
  int uVar3;
  if (*flag == 0) {
    if (param_1 == 0) {
      uVar3 = 0xffffffea;
    } else {
      unsigned int v = *param_1;
      unsigned int *puVar1 = (unsigned int*)(0x21000684 + 4);
      *puVar1 = v;
      unsigned long long uVar4 = FUN_0103a80c(puVar1, 0, param_3, v, param_4);
      uVar3 = (int)(uVar4 >> 32);
      unsigned int uVar2 = (unsigned int)uVar4;
      *(volatile unsigned int*)(G1_NRF_RADIO_NS_BASE + 0x520) =
           (uVar2 << 24) | ((uVar2 >> 8 & 0xff) << 16) | ((uVar2 >> 16 & 0xff) << 8) | (uVar2 >> 24);
    }
  } else {
    uVar3 = 0xfffffff0;
  }
  return uVar3;
}
