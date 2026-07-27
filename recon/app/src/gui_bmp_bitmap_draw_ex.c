/* Reconstructed gui_bmp_bitmap_draw_ex @ 0x435d4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0007dda4(unsigned long, ...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_000431a8(void);
extern int FUN_0004588c(int,...);
extern int FUN_000471cc(int,...);
extern int FUN_00047260(int,...);
extern int FUN_0007d53a(int,...);
extern int FUN_00086c04(int,...);

unsigned int gui_bmp_bitmap_draw_ex(unsigned int param_1, int param_2, int param_3, int param_4, unsigned char param_5)
{
    int iVar3;
    unsigned int uVar5;
    struct {
        int width;
        int height;
        unsigned int data_offset;
    } metadata;

    if (param_5 == 0) {
        if (*(volatile int*)0x2000230cUL < 2) return 0xffffffff;
        iVar3 = *(volatile int*)0x20007554UL;
        uVar5 = 0x000aa923;
    } else {
        iVar3 = FUN_0004588c(4, param_1, &metadata.width,
                            &metadata.height, &metadata.data_offset, 0);
        if (iVar3 >= 0) {
            int cnt = metadata.height * (metadata.width / 2);
            FUN_00086c04(param_4, metadata.data_offset, cnt);
            for (int i = 0; i < cnt; i++) {
                unsigned char *p = (unsigned char*)(intptr_t)(param_4) + i;
                if (*p != 0) *p = *p & param_5;
            }
            unsigned int m = FUN_000431a8();
            if ((m & 2) != 0) {
                FUN_000471cc(*(volatile uint32_t*)0x2000a034UL, 0, param_2,
                             param_3, metadata.width + 2 + param_2,
                             metadata.height + param_3);
            }
            FUN_0007d53a(*(volatile uint32_t*)0x2000a034UL, param_4,
                         metadata.width / 2, metadata.height,
                         param_2, param_3);
            iVar3 = FUN_000431a8();
            if ((iVar3 << 0x1e) < 0) {
                int r = FUN_000167a8();
                unsigned int v = *(volatile uint32_t*)(intptr_t)(r + 0xeb4);
                r = FUN_000167a8();
                FUN_00047260(v, *(volatile uint32_t*)(intptr_t)(r + 0xeb8),
                             param_2, param_3,
                             metadata.width + 2 + param_2,
                             metadata.height + param_3);
            }
            return 0;
        }
        if (*(volatile int*)0x2000230cUL < 2) return 0xffffffff;
        iVar3 = *(volatile int*)0x20007554UL;
        uVar5 = 0x000aa8eb;
    }
    if (iVar3 == 0) {
        FUN_0007dda4(uVar5, 0x000aadb9);
    } else {
        FUN_00019c70(uVar5, 0x000aadb9);
    }
    return 0xffffffff;
}
