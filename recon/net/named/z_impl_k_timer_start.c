/* readable reconstruction; identity: FUN_01038448 @ 0x01038448
 * public-name: z_impl_k_timer_start
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_k_timer_start                     <= FUN_01038448 @ 0x01038448
 */
/* net-core FUN_01038448 @ 0x1038448  (parity 300 trials PROVEN) */
extern void FUN_01037f8c(int param_1, unsigned int lit, int param_3, int param_4);
extern void FUN_010380d8(int param_1);

static int SBORROW4(int a, int b)
{
    unsigned int ua = (unsigned int)a, ub = (unsigned int)b;
    unsigned int diff = ua - ub;
    return (int)(((ua ^ ub) & (ua ^ diff))) < 0;
}

void z_impl_k_timer_start(int param_1, unsigned int param_2, int param_3, int param_4,
                   unsigned int param_5, unsigned int param_6)
{
    if (param_4 == -1 && param_3 == -1) {
        return;
    }
    if ((int)((param_4 + 1) - (unsigned int)(param_3 != -1)) < 0 ==
        (SBORROW4(param_4, -1) != SBORROW4(param_4 + 1, (int)(unsigned int)(param_3 != -1)))) {
        if (param_4 < (int)(unsigned int)(param_3 == 0)) {
            param_3 = 1;
            param_4 = 0;
        }
        unsigned char bVar1 = param_3 != 0;
        param_3 = param_3 - 1;
        param_4 = param_4 - 1 + bVar1;
    }
    FUN_010380d8(param_1);
    *(volatile unsigned int *)(param_1 + 0x28) = param_5;
    *(volatile unsigned int *)(param_1 + 0x2c) = param_6;
    *(volatile unsigned int *)(param_1 + 0x30) = 0;
    FUN_01037f8c(param_1, 0x1038afd, param_3, param_4);
}
