#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00049090 @ 0x00049090
 * public-name: display_thread_handler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_uldivmod                         <= FUN_0000e244 @ 0x0000e244
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   gui_set_active_canvas                    <= FUN_000431b4 @ 0x000431b4
 *   display_reflash_handler                  <= FUN_00048e28 @ 0x00048e28
 *   stop_some_timer                          <= FUN_00048ff4 @ 0x00048ff4
 *   setDelayExitValue                        <= FUN_00049000 @ 0x00049000
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   projector_fill_and_sync                  <= FUN_0007d6f4 @ 0x0007d6f4
 *   k_timer_init                             <= FUN_00086726 @ 0x00086726
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   rodata_7d86d                             @ 0x0007d86d
 *   rodata_efb2e                             @ 0x000efb2e
 *   rodata_efb50                             @ 0x000efb50
 *   rodata_efb7a                             @ 0x000efb7a
 *   rodata_efb9f                             @ 0x000efb9f
 *   rodata_efbb7                             @ 0x000efbb7
 *   rodata_efbe5                             @ 0x000efbe5
 *   rodata_efc00                             @ 0x000efc00
 *   rodata_efc2d                             @ 0x000efc2d
 *   rodata_efc62                             @ 0x000efc62
 *   rodata_efc92                             @ 0x000efc92
 *   rodata_efcdf                             @ 0x000efcdf
 *   rodata_efd03                             @ 0x000efd03
 *   rodata_efd2d                             @ 0x000efd2d
 *   rodata_efd6f                             @ 0x000efd6f
 *   rodata_efe74                             @ 0x000efe74
 *   rodata_efebc                             @ 0x000efebc
 *   rodata_eff70                             @ 0x000eff70
 *   rodata_effaf                             @ 0x000effaf
 *   rodata_f01aa                             @ 0x000f01aa
 *   g_log_level                              @ 0x2000230c
 *   g_dashboard_display_level                @ 0x20002544
 *   g_display_msgq                           @ 0x200038c4
 *   g_some_k_timer                           @ 0x20004ce0
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_2001d447                               @ 0x2001d447
 *   g_display_last_reflash_id                @ 0x2001d448
 */
/* Reconstructed display_thread_handler @ 0x49090  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>

extern void    DEBUG_PRINT(unsigned a, unsigned b, unsigned c);
extern int     debug_print(void);
extern int64_t __aeabi_uldivmod(int, int, int, int);
extern int     get_device_info(void);
extern void    gui_set_active_canvas(int);
extern void    display_reflash_handler(int, int, int, int);
extern void    stop_some_timer(void);
extern int     setDelayExitValue(int);
extern void    FUN_0004906c(void);
extern int     k_msgq_get(int, void *, int, int);
extern void    FUN_00074844(int, int);
extern void    projector_fill_and_sync(int);
extern void    k_timer_init(int, int, int);
extern void    memset_bytes(void *, int, int);

/* globals (absolute addresses from literal pool) */
#define PIV5   (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/)   /* DAT_00049310 : verbosity level */
#define PIV6   (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)   /* DAT_00049314 / DAT_000495cc    */
#define P30    (*(volatile int *)((unsigned long)&g_dashboard_display_level) /*=0x20002544*/)   /* DAT_00049330                   */
#define PC8    (*(volatile signed char *)((unsigned long)&g_2001d447) /*=0x2001d447*/)   /* DAT_0004932c[0] */
#define PC8_1  (*(volatile signed char *)((unsigned long)&g_display_last_reflash_id) /*=0x2001d448*/)   /* DAT_0004932c[1] */
#define PC16   (*(volatile short *)((unsigned long)&g_2001d447) /*=0x2001d447*/)         /* 16-bit store form */

