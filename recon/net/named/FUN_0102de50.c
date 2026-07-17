/* readable reconstruction; identity: FUN_0102de50 @ 0x0102de50
 * public-name: FUN_0102de50
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103c0ec                           @ 0x0103c0ec
 *   rodata_103c0fc                           @ 0x0103c0fc
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d5d7                           @ 0x0103d5d7
 */
/* net-core FUN_0102de50 @ 0x102de50  (parity 300 trials PROVEN) */

extern unsigned int FUN_0102de38(void);
extern void FUN_01039bbe(unsigned int a, unsigned int b, unsigned int c);
extern void FUN_01039bb0(unsigned int a, unsigned int b);

typedef void (*fnptr)(int*, unsigned int);

void FUN_0102de50(void)
{
    unsigned int uVar2 = FUN_0102de38();
    int *piVar1 = (int *)0x0103c0fc;
    int *piVar3 = (int *)0x0103c0ec;
    while (1) {
        if (piVar1 < piVar3) {
            FUN_01039bbe(0x0103d2a7, 0x0103d5d7, 0x1d1);
            FUN_01039bb0(0x0103d5d7, 0x1d1);
        }
        if (piVar1 <= piVar3) break;
        if ((*(volatile char *)(piVar3[1] + 5) != 0) && (*(volatile unsigned int *)(piVar3[0] + 4) != 0)) {
            fnptr fn = (fnptr)(*(unsigned int *)(piVar3[0] + 4));
            fn(piVar3, uVar2);
        }
        piVar3 = piVar3 + 4;
    }
}
