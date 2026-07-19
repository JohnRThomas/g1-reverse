/* readable reconstruction; identity: FUN_0005fa94 @ 0x0005fa94
 * public-name: dmic_read_block
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_uldivmod                         <= FUN_0000e244 @ 0x0000e244
 *   dmic_read_block                          <= FUN_0005fa94 @ 0x0005fa94
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   log_forward_zero_arg                     <= FUN_000837a2 @ 0x000837a2
 * address symbols (name @ address):
 *   rodata_881a0                             @ 0x000881a0
 *   rodata_f5660                             @ 0x000f5660
 *   rodata_f5679                             @ 0x000f5679
 */
/* Reconstructed FUN_0005fa94 @ 0x5fa94  (parity: 300/300 trials, PROVEN) */

extern unsigned long long __aeabi_uldivmod(int a,int b,int c,int d);
extern int k_msgq_get(int a, unsigned b, int c, int d);
extern void log_forward_zero_arg(unsigned a, unsigned b, void*c);
int dmic_read_block(int param_1, unsigned param_2, unsigned param_3, unsigned *param_4, unsigned param_5){
    int iVar3 = *(volatile int*)(param_1 + 0x10);
    unsigned char b = *(volatile unsigned char*)(iVar3 + 0x50);
    unsigned loc[2]; int iVar2;
    if ((int)((unsigned)b << 0x1e) >= 0){
        loc[1] = 0x000f5660; iVar2 = -5; loc[0] = 2;
        log_forward_zero_arg(0x000881a0, 0x1040, loc);
        return iVar2;
    }
    unsigned long long uVar4;
    if (param_5 == 0xffffffffu){
        uVar4 = 0xffffffffffffffffULL;
    } else {
        int r4c = (int)param_5 & ~((int)param_5 >> 31);
        long long lVar1 = (long long)r4c * 0x8000 + 999;
        uVar4 = __aeabi_uldivmod((int)lVar1, (int)((unsigned long long)lVar1 >> 32), 1000, 0);
    }
    iVar2 = k_msgq_get(iVar3 + 0x1c, param_3, (int)(unsigned)uVar4, (int)(unsigned)(uVar4 >> 32));
    if (iVar2 == 0){
        *param_4 = *(volatile unsigned*)(iVar3 + 0x18);
    } else {
        loc[1] = 0x000f5679; loc[0] = 2;
        log_forward_zero_arg(0x000881a0, 0x1040, loc);
    }
    return iVar2;
}