void display_thread_handler(int param_1)
{
    volatile signed char *base = (volatile signed char *)param_1;
    unsigned char local[24];
    int  iVar13, iVar9;
    int  bVar3;
    signed char cVar1;
    short local_3e;
    unsigned lo, b1;
    unsigned uVar12, uVar10, uVar8;

    if (2 < PIV5) {
        if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_efb2e) /*=0xefb2e*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, 0);
        else debug_print();
    }
    memset_bytes(local, 0, 0x18);
    iVar13 = param_1 + 0xd4;
    if (2 < PIV5) {
        if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_efb50) /*=0xefb50*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, 0);
        else debug_print();
    }
    k_timer_init(((unsigned long)&g_some_k_timer) /*=0x20004ce0*/, ((unsigned long)&rodata_7d86d) /*=0x7d86d*/, 0);
    gui_set_active_canvas(param_1 + 0xb90);
    PC16 = 0;

    do {
        while (base[1] == 1 || base[1] == 8) {
            if (2 < PIV5) {
                if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_efb7a) /*=0xefb7a*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, 0);
                else debug_print();
            }
            FUN_00074844(((unsigned long)&rodata_28000) /*=0x28000*/, 0);
        }
        memset_bytes(local, 0, 0x18);
        bVar3 = 0;
        {
            int x = P30;
            int t = x & ~(x >> 31);
            int64_t lVar2 = (int64_t)t * 0x8000 + 999;
            int64_t uVar14 = __aeabi_uldivmod((int)lVar2, (int)((uint64_t)lVar2 >> 32), 1000, 0);
            iVar9 = k_msgq_get(((unsigned long)&g_display_msgq) /*=0x200038c4*/, local, (int)uVar14, (int)((uint64_t)uVar14 >> 32));
        }
        local_3e   = *(short *)(local + 2);
        lo         = local[4];
        b1         = local[5];
        uVar8      = *(unsigned *)(local + 4);
        if (iVar9 == 0) bVar3 = 1;
        else if (iVar9 == -0x23 || iVar9 == -0xb) bVar3 = 0;

        cVar1 = PC8;
        if (cVar1 == 1) {
            if (!bVar3) {
                if (base[0xd5] != 0) { uVar12 = 0; uVar10 = (unsigned char)base[0xd5]; goto LAB_492ee; }
                /* second identical test is dead */
                if (3 < PIV5) {
                    if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_efebc) /*=0xefebc*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, (unsigned char)base[0xd5]);
                    else debug_print();
                }
                if (PIV5 < 1) goto LAB_495ba;
                iVar9 = PIV6;
                uVar12 = 0xeff0e; { unsigned uVar11 = ((unsigned long)&rodata_f01aa) /*=0xf01aa*/;
LAB_495a8:
                if (iVar9 == 0) DEBUG_PRINT(uVar12, uVar11, 0);
                else debug_print(); }
                goto LAB_495ba;
            }
            if (local[0] == 2) {
                if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_efcdf) /*=0xefcdf*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, 0); else debug_print(); }
                if (local_3e == 0) {
                    if (3 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_efd03) /*=0xefd03*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, 0); else debug_print(); }
                    uVar12 = 1; uVar10 = (unsigned char)base[0xd5]; goto LAB_492ee;
                }
                if (local_3e == 2) {
                    if (lo == 1) {
                        if (3 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_efd2d) /*=0xefd2d*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, b1); else debug_print(); }
                        uVar12 = 1;
LAB_492e8:
                        uVar10 = b1; goto LAB_492ee;
                    }
                    if (0 < PIV5) {
                        iVar9 = PIV6; { unsigned u12 = 0xefd45, u11 = ((unsigned long)&rodata_f01aa) /*=0xf01aa*/;
LAB_49270:
                        if (iVar9 == 0) DEBUG_PRINT(u12, u11, 0); else debug_print(); }
                    }
                }
            } else {
                switch (local[0]) {
                case 3:
                    if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_efd6f) /*=0xefd6f*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, 0); else debug_print(); }
                    PC8 = 2;
                    if (local_3e == 0) {
                        if (3 < PIV5) { iVar9 = PIV6; uVar12 = ((unsigned long)&rodata_efd03) /*=0xefd03*/;
LAB_4943a:
                            if (iVar9 == 0) DEBUG_PRINT(uVar12, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, 0); else debug_print();
                        }
LAB_49442:
                        uVar10 = (unsigned char)base[0xd5];
