/* Recovered app-specific global structs (WS2). Field offsets/widths are
 * reconstructed from firmware access patterns; names are placeholders to
 * be assigned from accessing-function behavior. Instances live at fixed
 * RAM addresses (pinned via linker at assembly time). */
#ifndef G1_RECOVERED_STRUCTS_H
#define G1_RECOVERED_STRUCTS_H
#include <stdint.h>

/* @ 0x2000a018  ~248B  accessed by 24 functions */
struct g_obj_2000a018 {
    uint32_t f_0;  /* by FUN_000436f8 */
    uint32_t f_4;  /* by FUN_000436f8 */
    uint32_t f_8;  /* by FUN_000436f8 */
    uint32_t f_c;  /* by FUN_000436f8 */
    uint32_t f_10;  /* by FUN_000436f8 */
    uint32_t f_14;  /* by FUN_000436f8 */
    uint32_t f_18;  /* by FUN_000432d0 */
    uint32_t f_1c;  /* by FUN_000431b4 */
    uint8_t _pad_20[32];
    uint32_t f_40;  /* by FUN_00047028 */
    uint32_t f_44;  /* by FUN_00047028 */
    uint32_t f_48;  /* by FUN_00047698 */
    uint8_t _pad_4c[16];
    uint32_t f_5c;  /* by jdb_panel_init */
    uint8_t _pad_60[24];
    uint32_t f_78;  /* by FUN_00047ad0 */
    uint32_t f_7c;  /* by FUN_00049040 */
    uint8_t _pad_80[4];
    uint32_t f_84;  /* by FUN_0004904c */
    uint32_t f_88;  /* by FUN_0004a46c */
    uint8_t _pad_8c[12];
    uint32_t f_98;  /* by FUN_0004a500 */
    uint8_t _pad_9c[24];
    uint32_t f_b4;  /* by FUN_0004d508 */
    uint8_t _pad_b8[48];
    uint32_t f_e8;  /* by FUN_0004e3dc */
    uint32_t f_ec;  /* by FUN_0004e3c0 */
    uint8_t _pad_f0[4];
    uint32_t f_f4;  /* by FUN_0004e484 */
}; /* &g_obj_2000a018 @ 0x2000a018 */

/* @ 0x2000b2d0  ~180B  accessed by 15 functions */
struct g_obj_2000b2d0 {
    uint32_t f_0;  /* by FUN_00063524 */
    uint32_t f_4;  /* by FUN_0006385c */
    uint32_t f_8;  /* by FUN_00063524 */
    uint32_t f_c;  /* by FUN_00063610 */
    uint8_t _pad_10[40];
    uint32_t f_38;  /* by FUN_00063ba8 */
    uint8_t _pad_3c[4];
    uint32_t f_40;  /* by FUN_00063be0 */
    uint8_t _pad_44[8];
    uint32_t f_4c;  /* by FUN_00065190 */
    uint8_t _pad_50[4];
    uint32_t f_54;  /* by FUN_00065d3c */
    uint32_t f_58;  /* by FUN_00065d3c */
    uint32_t f_5c;  /* by FUN_00065d3c */
    uint32_t f_60;  /* by FUN_000661dc */
    uint8_t _pad_64[12];
    uint32_t f_70;  /* by FUN_00066300 */
    uint32_t f_71;  /* by FUN_00066300 */
    uint8_t _pad_75[3];
    uint32_t f_78;  /* by FUN_00066994 */
    uint8_t _pad_7c[44];
    uint32_t f_a8;  /* by FUN_00066994 */
    uint8_t _pad_ac[4];
    uint32_t f_b0;  /* by FUN_00066994 */
}; /* &g_obj_2000b2d0 @ 0x2000b2d0 */

/* @ 0x2000ae9c  ~180B  accessed by 9 functions */
struct g_obj_2000ae9c {
    uint32_t f_0;  /* by FUN_000596c0 */
    uint8_t _pad_4[52];
    uint32_t f_38;  /* by FUN_00059b5c */
    uint32_t f_39;  /* by FUN_00059b5c */
    uint8_t _pad_3d[43];
    uint32_t f_68;  /* by FUN_00059cb4 */
    uint8_t _pad_6c[8];
    uint32_t f_74;  /* by FUN_0005a9d8 */
    uint8_t _pad_78[4];
    uint32_t f_7c;  /* by FUN_00059c70 */
    uint8_t _pad_80[44];
    uint32_t f_ac;  /* by FUN_0005cc30 */
    uint32_t f_b0;  /* by FUN_0005e758 */
}; /* &g_obj_2000ae9c @ 0x2000ae9c */

#endif
