/* readable reconstruction; identity: FUN_00050c54 @ 0x00050c54
 * public-name: arm_core_mpu_configure
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   region_init                              <= FUN_00050bf0 @ 0x00050bf0
 *   mpu_region_alloc_fail_log                <= FUN_00050c24 @ 0x00050c24
 *   arm_core_mpu_configure                   <= FUN_00050c54 @ 0x00050c54
 *   arm_cmse_mpu_region_get                  <= FUN_00080786 @ 0x00080786
 *   mpu_configure_region                     <= FUN_00080798 @ 0x00080798
 * address symbols (name @ address):
 *   rodata_88228                             @ 0x00088228
 *   rodata_f2158                             @ 0x000f2158
 *   rodata_f217b                             @ 0x000f217b
 */
/* Reconstructed FUN_00050c54 @ 0x50c54  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#define S98 (*(volatile uint32_t*)0xe000ed98UL)
#define S9c (*(volatile uint32_t*)0xe000ed9cUL)
#define Sa0 (*(volatile uint32_t*)0xe000eda0UL)
extern void FUN_0004d944(uint32_t, uint32_t, const void *, uint32_t);
extern int region_init(unsigned, int);
extern int mpu_region_alloc_fail_log(unsigned);
extern unsigned arm_cmse_mpu_region_get(unsigned);
extern int mpu_configure_region(unsigned, int);

unsigned arm_core_mpu_configure(unsigned *param_1, int param_2, unsigned param_3)
{
    struct diagnostic_record {
        uint32_t severity;
        uint32_t message;
        uint32_t value;
    } diagnostic;
    struct region_descriptor {
        uint32_t next_address;
        uint32_t reserved;
        uint8_t attributes;
        uint8_t padding[3];
        uint32_t boundary;
    } descriptor;
    unsigned uVar6 = 0;
    int local_3c = param_2;
    unsigned uVar2, uVar4, uVar5, uVar7, uVar8;
    int iVar3;

LOOP:
    if (local_3c <= (int)uVar6) return param_3;
    uVar4 = param_1[1];
    if (uVar4 == 0) goto NEXT;
    if (uVar4 <= 0x1f || (uVar4 & 0x1f) != 0) goto SANITY_ERROR;
    uVar7 = param_1[0];
    if ((uVar7 & 0x1f) != 0) goto SANITY_ERROR;
    uVar2 = arm_cmse_mpu_region_get(uVar7);
    uVar4 = arm_cmse_mpu_region_get(uVar4 + uVar7 - 1);
    if (uVar2 != uVar4) {
        uVar2 = 0xffffffea;
        goto REGION_ERROR;
    }
    if (uVar2 == 0xffffffea || (int)uVar2 >= (int)param_3) goto REGION_ERROR;
    S98 = uVar2;
    S98 = uVar2;
    uVar5 = Sa0 | 0x1f;
    uVar7 = param_1[0];
    uVar4 = param_1[1];
    uVar8 = uVar4 + uVar7 - 1;
    if ((S9c & 0xffffffe0) == uVar7) {
        if (uVar5 == uVar8) {
            mpu_configure_region(uVar2 & 0xff, (int)(intptr_t)param_1);
            goto NEXT;
        }
        S98 = uVar2;
        S9c = (S9c & 0x1f) | ((uVar4 + uVar7) & 0xffffffe0);
        iVar3 = mpu_configure_region(param_3 & 0xff, (int)(intptr_t)param_1);
        if (iVar3 == -0x16) return 0xffffffea;
    } else {
        uVar4 = (uVar7 - 1) & 0xffffffe0;
        S98 = uVar2;
        if (uVar5 == uVar8) {
            Sa0 = (Sa0 & 0x1f) | uVar4;
            iVar3 = mpu_configure_region(param_3 & 0xff, (int)(intptr_t)param_1);
            if (iVar3 == -0x16) return 0xffffffea;
        } else {
            Sa0 = uVar4 | (Sa0 & 0x1f);
            iVar3 = mpu_configure_region(param_3 & 0xff, (int)(intptr_t)param_1);
            if (iVar3 == -0x16) return 0xffffffea;
            S98 = uVar2;
            uVar4 = (iVar3 + 1U) & 0xff;
            descriptor.next_address = uVar7 + param_1[1];
            descriptor.attributes = (uint8_t)((S9c & 0x1f) |
                (((Sa0 >> 1) & 7) << 5));
            descriptor.boundary = (((descriptor.next_address & 0xffffffe0) +
                (uVar5 - 1)) - uVar8) & 0xffffffe0;
            if (7 < uVar4) {
                iVar3 = mpu_region_alloc_fail_log(uVar4);
                if (iVar3 == -0x16) return 0xffffffea;
            } else {
                iVar3 = region_init(uVar4, (int)(intptr_t)&descriptor);
            }
        }
    }
    param_3 = iVar3 + 1;
NEXT:
    uVar6 = uVar6 + 1;
    param_1 = param_1 + 3;
    goto LOOP;
SANITY_ERROR:
    diagnostic.message = 0x000f2158;
    diagnostic.value = uVar6;
    goto DO_LOG;
REGION_ERROR:
    diagnostic.message = 0x000f217b;
    diagnostic.value = uVar2;
DO_LOG:
    diagnostic.severity = 3;
    FUN_0004d944(0x00088228, 0x1840, &diagnostic, 0);
    return 0xffffffea;
}
