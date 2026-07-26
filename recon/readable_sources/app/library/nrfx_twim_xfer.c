#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_nrfx_twim_control_block__param_0349    [param_0349; library]
 *   param_2          => struct g1_layout_twim_xfer_desc__param_0353             [param_0353; G1-original]
 * Raw function identity: 0x00067938.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00067938 @ 0x00067938
 * public-name: nrfx_twim_xfer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_twim_xfer                           <= FUN_00067938 @ 0x00067938
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   xfer_completeness_check                  <= FUN_00085316 @ 0x00085316
 *   __nrfy_internal_twim_events_process      <= FUN_0008539a @ 0x0008539a
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 *   rodata_40000                             @ 0x00040000
 *   rodata_40002                             @ 0x00040002
 *   rodata_40202                             @ 0x00040202
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6fef                             @ 0x000f6fef
 *   rodata_f707c                             @ 0x000f707c
 *   rodata_f78d1                             @ 0x000f78d1
 *   rodata_f7921                             @ 0x000f7921
 *   rodata_f7971                             @ 0x000f7971
 *   rodata_f7987                             @ 0x000f7987
 *   rodata_f799d                             @ 0x000f799d
 *   g_sram_base_word                         @ 0x20000000
 *   g_nrfx_twim_cb                           @ 0x2000b3cc
 */
/* Reconstructed FUN_00067938 @ 0x67938  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"

extern int assert_post_action(int,int);
extern int __nrfy_internal_twim_events_process(int,int);
extern int xfer_completeness_check(int,int);

#define R32(a) (*(volatile uint32_t*)(uintptr_t)(uint32_t)(a))
#define R8(a)  (*(volatile uint8_t*)(uintptr_t)(uint32_t)(a))

int nrfx_twim_xfer(int param_1, int param_2, unsigned int param_3, int param_4)
{
    uint32_t r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11;
    r7 = R8((uint32_t)param_1 + 4);
    r6 = (uint32_t)param_2;
    r8 = param_3;
    r0 = (uint32_t)param_1;
    r1 = (uint32_t)param_2;

    if (r7 > 1) goto L67956;
    r3 = R32(r6 + 4);
    if (r3 >= ((unsigned long)&rodata_10000) /*=0x10000*/) goto L67956;
    r3 = R32(r6 + 8);
    if (r3 < ((unsigned long)&rodata_10000) /*=0x10000*/) goto L6796e;

L67956:
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f707c) /*=0xf707c*/, ((unsigned long)&rodata_f6fef) /*=0xf6fef*/, 0x251, param_4);
    r1 = 0x251;
    goto L67968;

L67968:
    r0 = (uint32_t)assert_post_action(((unsigned long)&rodata_f6fef) /*=0xf6fef*/, (int)r1);
    /* falls through to L6796e (assert modeled as returning oracle) */

L6796e:
    r5 = ((unsigned long)&g_nrfx_twim_cb) /*=0x2000b3cc*/;
    r3 = R32(r5 + r7 * 0x28);
    if (r3 != 0) goto L679aa;
    r3 = R8(r1);
    if (r3 == 2) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f78d1) /*=0xf78d1*/, ((unsigned long)&rodata_f6fef) /*=0xf6fef*/, 0x259, param_4);
        r1 = 0x259;
        goto L67968;
    }
    if (r3 == 3) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f7921) /*=0xf7921*/, ((unsigned long)&rodata_f6fef) /*=0xf6fef*/, 0x25a, param_4);
        r1 = 0x25a;
        goto L67968;
    }
    /* fall through */

L679aa:
    r2 = 0;
    r3 = r7 * 0x28 + r5;              /* tbl */
    r4 = R32(r0);
    R8(r3 + 0x23) = (uint8_t)r2;
    r3 = R32(r6 + 4);
    if (r3 == 0) goto L679ca;
    r3 = R32(r6 + 0xc) & 0xe0000000;
    if (r3 != ((unsigned long)&g_sram_base_word) /*=0x20000000*/) goto L67d42;
L679ca:
    r3 = R8(r6);
    if ((uint32_t)(r3 - 2) > 1) goto L679e0;
    r3 = R32(r6 + 0x10) & 0xe0000000;
    if (r3 != ((unsigned long)&g_sram_base_word) /*=0x20000000*/) goto L67d42;
L679e0:
    r3 = 0x019c0202;
    R32(r4 + 0x308) = r3;
    r3 = r7 * 0x28 + r5;             /* tbl */
    r1 = R8(r3 + 0x24);
    r2 = r1 & 0xff;
    if (r1 == 0) goto L67a06;
    r3 = R32(r3 + 8);
    r11 = 0x0bad000b;
    R32(r4 + 0x304) = r3;
    goto L67a00;

