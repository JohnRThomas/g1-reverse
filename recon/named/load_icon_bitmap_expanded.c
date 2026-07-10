/* named: load_icon_bitmap_expanded */
/* Reconstructed load_icon_bitmap_expanded @ 0x47a4c  (parity: 300/300 trials, PROVEN) */

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

