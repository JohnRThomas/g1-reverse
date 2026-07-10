#include "g1_app_symbols.h"
/* named: count_chars_in_default_font_table */
/* globals referenced:
//   0x0008ac28  g_default_font_glyph_table_count 
*/
/* Reconstructed count_chars_in_default_font_table @ 0x43e58  (parity: 300/300 trials, PROVEN) */

int count_chars_in_default_font_table(unsigned int param_1, unsigned int param_2)
{
    int iVar1 = 0;
    int iVar2 = 0;
    unsigned int uVar3;
    int count = *(volatile int*)((uintptr_t)&g_default_font_glyph_table_count) /*=0x8ac28*/;
    while (iVar2 < count) {
        uVar3 = *(volatile unsigned short*)(((uintptr_t)&tbl_9873c) /*=0x9890c*/ + iVar2 * 4);
        iVar2 = iVar2 + 1;
        if (uVar3 == param_1) {
            iVar1 = iVar1 + 1;
        }
        if (uVar3 == param_2) {
            iVar1 = iVar1 + 1;
        }
    }
    if (iVar1 > 1) {
        iVar1 = 2;
    }
    return iVar1;
}

