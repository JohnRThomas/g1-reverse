#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01037768 @ 0x01037768
 * public-name: FUN_01037768
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   g_zephyr_sched_thread_field              @ 0x21004b40
 */
/* net-core FUN_01037768 @ 0x1037768  (parity 300 trials PROVEN) */

#include <stdint.h>
#include <cmsis_gcc.h>

extern int FUN_0103610c(void *);
extern int FUN_01036128(void *);
extern void FUN_01036144(void *);
extern void FUN_01036f74(int);
extern void FUN_0103735c(unsigned int, int);
extern void FUN_010380d8(int);
extern void FUN_01039bb0(unsigned int, unsigned int);
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);
extern void FUN_0103b2b4(void);

void FUN_01037768(int param_1)
{
    FUN_010380d8(param_1 + 0x18);

    unsigned int uVar6 = __get_BASEPRI();
    __set_BASEPRI_MAX(0x40u);
    __ISB();

    volatile int * const p1800 = (volatile int *)0x21004b68;
    int iVar4v = FUN_0103610c((void *)p1800);
    if (iVar4v == 0) {
        FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
        FUN_01039bb0(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
        __builtin_unreachable();
    }

    FUN_01036144((void *)p1800);
    volatile signed char *pb = (volatile signed char *)param_1;
    if (pb[0xd] < 0) {
        ((volatile unsigned char *)param_1)[0xd] = ((volatile unsigned char *)param_1)[0xd] & 0x7f;
        FUN_0103735c(((unsigned long)&g_zephyr_sched_thread_field) /*=0x21004b40*/, param_1);
    }

    volatile int * const p1810 = (volatile int *)0x21004b28;
    int iVar5 = p1810[2];
    ((volatile unsigned char *)param_1)[0xd] = ((volatile unsigned char *)param_1)[0xd] | 0x10;
    FUN_01036f74(iVar5 == param_1);

    int iVar5b = FUN_01036128((void *)p1800);
    if (iVar5b != 0) {
        __set_BASEPRI(uVar6);
        __ISB();
        if (p1810[2] != param_1) {
            return;
        }
        FUN_0103b2b4();
        return;
    }
    FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
    FUN_01039bb0(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
    __builtin_unreachable();
}
