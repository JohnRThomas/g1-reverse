#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00080cf2 @ 0x00080cf2
 * public-name: bt_settings_decode_key
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   hex2bin                                  <= FUN_0007dd0a @ 0x0007dd0a
 *   settings_name_next                       <= FUN_0007f1e8 @ 0x0007f1e8
 *   bt_settings_decode_key                   <= FUN_00080cf2 @ 0x00080cf2
 */
/* Reconstructed FUN_00080cf2 @ 0x80cf2  (parity: 300/300 trials, PROVEN) */

extern int settings_name_next(int, int);
extern void hex2bin(int, int, void*, int);

int bt_settings_decode_key(int param_1, unsigned char *param_2)
{
  int iVar1;
  int uVar2;
  unsigned char uVar3;
  int iVar4;
  unsigned char *puVar5;

  iVar1 = settings_name_next(param_1, 0);
  if (iVar1 == 0xd) {
    if (*(char*)(param_1+0xc) == 0x30) {
      uVar3 = 0;
    } else if (*(char*)(param_1+0xc) == 0x31) {
      uVar3 = 1;
    } else {
      return 0xffffffea;
    }
    puVar5 = param_2 + 6;
    *param_2 = uVar3;
    iVar1 = param_1;
    do {
      iVar4 = iVar1 + 2;
      hex2bin(iVar1, 2, puVar5, 1);
      puVar5 = puVar5 - 1;
      iVar1 = iVar4;
    } while (iVar4 != param_1 + 0xc);
    uVar2 = 0;
  } else {
    uVar2 = 0xffffffea;
  }
  return uVar2;
}
