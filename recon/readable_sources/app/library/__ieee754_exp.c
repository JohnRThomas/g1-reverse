#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00012db0 @ 0x00012db0
 * public-name: __ieee754_exp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dcmp_negate_rhs                          <= FUN_0000d588 @ 0x0000d588
 *   __aeabi_dadd                             <= FUN_0000d58c @ 0x0000d58c
 *   __floatsidf                              <= FUN_0000d824 @ 0x0000d824
 *   __muldf3                                 <= FUN_0000d8f8 @ 0x0000d8f8
 *   __divdf3                                 <= FUN_0000db4c @ 0x0000db4c
 *   __aeabi_dcmplt                           <= FUN_0000dddc @ 0x0000dddc
 *   __aeabi_dcmpgt                           <= FUN_0000de18 @ 0x0000de18
 *   __fixdfsi                                <= FUN_0000de58 @ 0x0000de58
 *   __ieee754_exp                            <= FUN_00012db0 @ 0x00012db0
 * address symbols (name @ address):
 *   rodata_88848                             @ 0x00088848
 *   rodata_88858                             @ 0x00088858
 *   rodata_88868                             @ 0x00088868
 */
/* Reconstructed FUN_00012db0 @ 0x12db0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u4; typedef int32_t i4; typedef uint64_t u8; typedef int64_t i8;
extern u8 dcmp_negate_rhs(u4,u4,u4,u4);
extern u8 __aeabi_dadd(u4,u4,u4,u4);
extern u8 __floatsidf(void);
extern u8 __muldf3(u4,u4,u4,u4);
extern u8 __divdf3(u4,u4,u4,u4);
extern u8 __aeabi_dcmplt(u4,u4,u4,u4);
extern u8 __aeabi_dcmpgt(u4,u4,u4,u4);
extern u8 __fixdfsi(void);

double __ieee754_exp(double xd, u4 param_1, u4 param_2, u4 param_3, u4 param_4){
    u8 in_d0; __builtin_memcpy(&in_d0,&xd,8);
    u8 uVar15 = ((u8)param_2<<32)|param_1;
    u8 uVar12=0, uVar13=0, uVar14=0x7e37e43c8800759cULL, uVar16=0;
    u4 uVar9 = (u4)(in_d0>>32);
    u4 uVar5 = uVar9 & 0x7fffffff;
    i4 iVar4 = (i4)uVar9 >> 31;
    i4 iVar1, iVar2=0, iVar7=0;
    u4 uVar3=0, uVar6=0, uVar8, uVar10;
    u8 res;
    const u4 *puVar11;

    if (0x40862e41u < uVar5) {
        if (0x7fefffffu < uVar5) {
            if ((in_d0 & 0xfffff00000000ULL)!=0 || (i4)(u4)in_d0 != 0) {
                res = __aeabi_dadd((u4)in_d0,uVar9,(u4)in_d0,uVar9); goto ret;
            }
            if ((i8)in_d0 >= 0) { res = in_d0; goto ret; }
        } else {
            iVar1 = (i4)(u4)__aeabi_dcmpgt((u4)in_d0,uVar9,0xfefa39efu,0x40862e42u);
            uVar12 = ((u8)param_4<<32)|param_3;
            uVar3=0x8800759cu; iVar2=0x7e37e43c; uVar6=0x8800759cu; iVar7=0x7e37e43c;
            if (iVar1 != 0) goto control_label_12e26;
            iVar2 = (i4)(u4)__aeabi_dcmplt((u4)in_d0,uVar9,0xfefa39efu,0x40862e42u);
            if (iVar2 == 0) goto control_label_12f2e;
        }
        res = 0; goto ret;
    } else {
        if (0x3fd62e42u < uVar5) {
            if (0x3ff0a2b1u < uVar5) {
control_label_12f2e:
                puVar11 = (const u4*)(((unsigned long)&rodata_88868) /*=0x88868*/ + (u4)(iVar4 * -8));
                uVar14 = __muldf3((u4)in_d0,uVar9,
                                      0x652b82feu,0x3ff71547u);
                __aeabi_dadd((u4)uVar14,(u4)(uVar14>>32),puVar11[0],puVar11[1]);
                iVar2 = (i4)(u4)__fixdfsi();
                uVar15 = __floatsidf();
                uVar3 = (u4)(uVar15>>32);
                uVar12 = __muldf3((u4)uVar15,uVar3,
                                      0xfee00000u,0x3fe62e42u);
                uVar14 = dcmp_negate_rhs((u4)in_d0,uVar9,
                                      (u4)uVar12,(u4)(uVar12>>32));
                uVar15 = __muldf3((u4)uVar15,uVar3,
                                      0x35793c76u,0x3dea39efu);
            } else {
                iVar2 = iVar4*2+1;
                puVar11 = (const u4*)(((unsigned long)&rodata_88858) /*=0x88858*/ + (u4)(iVar4 * -8));
                uVar14 = dcmp_negate_rhs((u4)in_d0,uVar9,
                                      puVar11[0],puVar11[1]);
                uVar15 = *(const u8*)(((unsigned long)&rodata_88848) /*=0x88848*/ + (u4)(iVar4 * -8));
            }
            in_d0 = dcmp_negate_rhs((u4)uVar14,(u4)(uVar14>>32),(u4)uVar15,(u4)(uVar15>>32));
        } else if (0x3e2fffffu < uVar5) {
            iVar2 = 0;
        } else {
            uVar14 = __aeabi_dadd((u4)in_d0,uVar9,0x8800759cu,0x7e37e43cu);
            iVar4 = (i4)(u4)__aeabi_dcmpgt((u4)uVar14,(u4)(uVar14>>32),0,0x3ff00000u);
            if (iVar4 != 0) { res = __aeabi_dadd((u4)in_d0,uVar9,0,0x3ff00000u); goto ret; }
            iVar2 = 0;
            uVar14 = 0;
        }
        uVar10 = (u4)(in_d0>>32);
        uVar8 = (u4)in_d0;
        uVar12 = __muldf3(uVar8,uVar10,uVar8,uVar10);
        uVar6 = (u4)(uVar12>>32); uVar3=(u4)uVar12;
        uVar12 = __muldf3(uVar3,uVar6,0x72bea4d0u,0x3e663769u);
        uVar12 = dcmp_negate_rhs((u4)uVar12,(u4)(uVar12>>32),0xc5d26bf1u,0x3ebbbd41u);
        uVar12 = __muldf3((u4)uVar12,(u4)(uVar12>>32),uVar3,uVar6);
        uVar12 = __aeabi_dadd((u4)uVar12,(u4)(uVar12>>32),0xaf25de2cu,0x3f11566au);
        uVar12 = __muldf3((u4)uVar12,(u4)(uVar12>>32),uVar3,uVar6);
        uVar12 = dcmp_negate_rhs((u4)uVar12,(u4)(uVar12>>32),0x16bebd93u,0x3f66c16cu);
        uVar12 = __muldf3((u4)uVar12,(u4)(uVar12>>32),uVar3,uVar6);
        uVar12 = __aeabi_dadd((u4)uVar12,(u4)(uVar12>>32),0x5555553eu,0x3fc55555u);
        uVar12 = __muldf3((u4)uVar12,(u4)(uVar12>>32),uVar3,uVar6);
        uVar12 = dcmp_negate_rhs(uVar8,uVar10,(u4)uVar12,(u4)(uVar12>>32));
        uVar6 = (u4)(uVar12>>32); uVar3=(u4)uVar12;
        uVar12 = __muldf3(uVar8,uVar10,uVar3,uVar6);
        if (iVar2 == 0) {
            uVar14 = dcmp_negate_rhs(uVar3,uVar6,0,0x40000000u);
            uVar14 = __divdf3((u4)uVar12,(u4)(uVar12>>32),(u4)uVar14,(u4)(uVar14>>32));
            uVar14 = dcmp_negate_rhs((u4)uVar14,(u4)(uVar14>>32),uVar8,uVar10);
            res = dcmp_negate_rhs(0,0x3ff00000u,(u4)uVar14,(u4)(uVar14>>32));
            goto ret;
        }
        uVar16 = dcmp_negate_rhs(0,0x40000000u,uVar3,uVar6);
        uVar16 = __divdf3((u4)uVar12,(u4)(uVar12>>32),(u4)uVar16,(u4)(uVar16>>32));
        uVar16 = dcmp_negate_rhs((u4)uVar15,(u4)(uVar15>>32),(u4)uVar16,(u4)(uVar16>>32));
        uVar14 = dcmp_negate_rhs((u4)uVar16,(u4)(uVar16>>32),(u4)uVar14,(u4)(uVar14>>32));
        uVar14 = dcmp_negate_rhs(0,0x3ff00000u,(u4)uVar14,(u4)(uVar14>>32));
        iVar4 = (i4)(u4)(uVar14>>32);
        if (-0x3fe < iVar2) {
            res = ((u8)(u4)(iVar4 + iVar2*0x100000)<<32) | (u4)uVar14;
            goto ret;
        }
        uVar3 = (u4)uVar14;
        iVar2 = iVar4 + (iVar2+1000)*0x100000;
        uVar6=0; iVar7=0x1700000;
control_label_12e26:
        uVar13 = __muldf3(uVar3,(u4)iVar2,uVar6,(u4)iVar7);
        res = uVar13;
    }
ret:
    { double r; __builtin_memcpy(&r,&res,8); return r; }
}
