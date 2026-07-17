#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007fe72 @ 0x0007fe72
 * public-name: audio_codec_get_reg14_bit2
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_select_page                  <= FUN_0007fb20 @ 0x0007fb20
 *   audio_codec_get_reg14_bit2               <= FUN_0007fe72 @ 0x0007fe72
 */
/* Reconstructed FUN_0007fe72 @ 0x7fe72  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007f97c(int, int, void*, int);
extern int audio_codec_select_page(int, int, ...);

int audio_codec_get_reg14_bit2(int param_1, unsigned char *param_2, int param_3, int param_4)
{
  int iVar1, iVar2;
  int dummy;
  iVar1 = audio_codec_select_page(param_1, 1, param_3, param_4, param_1);
  if (iVar1 == 0) {
    iVar1 = FUN_0007f97c(param_1, 0x14, &dummy, 1);
    *param_2 = (unsigned char)(((unsigned int)(unsigned long)param_2 >> 2) & 1);
    iVar2 = audio_codec_select_page(param_1, 0);
    iVar1 = iVar1 + iVar2;
  }
  return iVar1;
}
