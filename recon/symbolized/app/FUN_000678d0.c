#include "g1_app_symbols.h"
/* named: FUN_000678d0 */
/* Reconstructed FUN_000678d0 @ 0x678d0  (parity: 300/300 trials, PROVEN) */

extern void printk(int a, int b, int c, int d, int e);
extern int assert_post_action(int a, int b);

void FUN_000678d0(int *param_1, int param_2, int param_3, int param_4)
{
    unsigned char byte = *(unsigned char *)((int)param_1 + 4);
    int iVar2 = (int)((unsigned int)byte * 0x28 + ((uintptr_t)&g_nrfx_twim_cb) /*=0x2000b3cc*/);
    int r3 = iVar2;
    int r0 = (int)param_1;

    if (*(volatile char *)(iVar2 + 0x22) == 0) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "p_cb->state != NRFX_DRV_STATE_UNINITIALIZED" /*=0xf6e3a*/, "WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_twim.c" /*=0xf6fef*/, 0x176, param_4);
        r3 = 0x176;
        r0 = assert_post_action("WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_twim.c" /*=0xf6fef*/, 0x176);
    }
    *(volatile int *)(r3 + 8) = 0;
    int r2 = *(volatile int *)r0;
    *(volatile int *)(r2 + 0x308) = 0x019c0202;
    *(volatile unsigned int *)(r2 + 0x200) = *(volatile unsigned int *)(r2 + 0x200) & 0xffffe87f;
    *(volatile int *)(r2 + 0x500) = 0;
    *(volatile char *)(r3 + 0x24) = 0;
    *(volatile char *)(r3 + 0x22) = 1;
}

