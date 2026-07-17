/* readable reconstruction; identity: FUN_01036774 @ 0x01036774
 * public-name: FUN_01036774
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 */
/* net-core FUN_01036774 @ 0x1036774  (parity 300 trials PROVEN) */

static inline int isCurrentModePrivileged(void){return 1;}
static inline int getBasePriority(void){return 0;}
static inline void setBasePriority(int p){(void)p;}
static inline void InstructionSynchronizationBarrier(int x){(void)x; __atomic_signal_fence(__ATOMIC_SEQ_CST);}

extern int FUN_0103610c(void *);
extern int FUN_01036128(void *);
extern void FUN_01036144(void *);
extern int FUN_010375b8(void*, unsigned int, void*, unsigned int, unsigned int, unsigned int, unsigned int);
extern void FUN_01039bb0(unsigned int, unsigned int);
extern void assert_print(unsigned int, unsigned int, unsigned int);
extern unsigned int FUN_0103b1e2(void*, unsigned int, void*, unsigned int, void*, unsigned int);

unsigned int FUN_01036774(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int *puVar7 = param_1 + 2;
    unsigned int uVar8 = 0;
    if (isCurrentModePrivileged()) {
        uVar8 = getBasePriority();
    }
    if (isCurrentModePrivileged()) {
        unsigned int uVar5 = getBasePriority();
        if (uVar5 == 0 || uVar5 > 0x40) {
            setBasePriority(0x40);
        }
    }
    InstructionSynchronizationBarrier(0xf);

    int iVar2 = FUN_0103610c(puVar7);
    if (iVar2 == 0) {
        assert_print(0x0103d2a7, 0x0103d3b6, 0x72);
        uVar8 = 0x72;
        FUN_01039bb0(0x0103d3b6, uVar8);
        __builtin_unreachable();
    }

    FUN_01036144(puVar7);
    unsigned int *puVar6 = (unsigned int *)param_1[0];
    unsigned int uVar3 = 0;
    if (puVar6 == 0) {
        if ((param_3 | param_4) != 0) {
            int r = FUN_010375b8(puVar7, uVar8, param_1 + 3, param_3 | param_4, param_3, param_4, param_3);
            if (r != 0) {
                return 0;
            }
            volatile unsigned int * const p1 = (volatile unsigned int *)0x21004b28;
            unsigned int inner = p1[2];
            unsigned int val = *(volatile unsigned int *)(inner + 0x14);
            return val;
        }
    } else {
        unsigned int *puVar4 = (unsigned int *)param_1[1];
        unsigned int uVar5b = (*puVar6) & 0xfffffffc;
        param_1[0] = uVar5b;
        if (puVar6 == puVar4) {
            param_1[1] = uVar5b;
        }
        uVar3 = FUN_0103b1e2(puVar6, 1, puVar4, uVar5b, param_1, param_2);
    }

    iVar2 = FUN_01036128(puVar7);
    if (iVar2 != 0) {
        if (isCurrentModePrivileged()) {
            setBasePriority((int)uVar8);
        }
        InstructionSynchronizationBarrier(0xf);
        return uVar3;
    }
    assert_print(0x0103d2a7, 0x0103d3b6, 0xf0);
    uVar8 = 0xf0;
    FUN_01039bb0(0x0103d3b6, uVar8);
    __builtin_unreachable();
}
