/* readable reconstruction; identity: FUN_00080798 @ 0x00080798
 * public-name: mpu_configure_region
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   region_init                              <= FUN_00050bf0 @ 0x00050bf0
 *   mpu_region_alloc_fail_log                <= FUN_00050c24 @ 0x00050c24
 *   mpu_configure_region                     <= FUN_00080798 @ 0x00080798
 */
/* Reconstructed FUN_00080798 @ 0x80798  (parity: 300/300 trials, PROVEN) */

extern void mpu_region_alloc_fail_log(unsigned int);
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
        mpu_region_alloc_fail_log(param_1);
        return;
    }
    region_init(param_1, &local);
}
