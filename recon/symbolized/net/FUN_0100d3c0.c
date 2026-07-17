#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100d3c0 @ 0x0100d3c0
 * public-name: FUN_0100d3c0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100d3c0 @ 0x100d3c0  (parity 300 trials PROVEN) */
extern unsigned int FUN_shadow_default(void);

unsigned int FUN_0100d3c0(int param_1, unsigned int param_2, unsigned int param_3, int param_4)
{
  unsigned int uVar1;
  int bVar2;
  int bVar3;
  int bVar4;

  switch (param_2) {
  case 0:
    return (unsigned int)(param_3 == 0);
  case 1:
    return (unsigned int)(param_3 - 7 < 2);
  case 2:
    return (unsigned int)(param_3 - 0xb < 3);
  case 3:
    return (unsigned int)(param_3 - 0xe < 2);
  case 4:
    return (unsigned int)(param_3 - 0x11 < 0xd);
  case 5:
    if (param_4 != 0) {
      return (unsigned int)(param_3 - 0x12 < 0xc);
    }
    if (1 < param_3 - 0x13) {
      if (*(char *)(long)(param_1 + 0x5e) == '\0') {
        return (unsigned int)(param_3 - 0x18 < 5);
      }
      return (unsigned int)(param_3 - 0x14 < 9);
    }
    break;
  case 6:
    if (3 < param_3 - 0x11) {
      if (param_3 < 0x1e) {
        uVar1 = *(unsigned char *)(long)(param_1 + 0x5e) & 1;
      } else {
        uVar1 = 0;
      }
      return uVar1;
    }
    break;
  case 7:
    return (unsigned int)(param_3 == 4);
  case 8:
    return (unsigned int)(param_3 == 1);
  case 9:
    if (param_4 != 0) {
      return (unsigned int)(param_3 == 0x10);
    }
    return (unsigned int)(param_3 == 5);
  case 10:
    return (unsigned int)(param_3 - 0x1e < 3);
  case 0xb:
    uVar1 = param_3 - 0x21;
    bVar4 = 0x2e < param_3;
    bVar2 = param_3 == 0x2f;
    if (!bVar2) {
      bVar4 = 5 < uVar1;
    }
    bVar3 = uVar1 == 6;
    if (!bVar4 || (bVar2 || bVar3)) {
      uVar1 = 1;
    }
    if (bVar4 && (!bVar2 && !bVar3)) {
      uVar1 = 0;
    }
    return uVar1;
  case 0xc:
    return (unsigned int)(param_3 == 0x29);
  case 0xd:
    return (unsigned int)(param_3 - 0x2a < 5);
  default:
    return FUN_shadow_default();
  }
  return 1;
}
