/* readable reconstruction; identity: FUN_00043e58 @ 0x00043e58
 * public-name: count_chars_in_default_font_table
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   count_chars_in_default_font_table        <= FUN_00043e58 @ 0x00043e58
 * address symbols (name @ address):
 *   g_default_font_glyph_table_count         @ 0x0008ac28
 *   rodata_9890c                             @ 0x0009890c
 */
/* Reconstructed FUN_00043e58 @ 0x43e58  (parity: 300/300 trials, PROVEN) */

int count_chars_in_default_font_table(unsigned int param_1, unsigned int param_2)
{
    int iVar1 = 0;
    int iVar2 = 0;
    unsigned int uVar3;
    int count = *(volatile int*)0x8ac28UL;
    while (iVar2 < count) {
        uVar3 = *(volatile unsigned short*)(0x9890cUL + iVar2 * 4);
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