L67a06:
    r1 = ((r8 & 0x14) == 0) ? 1 : 0;
    R8(r3 + 0x24) = (uint8_t)r1;
    r1 = R8(r6);
    R8(r3 + 0x20) = (uint8_t)r1;
    r1 = R8(r6 + 1);
    r9 = r5 + r7 * 0x28;             /* sb = tbl */
    R8(r3 + 0x21) = (uint8_t)r1;
    r1 = R32(r6 + 0xc);
    r10 = r8 & 8;                    /* sl */
    R32(r3 + 0xc) = r1;
    r1 = R32(r6 + 4);
    R32(r3 + 0x10) = r1;
    r1 = R32(r6 + 0x10);
    R32(r3 + 0x14) = r1;
    r1 = R32(r6 + 8);
    R32(r3 + 0x1c) = r8;
    R32(r3 + 0x18) = r1;
    r1 = (r8 >> 4) & 1;
    R8(r3 + 0x25) = (uint8_t)r1;
    r3 = R8(r6 + 1);
    R32(r4 + 0x588) = r3;
    R32(r4 + 0x160) = r2;
    R32(r4 + 0x148) = r2;
    R32(r4 + 0x124) = r2;
    R32(r4 + 0x104) = r2;
    r3 = r8 & 1;  if (r3 != 0) r3 = 1;
    R32(r4 + 0x550) = r3;
    r3 = r8 & 2;  if (r3 != 0) r3 = 1;
    R32(r4 + 0x540) = r3;
    r3 = R8(r6);
    if (r3 > 3) goto L67c7e;
    if (r3 == 0) goto L67bf2;
    if (r3 == 1) goto L67c6c;
    if (r3 == 2) goto L67bc4;
    /* r3 == 3 */
    /* case 3 : L67a9a */
    if ((r8 & 0x10) != 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f7971) /*=0xf7971*/, ((unsigned long)&rodata_f6fef) /*=0xf6fef*/, 0x1d4, param_4);
        r1 = 0x1d4;
        goto L67968;
    }
    if (r10 != 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f7987) /*=0xf7987*/, ((unsigned long)&rodata_f6fef) /*=0xf6fef*/, 0x1d5, param_4);
        r1 = 0x1d5;
        goto L67968;
    }
    if ((r8 & 4) != 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f799d) /*=0xf799d*/, ((unsigned long)&rodata_f6fef) /*=0xf6fef*/, 0x1d6, param_4);
        r1 = 0x1d6;
        goto L67968;
    }
    r3 = 0x100;
    R32(r4 + 0x200) = r3;
    r2 = R32(r9 + 0xc);  r3 = R32(r9 + 0x10);
    R32(r4 + 0x544) = r2;
    R32(r4 + 0x548) = r3;
    r3 = 1;  R32(r4 + 8) = r3;
L67b00:
    r0 = (uint32_t)__nrfy_internal_twim_events_process((int)r4, 0x100000);
    if (r0 != 0) goto L67b00;
    r2 = R32(r9 + 0x14);  r3 = R32(r9 + 0x18);
    R32(r4 + 0x544) = r2;
    R32(r4 + 0x548) = r3;
    r3 = r7 * 0x28 + r5;
    r2 = ((unsigned long)&rodata_40000) /*=0x40000*/;
    goto L67b24;

L67bc4:  /* case 2 */
    r2 = R32(r9 + 0xc);  r3 = R32(r9 + 0x10);
    R32(r4 + 0x544) = r2;
    R32(r4 + 0x548) = r3;
    r2 = R32(r9 + 0x14);  r3 = R32(r9 + 0x18);
    R32(r4 + 0x534) = r2;
    R32(r4 + 0x538) = r3;
    r3 = 0x1080;
    goto L67be0;

L67c6c:  /* case 1 */
    r2 = R32(r9 + 0xc);  r3 = R32(r9 + 0x10);
    R32(r4 + 0x534) = r2;
    R32(r4 + 0x538) = r3;
    r3 = 0x1000;
    goto L67be0;

L67be0:
    R32(r4 + 0x200) = r3;
    r3 = 1;  R32(r4 + 0x20) = r3;
    r3 = r7 * 0x28 + r5;
    r2 = 2;
    goto L67b24;

L67bf2:  /* case 0 */
    {
        int c20 = (r8 & 0x20) != 0;
        r2 = R32(r9 + 0xc);  r3 = R32(r9 + 0x10);
        R32(r4 + 0x544) = r2;
        r2 = c20 ? 0x100 : 0x200;
        R32(r4 + 0x548) = r3;
        R32(r4 + 0x200) = r2;
        r2 = c20 ? ((unsigned long)&rodata_40000) /*=0x40000*/ : 2;
        r3 = r7 * 0x28 + r5;
        R32(r3 + 8) = r2;
        r3 = 1;  R32(r4 + 0x20) = r3;
        goto L67b26;
    }

L67b24:
    R32(r3 + 8) = r2;
L67b26:
    r11 = 0x0bad0000;
