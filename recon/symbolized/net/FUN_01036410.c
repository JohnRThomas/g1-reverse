#include "g1_net_symbols.h"
/* net-core FUN_01036410 @ 0x1036410  (parity 300 trials PROVEN) */
#define ALWI __attribute__((always_inline)) static inline
ALWI unsigned int readIPSR(void){unsigned c;__asm__ volatile("mrs %0, ipsr":"=r"(c));return c;}
ALWI int isCurrentModePrivileged(void){unsigned c;__asm__ volatile("mrs %0, control":"=r"(c));return (c&1)==0;}
ALWI int getBasePriority(void){unsigned b;__asm__ volatile("mrs %0, basepri":"=r"(b));return (int)b;}
ALWI void setBasePriority(int p){__asm__ volatile("msr basepri, %0"::"r"(p):"memory");}
ALWI void isb_(void){__asm__ volatile("isb sy":::"memory");}

extern int FUN_0103610c(unsigned int);
extern int FUN_01036128(unsigned int);
extern void FUN_01036144(unsigned int);
extern int FUN_010375b8(unsigned int, int, void*);
extern int FUN_01037130(unsigned int, int);
extern void FUN_01039bbe(int,int,int);
extern void FUN_01039bb0(int,int);
extern int FUN_0103b1c4(int,int);

#define OBJ  ((uintptr_t)&g_net_mutexq_spinlock) /*=0x21004b48*/
#define TAB  ((uintptr_t)&g_zephyr_kernel_readyq) /*=0x21004b28*/
#define STRA "acking error (context area might be not valid)" /*=0x103d2a7*/
#define STR65 ((uintptr_t)&rodata_103eaab) /*=0x103eaab*/
#define STR72 "***** HARD FAULT *****" /*=0x103d3b6*/

static void panic(int arg0, int code) __attribute__((noreturn));
static void panic(int arg0, int code) { FUN_01039bb0(arg0, code); __builtin_unreachable(); }

unsigned int FUN_01036410(int *param_1, unsigned int param_2, int param_3, int param_4)
{
    unsigned int ipsr = readIPSR();
    if (ipsr != 0) {
        FUN_01039bbe(STRA, STR65, 0x65);
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
        FUN_01039bbe(STRA, STR72, 0x72);
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
        FUN_01039bbe(STRA, STR72, 0xf0);
        panic(STR72, 0xf0);
    } else {
        signed char cVar5 = *(volatile signed char*)(tab8 + 0xe);
        signed char cVar1 = *(volatile signed char*)(param_1[2] + 0xe);
        if (cVar1 <= cVar5) cVar5 = cVar1;
        if (cVar5 < -0x7f) cVar5 = -0x7f;
        int iVar3b = 0;
        if (cVar5 < cVar1) iVar3b = FUN_0103b1c4(0,0);

        int iVar4 = FUN_010375b8(OBJ, saved_bp, param_1);
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
            FUN_01039bbe(STRA, STR72, 0x72);
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

    FUN_01039bbe(STRA, STR72, 0xf0);
    panic(STR72, 0xf0);
}

