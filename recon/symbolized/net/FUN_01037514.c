#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01037514 @ 0x01037514
 * public-name: FUN_01037514
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103eb0e                           @ 0x0103eb0e
 */
/* net-core FUN_01037514 @ 0x1037514  (parity 300 trials PROVEN) */

extern void FUN_010374dc(void);
extern int assert_print(int,int,int);
extern void FUN_01039bb0(int,int) __attribute__((noreturn));

void FUN_01037514(int *param_1, int *param_2, unsigned int param_3, unsigned int param_4)
{
    FUN_010374dc();
    *((volatile unsigned char*)param_1 + 0xd) |= 2;
    int *piVar2 = (int*)0x210043a8;
    if (param_2 != 0) {
        param_1[2] = (int)param_2;
        if (param_1 == piVar2) {
            assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eb0e) /*=0x103eb0e*/, 0xc1);
            FUN_01039bb0(((unsigned long)&rodata_103eb0e) /*=0x103eb0e*/, 0xc1);
        }
        int *p3 = (int*)*param_2;
        if (param_2 != p3) {
            while (p3 != 0) {
                signed char ca = *((signed char*)param_1 + 0xe);
                signed char cb = *((signed char*)p3 + 0xe);
                if (ca != cb && ca < cb) {
                    int *piVar1 = (int*)p3[1];
                    param_1[0] = (int)p3;
                    param_1[1] = (int)piVar1;
                    *piVar1 = (int)param_1;
                    p3[1] = (int)param_1;
                    return;
                }
                if (p3 == (int*)param_2[1]) break;
                p3 = (int*)*p3;
            }
        }
        int *tail = (int*)param_2[1];
        param_1[0] = (int)param_2;
        param_1[1] = (int)tail;
        *tail = (int)param_1;
        param_2[1] = (int)param_1;
    }
}
