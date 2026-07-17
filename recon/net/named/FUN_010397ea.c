/* readable reconstruction; identity: FUN_010397ea @ 0x010397ea
 * public-name: FUN_010397ea
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010397ea @ 0x10397ea  (parity 300 trials PROVEN) */
extern int FUN_0103973c(int a, int b, int c);
extern void FUN_01039752(int a, int b, int c, int d);

void FUN_010397ea(int param_1, int param_2, unsigned int param_3)
{
    int iVar1 = FUN_0103973c(param_1, param_2, 3);
    if (param_2 == iVar1) {
        volatile unsigned int *pc = (volatile unsigned int *)(param_1 + 0xc);
        *pc = *pc & ~(1u << (param_3 & 0xff));
        *(volatile unsigned int *)(param_1 + (param_3 + 4) * 4) = 0;
        return;
    }
    int uVar2 = FUN_0103973c(param_1, param_2, 2);
    *(volatile int *)(param_1 + (param_3 + 4) * 4) = iVar1;
    FUN_01039752(param_1, uVar2, 3, iVar1);
    FUN_01039752(param_1, iVar1, 2, uVar2);
}
