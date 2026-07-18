/* readable reconstruction; identity: FUN_0102c4e4 @ 0x0102c4e4
 * public-name: FUN_0102c4e4
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d373                           @ 0x0103d373
 */
/* net-core FUN_0102c4e4 @ 0x102c4e4  (parity 300 trials PROVEN) */
typedef unsigned int uint;
typedef unsigned int undefined4;

extern int FUN_01039a7a(int*, unsigned int);
extern unsigned int FUN_010397c0(unsigned int, unsigned int);
extern unsigned int FUN_01039874(int, unsigned int);
extern unsigned int FUN_01039768(int, unsigned int);
extern void FUN_010398e8(int, unsigned int, unsigned int);
extern void FUN_01039972(int, unsigned int);
extern unsigned int FUN_01039774(int, unsigned int, int);
extern unsigned int FUN_010397ac(int, unsigned int);
extern void assert_print(int, int, int, unsigned int, unsigned int);
extern void assert_post_action(int, int);

#define STRA 0x0103d2a7
#define STRB 0x0103d373

int FUN_0102c4e4(int *param_1, uint param_2, uint param_3, undefined4 param_4)
{
    int iVar7 = *param_1;
    uint uVar4 = *(volatile unsigned int*)(iVar7 + 8);
    uint uVar3 = (uVar4 < 0x8000) ? 4u : 8u;
    uint uVar5 = (param_2 - 1) & param_2;
    uint uVar8;

    if (uVar5 == 0) {
        if (param_2 <= uVar3) {
            return FUN_01039a7a(param_1, param_3);
        }
        uVar8 = 0;
        uVar5 = param_2;
    } else {
        uVar8 = (uint)(-(int)param_2) & param_2;
        if (uVar8 <= uVar3) uVar3 = uVar8;
        if (((uVar5 - 1) & uVar5) != 0) {
            assert_print(STRA, STRB, 0x144, uVar5, param_4);
            assert_post_action(STRB, 0x144);
            /* The diagnostic backend is normally terminal. If it returns,
               r2 still contains the line number and becomes the subsequent
               heap-size comparison operand in the original. */
            uVar4 = 0x144;
        }
    }

    if (param_3 != 0 && (param_3 >> 3) < uVar4) {
        unsigned int uVar1 = FUN_010397c0(uVar4, (param_3 + uVar5) - uVar3);
        uVar4 = FUN_01039874(iVar7, uVar1);
        if (uVar4 != 0) {
            int iVar6b = (*(volatile unsigned int*)(iVar7+8) < 0x8000) ? 4 : 8;
            int iVar6 = (int)(uVar5 * ((uVar8 + uVar4*8 + iVar6b + iVar7 + (uVar5-1)) / uVar5) - uVar5);
            unsigned int uVar5b = FUN_010397ac(iVar7, iVar6);
            unsigned int uVar3b = (unsigned int)(((param_3 + (unsigned)iVar6 + 7) & 0xfffffff8u) - iVar7) >> 3;
            if (uVar4 < uVar5b) {
                FUN_010398e8(iVar7, uVar4, uVar5b);
                FUN_01039972(iVar7, uVar4);
            }
            unsigned int iVar2 = FUN_01039768(iVar7, uVar5b);
            if (uVar3b < iVar2 + uVar5b) {
                FUN_010398e8(iVar7, uVar5b, uVar3b);
                FUN_01039972(iVar7, uVar3b);
            }
            FUN_01039774(iVar7, uVar5b, 1);
            return iVar6;
        }
    }
    return 0;
}
