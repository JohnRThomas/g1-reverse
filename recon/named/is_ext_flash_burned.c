/* named: is_ext_flash_burned */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed is_ext_flash_burned @ 0x32c28  (parity: 200/200 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned undefined4;
extern void DEBUG_PRINT(unsigned, ...);
extern void debug_print(unsigned, ...);
extern int calc_flash_crc(int a, unsigned b, int c);
extern void k_msleep_ticks32768_b(int a);

undefined4 is_ext_flash_burned(unsigned param_1, uint param_2, unsigned param_3)
{
    volatile int *piVar1 = (volatile int *)0x2000230c;
    volatile int *dbg = (volatile int *)0x20007554;
    int iVar5, iVar6;
    uint uVar7;
    volatile unsigned uStack_24;
    volatile unsigned short *uhi = (volatile unsigned short*)&uStack_24 + 1;

    uStack_24 = param_2;
    if (2 < *piVar1) {
        if (*dbg == 0) DEBUG_PRINT(0xa74dc, 0xa766d, param_3, 0, param_1);
        else debug_print(0);
    }
    uVar7 = 0;
    iVar6 = 0;
LAB_00032c54:
    do {
        *uhi = 0xffff;
        switch (iVar6) {
        case 1:
            iVar5 = calc_flash_crc((int)&uStack_24 + 2, 0x200000, 0x10);
            if ((iVar5 != 0) || (iVar5 = calc_flash_crc((int)&uStack_24 + 2, 0x3f8c98, 0x10), iVar5 != 0)) goto LAB_00032e38;
            if (*uhi != 0xdab9) return 1;
            if (2 < *piVar1) break;
            iVar6 = 2;
            goto LAB_00032caa;
        case 2:
            iVar5 = calc_flash_crc((int)&uStack_24 + 2, 0x500000, 0x10);
            if ((iVar5 != 0) || (iVar5 = calc_flash_crc((int)&uStack_24 + 2, 0x515768, 0x10), iVar5 != 0)) goto LAB_00032e38;
            if (*uhi != 0x1265) return 1;
            if (*piVar1 < 3) { iVar6 = 3; goto LAB_00032caa; }
            break;
        case 3:
            iVar5 = calc_flash_crc((int)&uStack_24 + 2, 0x520000, 0x10);
            if ((iVar5 != 0) || (iVar5 = calc_flash_crc((int)&uStack_24 + 2, 0x97c44f, 0x10), iVar5 != 0)) goto LAB_00032e38;
            if (*uhi != 0xdab9) return 1;
            if (*piVar1 < 3) { iVar6 = 4; goto LAB_00032caa; }
            break;
        case 4:
            iVar5 = calc_flash_crc((int)&uStack_24 + 2, 0xa20000, 0x10);
            if ((iVar5 != 0) || (iVar5 = calc_flash_crc((int)&uStack_24 + 2, 0xa2b77f, 0x10), iVar5 != 0)) goto LAB_00032e38;
            if (*uhi != 0xd412) return 1;
            if (*piVar1 < 3) { iVar6 = 5; goto LAB_00032caa; }
            break;
        case 5:
            iVar5 = calc_flash_crc((int)&uStack_24 + 2, 0xa40000, 0x10);
            if ((iVar5 != 0) || (iVar5 = calc_flash_crc((int)&uStack_24 + 2, 0xdbedcf, 0x10), iVar5 != 0)) goto LAB_00032e38;
            if (*uhi != 0xdab9) return 1;
            if (*piVar1 < 3) { iVar6 = 6; goto LAB_00032caa; }
            break;
        case 6:
            iVar5 = calc_flash_crc((int)&uStack_24 + 2, 0x180000, 0x10);
            if ((iVar5 != 0) || (iVar5 = calc_flash_crc((int)&uStack_24 + 2, 0x1af0d8, 0x10), iVar5 != 0)) goto LAB_00032e38;
            if (*uhi != 0x2632) return 1;
            if (*piVar1 < 3) return 0;
            break;
        default:
            iVar5 = calc_flash_crc((int)&uStack_24 + 2, 0x140000, 0x10);
            if ((iVar5 != 0) || (iVar5 = calc_flash_crc((int)&uStack_24 + 2, 0x17fcf8, 0x10), iVar5 != 0)) {
                iVar6 = 0;
                goto LAB_00032e38;
            }
            if (*uhi != 0xd59) return 1;
            if (*piVar1 < 3) { iVar6 = 1; goto LAB_00032caa; }
        }
        if (*dbg == 0) DEBUG_PRINT(0xa7500, 0xa766d, iVar6, *uhi);
        else debug_print(0xa7500, 0xa766d, iVar6);
        iVar6 = iVar6 + 1;
        if (iVar6 == 7) return 0;
LAB_00032caa:
        uVar7 = 0;
    } while (1);
LAB_00032e38:
    if (uVar7 == 5) return 2;
    k_msleep_ticks32768_b(100);
    uVar7 = uVar7 + 1 & 0xff;
    if (0 < *piVar1) {
        if (*dbg == 0) DEBUG_PRINT(0x9e2f1, 0xa766d, uVar7);
        else debug_print(0);
    }
    goto LAB_00032c54;
}

