/* readable reconstruction; identity: FUN_000777f0 @ 0x000777f0
 * public-name: printf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __sinit                                  <= FUN_00076bcc @ 0x00076bcc
 *   _vfprintf_r                              <= FUN_00076ed4 @ 0x00076ed4
 *   printf                                   <= FUN_000777f0 @ 0x000777f0
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* Reconstructed FUN_000777f0 @ 0x777f0  (parity: 300/300 trials, PROVEN) */

extern void __sinit(int);
extern void _vfprintf_r(int, unsigned int, unsigned int, void*, unsigned int, void*);

void printf(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1 = *(volatile int*)0x20002d20UL;
    unsigned int uVar2 = param_1;
    unsigned int uStack_c = param_2;
    unsigned int uStack_8 = param_3;
    unsigned int uStack_4 = param_4;
    if (iVar1 != 0 && *(int*)(iVar1+0x18) == 0) {
        __sinit(iVar1);
    }
    _vfprintf_r(iVar1, *(unsigned int*)(iVar1+8), param_1, &uStack_c, uVar2, &uStack_c);
}