LAB_4947e:
                        display_reflash_handler(param_1, uVar10, iVar13, 2);
                    } else if (local_3e == 2) {
                        if ((signed char)lo != 1) {
                            if (0 < PIV5) { iVar9 = PIV6; uVar12 = 0xefd45; goto LAB_4943a; }
                            goto LAB_49442;
                        }
                        if (3 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_efd2d) /*=0xefd2d*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, b1); else debug_print(); }
                        uVar10 = b1; goto LAB_4947e;
                    }
                    stop_some_timer();
                    goto LAB_49488;
                case 4:
                    if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_efe74) /*=0xefe74*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, uVar8); else debug_print(); }
                    setDelayExitValue(uVar8); uVar12 = 3; uVar10 = (unsigned char)base[0xd5]; break;
                case 5:
                    if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_efebc) /*=0xefebc*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, 0); else debug_print(); }
                    uVar12 = 4; uVar10 = (unsigned char)base[0xd5]; break;
                case 6:
                    if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xefef4, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, 0); else debug_print(); }
                    uVar12 = 5; uVar10 = (unsigned char)base[0xd5]; break;
                case 7:
                    if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xeff2c, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, 0); else debug_print(); }
                    uVar12 = 6; uVar10 = (unsigned char)base[0xd5]; break;
                case 8:
                    if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(0xeff5c, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, 0); else debug_print(); }
                    uVar12 = 7; uVar10 = (unsigned char)base[0xd5]; break;
                default:
                    goto LAB_switchD;
                }
LAB_492ee:
                display_reflash_handler(param_1, uVar10, iVar13, uVar12);
            }
        } else {
            if (cVar1 == 2) {
LAB_49488:
                if (2 < PIV5) {
                    iVar9 = PIV6; uVar12 = ((unsigned long)&rodata_eff70) /*=0xeff70*/; unsigned uVar11 = ((unsigned long)&rodata_f01aa) /*=0xf01aa*/;
                    if (iVar9 == 0) DEBUG_PRINT(uVar12, uVar11, 0); else debug_print();
                }
            } else {
                if (cVar1 == 0) {
                    if (bVar3) {
                        if (local[0] == 2) {
                            if (base[0xd5] == 0x10) {
                                iVar9 = get_device_info();
                                if (**(unsigned char **)(iVar9 + 0x100c) < 0xc) projector_fill_and_sync(0);
                            }
                            if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_efb9f) /*=0xefb9f*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, 0); else debug_print(); }
                            if (local_3e == 0) {
                                if (3 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_efbb7) /*=0xefbb7*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, 0); else debug_print(); }
                                cVar1 = base[0xd5]; PC8_1 = base[0xd5];
LAB_49204:
                                display_reflash_handler(param_1, cVar1, iVar13, 1); PC8 = 1;
                            } else if (local_3e == 2) {
                                if (lo == 1) {
                                    if (3 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_efbe5) /*=0xefbe5*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, b1); else debug_print(); }
                                    PC8_1 = (signed char)b1; cVar1 = (signed char)b1; goto LAB_49204;
                                }
                                if (0 < PIV5) { iVar9 = PIV6; uVar12 = ((unsigned long)&rodata_efc00) /*=0xefc00*/; unsigned uVar11 = ((unsigned long)&rodata_f01aa) /*=0xf01aa*/;
                                    if (iVar9 == 0) DEBUG_PRINT(uVar12, uVar11, 0); else debug_print(); }
                            }
                        } else if (local[0] == 3) {
                            if (2 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_efc2d) /*=0xefc2d*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, 0); else debug_print(); }
                            PC16 = 0;
                            if (local_3e == 0) {
                                if (3 < PIV5) { iVar9 = PIV6; uVar12 = ((unsigned long)&rodata_efc62) /*=0xefc62*/;
LAB_492ac:
                                    if (iVar9 == 0) DEBUG_PRINT(uVar12, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, 0); else debug_print();
                                }
                            } else {
                                if (local_3e != 2) goto LAB_switchD;
                                if ((signed char)lo == 1) {
                                    if (3 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_efc92) /*=0xefc92*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, b1); else debug_print(); }
                                    uVar12 = 2; goto LAB_492e8;
                                }
                                if (0 < PIV5) { iVar9 = PIV6; uVar12 = 0xefcaf; goto LAB_492ac; }
                            }
                            uVar12 = 2; uVar10 = (unsigned char)base[0xd5]; goto LAB_492ee;
                        }
                    }
                    goto LAB_switchD;
                }
                if (0 < PIV5) { if (PIV6 == 0) DEBUG_PRINT(((unsigned long)&rodata_effaf) /*=0xeffaf*/, ((unsigned long)&rodata_f01aa) /*=0xf01aa*/, 0); else debug_print(); }
                display_reflash_handler(param_1, (unsigned char)base[0xd5], iVar13, 2);
            }
LAB_495ba:
            projector_fill_and_sync(0); stop_some_timer(); PC16 = 0;
        }
LAB_switchD:
        FUN_0004906c();
    } while (1);
}
