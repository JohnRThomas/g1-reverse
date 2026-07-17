/* readable reconstruction; identity: FUN_00076ed4 @ 0x00076ed4
 * public-name: _vfprintf_r
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lock_acquire_or_fatal                    <= FUN_000510fc @ 0x000510fc
 *   lock_release_or_fatal                    <= FUN_00051134 @ 0x00051134
 *   stdio_streams_init                       <= FUN_00076bcc @ 0x00076bcc
 *   _vfprintf_r                              <= FUN_00076ed4 @ 0x00076ed4
 *   vfprintf_format_engine                   <= FUN_00077594 @ 0x00077594
 *   stdio_fclose                             <= FUN_00077d54 @ 0x00077d54
 *   mem_find_byte                            <= FUN_00086bc8 @ 0x00086bc8
 *   libc_write_buffer_via_putc               <= FUN_00086cb6 @ 0x00086cb6
 * address symbols (name @ address):
 *   ADDR_FUN_0007712c_THUMB                  @ 0x0007712d
 *   ADDR_libc_write_buffer_via_putc_THUMB    @ 0x00086cb7
 *   rodata_f8b6b                             @ 0x000f8b6b
 *   rodata_f8b71                             @ 0x000f8b71
 *   rodata_f8b75                             @ 0x000f8b75
 */
