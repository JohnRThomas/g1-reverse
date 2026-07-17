#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000478d8 @ 0x000478d8
 * public-name: utf8_string_to_utf16
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   utf8_decode_to_utf16_buffer              <= FUN_00047844 @ 0x00047844
 *   utf8_string_to_utf16                     <= FUN_000478d8 @ 0x000478d8
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_utf16_conv_buf                         @ 0x2000f704
 */
/* Reconstructed FUN_000478d8 @ 0x478d8  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern unsigned int strlen(unsigned int);
extern unsigned short utf8_decode_to_utf16_buffer(unsigned int, unsigned int, unsigned int, int);

unsigned int utf8_string_to_utf16(unsigned int param_1, unsigned short *param_2)
{
    unsigned int uVar1 = ((unsigned long)&g_utf16_conv_buf) /*=0x2000f704*/;
    unsigned short uVar2;
    unsigned int uVar3;
    memset_bytes((void*)uVar1, 0, 0x800);
    uVar3 = strlen(param_1);
    uVar2 = utf8_decode_to_utf16_buffer(param_1, uVar3, uVar1, 0x400);
    *param_2 = uVar2;
    return uVar1;
}
