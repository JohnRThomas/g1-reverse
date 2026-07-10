/* named: audio_codec_set_reg14_bit2 */
/* Reconstructed audio_codec_set_reg14_bit2 @ 0x7fe2a  (parity: 300/300 trials, PROVEN) */

extern int audio_codec_select_page(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern int audio_codec_bus_read_trampoline(unsigned int, unsigned int, void*, unsigned int);
extern int audio_codec_bus_write_trampoline(unsigned int, unsigned int, void*, unsigned int);

int audio_codec_set_reg14_bit2(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1, iVar2=0, iVar3=0;
  unsigned char local_1c;

  local_1c = (unsigned char)param_2;
  iVar1 = audio_codec_select_page(param_1,1,param_3,param_4,param_1);
  if (iVar1 == 0) {
    iVar2 = audio_codec_bus_read_trampoline(param_1,0x14,&local_1c,1);
    local_1c = (unsigned char)((local_1c & 0xfb) | ((param_2 & 1) << 2));
    iVar3 = audio_codec_bus_write_trampoline(param_1,0x14,&local_1c,1);
    iVar1 = audio_codec_select_page(param_1,0,0,0,0);
    iVar1 = iVar2 + iVar3 + iVar1;
  }
  return iVar1;
}

