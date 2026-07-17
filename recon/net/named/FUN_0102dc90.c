/* readable reconstruction; identity: FUN_0102dc90 @ 0x0102dc90
 * public-name: FUN_0102dc90
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103c0ec                           @ 0x0103c0ec
 */
/* net-core FUN_0102dc90 @ 0x102dc90  (parity 300 trials PROVEN) */
extern void FUN_0102e23c(int a, unsigned int b, int c);

typedef int (*call_fn_t)(int arg);

unsigned int FUN_0102dc90(unsigned int param_1)
{
    unsigned int uVar10 = param_1;
    int iVar5 = 0x103c0ec;

    while (param_1 != 0) {
        int iVar8 = __builtin_ctz(param_1);
        int iVar9 = iVar5 + iVar8 * 0x10;
        param_1 = param_1 & ~(1u << iVar8);
        if (*(volatile char *)(iVar9 + 0xc) != 0) {
            int obj = *(volatile int *)iVar9;
            call_fn_t pcVar7 = *(call_fn_t *)(obj + 0x10);
            if (pcVar7 == 0 || pcVar7(iVar9) == 0) {
                uVar10 = uVar10 & ~(1u << iVar8);
                int *pp = *(int **)(iVar9 + 4);
                FUN_0102e23c(iVar9, (unsigned int)*pp, 4);
            }
        }
    }
    return uVar10;
}
