/* readable reconstruction; identity: FUN_010323f8 @ 0x010323f8
 * public-name: FUN_010323f8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103bf70                           @ 0x0103bf70
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e187                           @ 0x0103e187
 */
/* net-core FUN_010323f8 @ 0x10323f8  (parity 300 trials PROVEN) */

extern int FUN_0103b0f0(void *a);
extern void FUN_01039bbe(unsigned int a, unsigned int b, unsigned int c);
extern void FUN_01039bb0(unsigned int a, unsigned int b);

typedef unsigned int (*fnptr)(void*, unsigned int, unsigned short);

unsigned int FUN_010323f8(unsigned int param_1, unsigned short param_2)
{
    void *iVar1 = (void*)0x0103bf70;
    int iVar2 = FUN_0103b0f0(iVar1);
    unsigned int target;
    fnptr f;
    if (iVar2 == 0) return 0xffffffed;
    target = *(unsigned int *)(*(unsigned int *)((char*)iVar1 + 8));
    if (target == 0) {
        FUN_01039bbe(0x0103d2a7, 0x0103e187, 0x4d);
        FUN_01039bb0(0x0103e187, 0x4d);
    }
    f = (fnptr)target;
    return f(iVar1, param_1, param_2);
}
