/* readable reconstruction; identity: FUN_0102dcf4 @ 0x0102dcf4
 * public-name: FUN_0102dcf4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103c0ec                           @ 0x0103c0ec
 *   rodata_103c0fc                           @ 0x0103c0fc
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d5d7                           @ 0x0103d5d7
 */
/* net-core FUN_0102dcf4 @ 0x102dcf4  (parity 300 trials PROVEN) */

typedef unsigned int uint;
extern unsigned int FUN_0102dc90(unsigned int);
extern void FUN_0102e23c(int*, unsigned int, unsigned int);
extern void FUN_01037c64(unsigned int, unsigned int);
extern void FUN_01039bb0(unsigned int,unsigned int);
extern void FUN_01039bbe(unsigned int,unsigned int,unsigned int);
extern int FUN_0103a294(unsigned int);

unsigned int FUN_0102dcf4(int param_1, int param_2)
{
    int *piVar5 = (int *)0x0103c0ec; /* DAT_0102ddac */
    int *piVar1 = (int *)0x0103c0fc; /* DAT_0102dda8 */

    if ((unsigned int)((int)piVar1 - (int)piVar5) < 0xa0) {
        int iVar2 = FUN_0103a294(0x2100466cu); /* DAT_0102ddb8 */
        if (iVar2 != 0) {
            return 0;
        }
        unsigned int uVar3 = 0;
        unsigned int uVar6 = 0;
        for (; piVar5 <= piVar1; piVar5 = piVar5 + 4) {
            if (piVar1 <= piVar5) {
                if (param_1 != 0) {
                    while (uVar3 != 0) {
                        uVar3 = FUN_0102dc90(uVar3);
                        if (param_2 != 0) {
                            FUN_01037c64(0x148, 0);
                        }
                    }
                    return 0;
                }
                return uVar3;
            }
            if ((char)piVar5[3] != 0) {
                void (*cb0)(int*) = *(volatile void(**)(int*))(*piVar5 + 0xc);
                if (cb0 != 0) {
                    cb0(piVar5);
                }
                int (*cb1)(int*) = *(volatile int(**)(int*))(*piVar5 + 0x10);
                if (cb1 == 0 || cb1(piVar5) == 0) {
                    FUN_0102e23c(piVar5, *(volatile unsigned int*)piVar5[1], 4);
                } else {
                    uVar3 = uVar3 | (1u << (uVar6 & 0xff));
                }
                uVar6 = uVar6 + 1;
            }
        }
        FUN_01039bbe(0x0103d2a7, 0x0103d5d7, 0x126);
        FUN_01039bb0(0x0103d5d7, 0x126);
        __builtin_unreachable();
    } else {
        FUN_01039bbe(0x0103d2a7, 0x0103d5d7, 0x119);
        FUN_01039bb0(0x0103d5d7, 0x119);
        __builtin_unreachable();
    }
}