L67b2a:
    r1 = r7 * 0x28;
    r3 = R32(r5 + r1);
    r0 = r5 + r1;
    if (r10 != 0) goto L67b82;
    r1 = R8(r6);
    if (r1 == 3) goto L67b82;
    if (r1 != 1) goto L67c88;
    R32(r4) = r1;
    if (r3 != 0) goto L67b6e;
    r2 = R32(r0 + 0x10);
    if (r2 == 0) goto L67c84;
L67b50:
    r1 = ((unsigned long)&rodata_40202) /*=0x40202*/;
    r10 = ((unsigned long)&rodata_40002) /*=0x40002*/;
L67b56:
    r0 = (uint32_t)__nrfy_internal_twim_events_process((int)r4, (int)r1);
    r2 = 1;
    if ((r0 & 0x200) != 0) R32(r4 + 0x14) = r2;
    r1 = ((unsigned long)&rodata_40202) /*=0x40202*/;
    if ((r0 & r10) == 0) goto L67b56;
L67b6e:
    r2 = r7 * 0x28;
    r1 = R32(r6 + 4);
    r2 = R32(r5 + r2);
    if (r1 != 0) goto L67b82;
    if (r2 == 0) goto L67cee;
    r2 = 1;  R32(r4 + 0x14) = r2;
L67b82:
    r2 = r7 * 0x28;
    r1 = r5 + r2;
    r2 = R32(r5 + r2);
    if (r2 == 0) goto L67cee;
    if ((r8 & 4) != 0) { r2 = 0; R32(r1 + 8) = r2; }
    if ((r8 & 0x40) == 0) {
        r2 = r7 * 0x28 + r5;
        r1 = R32(r2 + 8) | 2;
        R32(r2 + 8) = r1;
    }
    r2 = r7 * 0x28 + r5;
    r1 = R32(r2 + 8) | 0x200;
    R32(r2 + 8) = r1;
    r2 = R32(r2 + 8);
    R32(r4 + 0x304) = r2;
    goto L67a00;

L67c7e:
    r11 = 0x0bad0004;
    goto L67b2a;

L67c84:
    R32(r4 + 0x14) = r1;
    goto L67b50;

L67c88:
    r1 = 1;  R32(r4 + 8) = r1;
    if (r3 != 0) goto L67b6e;
    r0 = R32(r0 + 0x10);
    if (r0 == 0) goto L67cde;
L67c96:
    r3 = ((unsigned long)&rodata_40002) /*=0x40002*/;
    if ((r10 & r3) != 0) goto L67b6e;
    r0 = r4;
    r0 = (uint32_t)__nrfy_internal_twim_events_process((int)r4, ((unsigned long)&rodata_40202) /*=0x40202*/);
    r10 = r0;
    if ((r0 & 0x200) == 0) goto L67c96;
    r0 = (uint32_t)__nrfy_internal_twim_events_process((int)r4, 0x1000000);
    r1 = R32(r4 + 0x200);
    if (r0 == 0) goto L67ce2;
    r0 = r1 & 0x200;
    if (r0 == 0) {
        r2 = 1;  r10 = r0;
        R32(r4 + 0x20) = r2;
        R32(r4 + 0x14) = r2;
    }
L67cce:
    r3 = r1 << 0x17;
    if ((int32_t)r3 >= 0) goto L67c96;
    r0 = (uint32_t)__nrfy_internal_twim_events_process((int)r4, ((unsigned long)&rodata_40000) /*=0x40000*/);
    goto L67ce8;
L67cde:
    R32(r4 + 0x14) = r1;
    goto L67c96;
L67ce2:
    r2 = 1;
    R32(r4 + 0x20) = r2;
    R32(r4 + 0x14) = r2;
L67ce8:
    r10 = 0;
    goto L67c96;

L67cee:
    r5 = r7 * 0x28 + r5;
    r1 = 0;
    r2 = R32(r4 + 0x4c4);
    R32(r4 + 0x4c4) = r2;
    R8(r5 + 0x24) = (uint8_t)r1;
    if (r2 == 0) goto L67d28;
    r1 = 0x0bae0000;
    r3 = 0x0bad0001;
    r11 = ((r2 & 1) != 0) ? r1 : r3;
    r1 = r1 + 1;
    if ((r2 & 2) != 0) r11 = r1;
    {
        int c4 = (r2 & 4) != 0;
        r2 = 0x0bae0002;
        if (c4) r11 = r2;
    }
    goto L67a00;
L67d28:
    if ((r8 & 0x40) != 0) goto L67a00;
    r1 = r9;
    r0 = (uint32_t)xfer_completeness_check((int)r4, (int)r9);
    r2 = 0x0bad0001;
    if (r0 == 0) r11 = r2;
    goto L67a00;

L67d42:
    r11 = 0x0bad000a;
    /* fall */
L67a00:
    return (int)r11;
}
