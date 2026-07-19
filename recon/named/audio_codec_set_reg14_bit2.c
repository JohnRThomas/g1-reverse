/* readable reconstruction; identity: FUN_0007fe2a @ 0x0007fe2a
 * public-name: audio_codec_set_reg14_bit2
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_codec_reg_op_dispatch              <= FUN_0007f97c @ 0x0007f97c
 *   audio_codec_bus_write                    <= FUN_0007f98a @ 0x0007f98a
 *   audio_codec_select_page                  <= FUN_0007fb20 @ 0x0007fb20
 *   audio_codec_set_reg14_bit2               <= FUN_0007fe2a @ 0x0007fe2a
 */
/* Reconstructed FUN_0007fe2a @ 0x7fe2a  (parity: 300/300 trials, PROVEN) */

extern int audio_codec_select_page(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern int audio_codec_reg_op_dispatch(unsigned int, unsigned int, void*, unsigned int);
extern int audio_codec_bus_write(unsigned int, unsigned int, void*, unsigned int);

int audio_codec_set_reg14_bit2(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1, iVar2=0, iVar3=0;
  unsigned char local_1c;

  local_1c = (unsigned char)param_2;
  iVar1 = audio_codec_select_page(param_1,1,param_3,param_4,param_1);
  if (iVar1 == 0) {
    iVar2 = audio_codec_reg_op_dispatch(param_1,0x14,&local_1c,1);
    local_1c = (unsigned char)((local_1c & 0xfb) | ((param_2 & 1) << 2));
    iVar3 = audio_codec_bus_write(param_1,0x14,&local_1c,1);
    iVar1 = audio_codec_select_page(param_1,0,0,0,0);
    iVar1 = iVar2 + iVar3 + iVar1;
  }
  return iVar1;
}
