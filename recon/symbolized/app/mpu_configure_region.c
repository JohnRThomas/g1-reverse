#include "g1_app_symbols.h"
/* named: mpu_configure_region */
/* Reconstructed mpu_configure_region @ 0x80798  (parity: 300/300 trials, PROVEN) */

extern void mpu_region_alloc_fail_log(void);
extern void region_init(unsigned int, void*);

void mpu_configure_region(unsigned int param_1, unsigned int *param_2)
{
    struct { unsigned int f0; unsigned char reserved[4]; unsigned char f8; unsigned char pad2[3]; unsigned int fc; } local;
    unsigned short h8 = *(unsigned short*)((char*)param_2 + 8);
    unsigned short ha = *(unsigned short*)((char*)param_2 + 10);
    local.f0 = param_2[0];
    local.f8 = (unsigned char)((h8 & 0x1f) | (ha << 5));
    local.fc = ((param_2[0] & ~0x1fu) + (param_2[1] - 1)) & ~0x1fu;
    if (param_1 > 7) {
        mpu_region_alloc_fail_log();
        return;
    }
    region_init(param_1, &local);
}

