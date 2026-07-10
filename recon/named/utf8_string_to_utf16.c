/* named: utf8_string_to_utf16 */
/* Reconstructed utf8_string_to_utf16 @ 0x478d8  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern unsigned int strlen(unsigned int);
extern unsigned short utf8_decode_to_utf16_buffer(unsigned int, unsigned int, unsigned int, int);

unsigned int utf8_string_to_utf16(unsigned int param_1, unsigned short *param_2)
{
    unsigned int uVar1 = 0x2000f704U;
    unsigned short uVar2;
    unsigned int uVar3;
    memset_bytes((void*)uVar1, 0, 0x800);
    uVar3 = strlen(param_1);
    uVar2 = utf8_decode_to_utf16_buffer(param_1, uVar3, uVar1, 0x400);
    *param_2 = uVar2;
    return uVar1;
}

