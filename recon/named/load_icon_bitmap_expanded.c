/* readable reconstruction; identity: FUN_00047a4c @ 0x00047a4c
 * public-name: load_icon_bitmap_expanded
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   expand_bytes_via_lut32                   <= FUN_0004790c @ 0x0004790c
 *   load_icon_bitmap_expanded                <= FUN_00047a4c @ 0x00047a4c
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_88697                             @ 0x00088697
 *   rodata_e123a                             @ 0x000e123a
 *   g_icon_bitmap_buf                        @ 0x2001d142
 */
/* Reconstructed FUN_00047a4c @ 0x47a4c  (parity: 300/300 trials, PROVEN) */

extern void expand_bytes_via_lut32(int,int,int,int,int);
extern void memcpy(int,int,int);
int load_icon_bitmap_expanded(int param_1, int param_2, int param_3, int param_4)
{
    if (param_1 == 4) {
        memcpy(0x2001d142, 0x00088697, 0x120);
    } else {
        if (param_2 < 0) {
            param_2 = param_2 + 3;
        }
        expand_bytes_via_lut32((param_2 >> 2) * param_1 + 0x000e123a, param_2 >> 2, 0x2001d142, 0x000e123a, param_4);
    }
    return 0x2001d142;
}
