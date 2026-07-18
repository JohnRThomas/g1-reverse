/* readable reconstruction; identity: FUN_01036410 @ 0x01036410
 * public-name: FUN_01036410
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103eaab                           @ 0x0103eaab
 */
/* net-core FUN_01036410 @ 0x1036410  (parity 300 trials PROVEN) */
#define ALWI __attribute__((always_inline)) static inline
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
ALWI unsigned int readIPSR(void){return __get_IPSR();}
ALWI int isCurrentModePrivileged(void){return (__get_CONTROL()&1)==0;}
ALWI int getBasePriority(void){return (int)__get_BASEPRI();}
ALWI void setBasePriority(int p){__set_BASEPRI((unsigned)p);}
ALWI void isb_(void){__ISB();}

extern int FUN_0103610c(unsigned int);
extern int FUN_01036128(unsigned int);
extern void FUN_01036144(unsigned int);
extern int FUN_010375b8(unsigned int, int, void*, int, int, int);
extern int FUN_01037130(unsigned int, int);
extern void assert_print(int,int,int);
extern void assert_post_action(int,int);
extern int FUN_0103b1c4(int,int);

#define OBJ  0x21004b48u
#define TAB  0x21004b28u
#define STRA 0x0103d2a7
#define STR65 0x0103eaab
#define STR72 0x0103d3b6

static void panic(int arg0, int code) __attribute__((noreturn));
static void panic(int arg0, int code) { assert_post_action(arg0, code); __builtin_unreachable(); }

unsigned int FUN_01036410(int *param_1, unsigned int param_2, int param_3, int param_4)
{
    unsigned int ipsr = readIPSR();
    if (ipsr != 0) {
        assert_print(STRA, STR65, 0x65);
        panic(STR65, 0x65);
    }

    int saved_bp = 0;
    if (isCurrentModePrivileged()) saved_bp = getBasePriority();
    if (isCurrentModePrivileged()) {
        int cur = getBasePriority();
        if (cur == 0 || cur > 0x40) setBasePriority(0x40);
    }
    isb_();

    int iVar3 = FUN_0103610c(OBJ);
    if (iVar3 == 0) {
        assert_print(STRA, STR72, 0x72);
        panic(STR72, 0x72);
    }
    FUN_01036144(OBJ);

    volatile int *tab = (volatile int*)TAB;
    int tab8 = *(volatile int*)(TAB+8);

    if (param_1[3] == 0) {
        int iVar4 = (int)*(volatile signed char*)(tab8 + 0xe);
        param_1[3] = param_1[3] + 1;
        param_1[4] = iVar4;
        param_1[2] = *(volatile int*)(TAB+8);
        iVar3 = FUN_01036128(OBJ);
        if (iVar3 != 0) {
            if (isCurrentModePrivileged()) setBasePriority(saved_bp);
            isb_();
            return 0;
        }
    } else if (param_1[2] == *(volatile int*)(TAB+8)) {
        int iVar4 = param_1[4];
        param_1[3] = param_1[3] + 1;
        param_1[4] = iVar4;
        param_1[2] = *(volatile int*)(TAB+8);
        iVar3 = FUN_01036128(OBJ);
        if (iVar3 != 0) {
            if (isCurrentModePrivileged()) setBasePriority(saved_bp);
            isb_();
            return 0;
        }
    } else if (param_3 == 0 && param_4 == 0) {
        iVar3 = FUN_01036128(OBJ);
        if (iVar3 != 0) {
            if (isCurrentModePrivileged()) setBasePriority(saved_bp);
            isb_();
            return 0xfffffff0u;
        }
        assert_print(STRA, STR72, 0xf0);
        panic(STR72, 0xf0);
    } else {
        signed char cVar5 = *(volatile signed char*)(tab8 + 0xe);
        signed char cVar1 = *(volatile signed char*)(param_1[2] + 0xe);
        if (cVar1 <= cVar5) cVar5 = cVar1;
        if (cVar5 < -0x7f) cVar5 = -0x7f;
        int iVar3b = 0;
        if (cVar5 < cVar1) iVar3b = FUN_0103b1c4(param_1[2], cVar5);

        int iVar4 = FUN_010375b8(OBJ, saved_bp, param_1, cVar1,
                                 param_3, param_4);
        if (iVar4 == 0) return 0;

        saved_bp = 0;
        if (isCurrentModePrivileged()) saved_bp = getBasePriority();
        if (isCurrentModePrivileged()) {
            int cur = getBasePriority();
            if (cur == 0 || cur > 0x40) setBasePriority(0x40);
        }
        isb_();

        iVar4 = FUN_0103610c(OBJ);
        if (iVar4 == 0) {
            assert_print(STRA, STR72, 0x72);
            panic(STR72, 0x72);
        }
        FUN_01036144(OBJ);

        int matched = 0;
        if (param_1[2] != 0) {
            int *piVar7 = (int*)param_1[0];
            int iVar4b = param_1[4];
            if (param_1 != piVar7 && piVar7 != (int*)0) {
                signed char pv = *(volatile signed char*)((int)piVar7 + 0xe);
                if (pv <= iVar4b) iVar4b = pv;
                if (iVar4b < -0x7f) iVar4b = -0x7f;
            }
            int rc = FUN_0103b1c4(param_1[2], iVar4b);
            if (rc != 0) {
                FUN_01037130(OBJ, saved_bp);
                return 0xfffffff5u;
            }
        }
        if (iVar3b != 0) {
            FUN_01037130(OBJ, saved_bp);
            return 0xfffffff5u;
        }
        iVar3 = FUN_01036128(OBJ);
        if (iVar3 != 0) {
            if (isCurrentModePrivileged()) setBasePriority(saved_bp);
            isb_();
            return 0xfffffff5u;
        }
    }

    assert_print(STRA, STR72, 0xf0);
    panic(STR72, 0xf0);
}
