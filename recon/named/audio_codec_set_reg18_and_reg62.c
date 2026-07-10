/* named: audio_codec_set_reg18_and_reg62 */
/* Reconstructed audio_codec_set_reg18_and_reg62 @ 0x7fb7a  (parity: 300/300 trials, PROVEN) */
extern int audio_codec_bus_read_trampoline(unsigned,int,void*,int);
extern int audio_codec_bus_write_trampoline(unsigned,int,void*,int);
int audio_codec_set_reg18_and_reg62(unsigned param_1, unsigned param_2){
    unsigned local_18 = param_1;
    unsigned local_14 = param_2;
    int iVar1 = audio_codec_bus_read_trampoline(param_1, 0x18, &local_14, 1);
    { unsigned char* p=(unsigned char*)&local_14; *p = (*p & 0xfd) | (((param_2>>7)&1)<<1); }
    int iVar2 = audio_codec_bus_write_trampoline(param_1, 0x18, &local_14, 1);
    iVar1 = iVar1 + iVar2;
    if (iVar1 == 0){
        iVar2 = audio_codec_bus_read_trampoline(param_1, 0x62, &local_18, 1);
        { unsigned char* p=(unsigned char*)&local_18; *p = (*p & 0xe7) | ((param_2 & 3)<<3); }
        iVar1 = audio_codec_bus_write_trampoline(param_1, 0x62, &local_18, 1);
        iVar1 = iVar1 + iVar2;
    }
    return iVar1;
}

