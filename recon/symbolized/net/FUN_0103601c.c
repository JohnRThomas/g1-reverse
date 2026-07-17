#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103601c @ 0x0103601c
 * public-name: FUN_0103601c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103bac9                           @ 0x0103bac9
 *   rodata_103bfc0                           @ 0x0103bfc0
 *   rodata_103bfec                           @ 0x0103bfec
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103ea45                           @ 0x0103ea45
 */
/* net-core FUN_0103601c @ 0x103601c  (parity 300 trials PROVEN) */
typedef unsigned int uint;
typedef unsigned long long ulonglong;

extern void FUN_01035edc(int,int,int,int,int,int,int,int,int,int);
extern void FUN_0103721c(void);
extern int FUN_0103719c(int);
extern ulonglong FUN_0100823c(int,int,int,int);
extern void FUN_01037f8c(int,unsigned int,int,int);
extern void FUN_01039bbe(int,int,int);
extern void FUN_01039bb0(int,int) __attribute__((noreturn));
extern void FUN_010372b4(void);

#define START ((int*)((unsigned long)&rodata_103bfc0) /*=0x103bfc0*/)
#define END   ((int*)((unsigned long)&rodata_103bfec) /*=0x103bfec*/)
#define STRA   ((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/
#define STR2F3 ((unsigned long)&rodata_103ea45) /*=0x103ea45*/
#define MAGIC7 ((unsigned long)&rodata_103bac9) /*=0x103bac9*/

void FUN_0103601c(void)
{
    int *piVar4 = END;
    int *piVar9 = START;

    for (;;) {
        if (piVar4 < piVar9) {
            FUN_01039bbe(STRA, STR2F3, 0x2f3);
            FUN_01039bb0(STR2F3, 0x2f3);
        }
        if (piVar4 <= piVar9) break;

        FUN_01035edc(piVar9[0], piVar9[1], piVar9[2], piVar9[3], piVar9[4],
                     piVar9[5], piVar9[6], piVar9[7], piVar9[8], piVar9[10]);
        *(volatile int**)(piVar9[0] + 0x54) = piVar9;
        piVar9 = piVar9 + 0xb;
    }

    FUN_0103721c();

    for (piVar9 = START; piVar9 <= piVar4; piVar9 = piVar9 + 0xb) {
        if (piVar4 < piVar9) {
            FUN_01039bbe(STRA, STR2F3, 0x312);
            FUN_01039bb0(STR2F3, 0x312);
        }
        if (piVar4 <= piVar9) {
            FUN_010372b4();
            return;
        }
        {
            uint uVar6 = (uint)piVar9[9];
            if (uVar6 != 0xffffffffu) {
                int iVar10 = piVar9[0];
                uVar6 = uVar6 & ~((int)uVar6 >> 31);
                long long lVar3 = (long long)(int)uVar6 * 0x8000 + 999;
                int iVar5 = (int)((unsigned long long)lVar3 >> 32);
                if (iVar5 == 0 && (uVar6 & 0x1ffff) == 0) {
                    FUN_0103719c(iVar10);
                } else {
                    ulonglong uVar11 = FUN_0100823c((int)lVar3, iVar5, 1000, 0);
                    FUN_01037f8c(iVar10 + 0x18, MAGIC7, (int)uVar11, (int)((ulonglong)uVar11 >> 32));
                }
            }
        }
    }

    FUN_01039bbe(STRA, STR2F3, 0x312);
    FUN_01039bb0(STR2F3, 0x312);
}
