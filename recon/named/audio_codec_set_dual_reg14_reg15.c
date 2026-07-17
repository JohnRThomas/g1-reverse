/* readable reconstruction; identity: FUN_0007fa22 @ 0x0007fa22
 * public-name: audio_codec_set_dual_reg14_reg15
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_set_dual_reg14_reg15         <= FUN_0007fa22 @ 0x0007fa22
 */
/* Reconstructed FUN_0007fa22 @ 0x7fa22  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0007f97c(unsigned param_1, int, void*, int);
extern int FUN_0007f98a(unsigned param_1, int, void*, int);
void audio_codec_set_dual_reg14_reg15(unsigned param_1, unsigned param_2, unsigned param_3){
    unsigned local_18 = param_1;
    unsigned local_14 = param_2;
    unsigned uStack_10 = param_3;
    (void)uStack_10;
    int iVar1 = FUN_0007f97c(param_1, 0x14, &local_18, 1);
    if (iVar1 != 0) return;
    { unsigned char *p = (unsigned char*)&local_18;
      *p = (*p & 0x7f) | (((param_2 >> 1) & 1) << 7); }
    iVar1 = FUN_0007f98a(param_1, 0x14, &local_18, 1);
    if (iVar1 != 0) return;
    iVar1 = FUN_0007f97c(param_1, 0x15, &local_14, 1);
    if (iVar1 != 0) return;
    { unsigned char *p = (unsigned char*)&local_14;
      *p = (*p & 0xef) | ((param_2 & 1) << 4); }
    FUN_0007f98a(param_1, 0x15, &local_14, 1);
}
