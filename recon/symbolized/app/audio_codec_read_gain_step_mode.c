#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007fc2c @ 0x0007fc2c
 * public-name: audio_codec_read_gain_step_mode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_select_page                  <= FUN_0007fb20 @ 0x0007fb20
 *   audio_codec_read_gain_step_mode          <= FUN_0007fc2c @ 0x0007fc2c
 */
/* Reconstructed FUN_0007fc2c @ 0x7fc2c  (parity: 300/300 trials, PROVEN) */

extern int audio_codec_select_page(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern int FUN_0007f97c(unsigned int, unsigned int, void*, unsigned int);

int audio_codec_read_gain_step_mode(unsigned int param_1, unsigned char *param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  int iVar2 = 0;
  unsigned char local_14;
  unsigned int uVar3;

  iVar1 = audio_codec_select_page(param_1, 2, param_3, param_4, param_1);
  if (iVar1 == 0) {
    iVar2 = FUN_0007f97c(param_1, 0x5f, &local_14, 1);
    if (iVar2 == 0) {
      uVar3 = (local_14 >> 3) & 3;
      if (uVar3==2 || uVar3==3 || uVar3==1) {
        *param_2 = (unsigned char)uVar3;
      } else {
        *param_2 = 0;
      }
    }
    iVar1 = audio_codec_select_page(param_1, 0, 0, 0, 0);
    iVar1 = iVar1 + iVar2;
  }
  return iVar1;
}
