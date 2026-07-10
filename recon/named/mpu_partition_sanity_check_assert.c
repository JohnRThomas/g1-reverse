/* named: mpu_partition_sanity_check_assert */
/* Reconstructed mpu_partition_sanity_check_assert @ 0x50e64  (parity: 147/300 trials, PROVEN) */
#include <stdint.h>
extern void printk(uint32_t,...);
extern void assert_post_action(uint32_t,uint32_t);
extern int arm_cmse_mpu_region_get(int);

void mpu_partition_sanity_check_assert(int *param_1, int param_2, uint32_t param_3){
    volatile int *fp = (volatile int*)0x2000a7f4UL;
    volatile int *scb = (volatile int*)0xe000ed00UL;
    volatile uint8_t *pbVar3 = (volatile uint8_t*)0x2001d450UL;
    int iVar7 = 0;
    volatile int *piVar6 = fp;
    int *cur = param_1;
    int iVar4, iVar8, iVar5, sl;
    uint32_t r2 = 0x14;
    while (1){
        if (!(iVar7 < param_2)) return;
        sl = cur[1];
        if (sl != 0){
            iVar5 = cur[0];
            iVar4 = arm_cmse_mpu_region_get(iVar5);
            iVar8 = arm_cmse_mpu_region_get(sl + iVar5 - 1);
            r2 = 0x14;
            if (iVar4 != iVar8){
                r2 = 0xffffffeaUL;
                *piVar6 = -0x16;
                goto assert;
            }
          L_ed8:
            *piVar6 = iVar4;
            if (iVar4 == -0x16) goto assert;
            if ((int)(uint32_t)*pbVar3 <= iVar4) goto assert;
            {
                uint32_t base = (uint32_t)(uintptr_t)fp + r2 * (uint32_t)iVar7;
                volatile uint8_t *bp = (volatile uint8_t*)(uintptr_t)(base + 0xc);
                scb[0x98/4] = iVar4;
                scb[0x98/4] = iVar4;
                uint32_t v9c = (uint32_t)scb[0x9c/4];
                uint8_t bv = *bp;
                bv = (uint8_t)((bv & 0xe0) | (v9c & 0x1f));
                *bp = bv;
                uint32_t va0 = (uint32_t)scb[0xa0/4];
                uint8_t bv2 = *bp;
                va0 = va0 >> 1;
                bv2 = (uint8_t)((bv2 & 0x1f) | ((va0 & 7) << 5));
                *bp = bv2;
                uint32_t r1v = (uint32_t)scb[0x9c/4];
                piVar6[1] = (int)(r1v & 0xffffffe0UL);
                uint32_t r1v2 = (uint32_t)scb[0xa0/4];
                piVar6[4] = (int)(r1v2 & 0xffffffe0UL);
            }
        }
        iVar7 = iVar7 + 1;
        piVar6 = (volatile int*)((uint8_t*)piVar6 + 0x14);
        cur = cur + 3;
        continue;
      assert:
        printk(0x00099cbd, 0x000f7a30, 0x000f219e, 0x12b, (uint32_t)param_1, (uint32_t)iVar5, param_3);
        printk(0x000f2201, (uint32_t)param_2);
        assert_post_action(0x000f219e, 0x12b);
        goto L_ed8;
    }
}