/* Reconstructed FUN_00076ed4 @ 0x76ed4  (parity: 80/80 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned undefined4;
typedef unsigned char undefined1;
extern void lock_acquire_or_fatal(unsigned a);
extern void lock_release_or_fatal(unsigned a);
extern void stdio_streams_init(void);
extern int FUN_0007712c(int a, void *b, int c, unsigned d, void *e);
extern int vfprintf_format_engine(int a, void *b, int c, unsigned d, void *e);
extern int stdio_fclose(int a, int b);
extern int mem_find_byte(unsigned a, unsigned b, ...);
extern int libc_write_buffer_via_putc(int a, int b, unsigned char *c, int d);

int _vfprintf_r(int param_1, int param_2, unsigned char *param_3, uint *param_4)
{
    int iVar1, iVar2, iVar8;
    uint *puVar3;
    int bVar4;
    uint uVar5;
    unsigned char *pbVar6, *pbVar7;
    int unaff_r7 = 0;
    uint *local_8c;
    uint local_88, local_84, local_7c;
    undefined4 uStack_80;
    int local_74;
    unsigned char local_70;
    undefined1 local_6f, local_6e, local_45;
    undefined4 local_30;

    if ((param_1 != 0) && (*(volatile int *)(param_1 + 0x18) == 0)) {
        stdio_streams_init();
    }
    if (param_2 == 0x9871c) param_2 = *(volatile int *)(param_1 + 4);
    else if (param_2 == 0x986fc) param_2 = *(volatile int *)(param_1 + 8);
    else if (param_2 == 0x986dc) param_2 = *(volatile int *)(param_1 + 0xc);
    if ((-1 < *(volatile int *)(param_2 + 100) << 0x1f) &&
        (-1 < (int)((uint)*(volatile unsigned short *)(param_2 + 0xc) << 0x16))) {
        lock_acquire_or_fatal(*(volatile unsigned *)(param_2 + 0x58));
    }
    if (((-1 < (int)((uint)*(volatile unsigned short *)(param_2 + 0xc) << 0x1c)) || (*(volatile int *)(param_2 + 0x10) == 0)) &&
        (iVar1 = stdio_fclose(param_1, param_2), iVar1 != 0)) {
        if ((-1 < *(volatile int *)(param_2 + 100) << 0x1f) &&
            (-1 < (int)((uint)*(volatile unsigned short *)(param_2 + 0xc) << 0x16))) {
            lock_release_or_fatal(*(volatile unsigned *)(param_2 + 0x58));
        }
        return -1;
    }
    local_74 = 0;
    local_6f = 0x20;
    local_6e = 0x30;
    pbVar7 = param_3;
    local_8c = param_4;
LAB_00076f6a:
    pbVar6 = pbVar7;
    if (*pbVar6 != 0) goto code_r0x00076f72;
    goto LAB_00076f76;
code_r0x00076f72:
    pbVar7 = pbVar6 + 1;
    if (*pbVar6 != 0x25) goto LAB_00076f6a;
LAB_00076f76:
    iVar8 = (int)pbVar6 - (int)param_3;
    if (iVar8 != 0) {
        iVar2 = libc_write_buffer_via_putc(param_1, param_2, param_3, iVar8);
        if (iVar2 == -1) {
LAB_000770da:
            if ((-1 < *(volatile int *)(param_2 + 100) << 0x1f) &&
                (-1 < (int)((uint)*(volatile unsigned short *)(param_2 + 0xc) << 0x16))) {
                lock_release_or_fatal(*(volatile unsigned *)(param_2 + 0x58));
            }
            if ((int)((uint)*(volatile unsigned short *)(param_2 + 0xc) << 0x19) < 0) return -1;
            return local_74;
        }
        local_74 = local_74 + iVar8;
    }
    if (*pbVar6 == 0) goto LAB_000770da;
    local_88 = 0;
    local_7c = 0;
    local_45 = 0;
    local_30 = 0;
    local_84 = 0xffffffff;
    uStack_80 = 0;
    pbVar7 = pbVar6 + 1;
    while (1) {
        pbVar6 = pbVar7 + 1;
        iVar2 = mem_find_byte(0xf8b6b, *pbVar7);
        iVar8 = 0xf8b71;
        if (iVar2 == 0) break;
        local_88 = 1 << (iVar2 - 0xf8b6b & 0xffU) | local_88;
        pbVar7 = pbVar6;
    }
    if ((int)(local_88 << 0x1b) < 0) local_45 = 0x20;
    if ((int)(local_88 << 0x1c) < 0) local_45 = 0x2b;
    if (*pbVar7 == 0x2a) {
        puVar3 = local_8c + 1;
        uVar5 = *local_8c;
        local_8c = puVar3;
        if ((int)uVar5 < 0) {
            local_88 = local_88 | 2;
            uVar5 = -uVar5;
        }
    } else {
        bVar4 = 0;
        uVar5 = local_7c;
        pbVar6 = pbVar7;
        while (1) {
            if (9 < (unsigned char)(*pbVar6 - 0x30)) break;
            uVar5 = uVar5 * 10 + (*pbVar6 - 0x30);
            bVar4 = 1;
            pbVar6 = pbVar6 + 1;
        }
        if (!bVar4) uVar5 = local_7c;
    }
    local_7c = uVar5;
    if (*pbVar6 == 0x2e) {
        if (pbVar6[1] == 0x2a) {
            pbVar6 = pbVar6 + 2;
            uVar5 = *local_8c;
            local_8c = local_8c + 1;
            local_84 = uVar5 | (int)uVar5 >> 0x1f;
        } else {
            bVar4 = 0;
            uVar5 = 0;
            local_84 = 0;
            while (1) {
                pbVar6 = pbVar6 + 1;
                if (9 < (unsigned char)(*pbVar6 - 0x30)) break;
                uVar5 = uVar5 * 10 + (*pbVar6 - 0x30);
                bVar4 = 1;
            }
            if (bVar4) local_84 = uVar5;
        }
    }
    iVar2 = mem_find_byte(0xf8b71, *pbVar6, 3);
    if (iVar2 != 0) {
        pbVar6 = pbVar6 + 1;
        local_88 = local_88 | 0x40 << (iVar2 - iVar8 & 0xffU);
    }
    param_3 = pbVar6 + 1;
    local_70 = *pbVar6;
    iVar8 = mem_find_byte(0xf8b75, local_70, 6);
    if (iVar8 == 0) {
        unaff_r7 = vfprintf_format_engine(param_1, &local_88, param_2, 0x86cb7, &local_8c);
    } else {
        if (0x7712d == 0) {
            local_8c = (uint *)(((int)local_8c + 7U & 0xfffffff8) + 8);
            goto LAB_00077088;
        }
        unaff_r7 = FUN_0007712c(param_1, &local_88, param_2, 0x86cb7, &local_8c);
    }
    if (unaff_r7 == -1) goto LAB_000770da;
LAB_00077088:
    local_74 = local_74 + unaff_r7;
    pbVar7 = param_3;
    goto LAB_00076f6a;
}
