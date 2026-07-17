/* readable reconstruction; identity: FUN_00084516 @ 0x00084516
 * public-name: FUN_00084516
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   us_to_ticks_scaled                       <= FUN_00012580 @ 0x00012580
 *   us_to_ticks_scaled_v2                    <= FUN_000125c0 @ 0x000125c0
 */
/* Reconstructed FUN_00084516 @ 0x84516  (parity: 300/300 trials, PROVEN) */

extern void us_to_ticks_scaled(int a, int b, unsigned c, unsigned d, unsigned e);
extern void us_to_ticks_scaled_v2(int a, int b, unsigned c);
unsigned FUN_00084516(int param_1, unsigned param_2, int param_3, unsigned param_4){
    int iVar2 = *(volatile int*)(param_1 + 0x10);
    unsigned uVar4;
    if (param_2 < 4){
        uVar4 = *(volatile unsigned*)(iVar2 + 0xc);
        if (param_2 == 2){
            param_2 = (unsigned)(int)*(volatile short*)(iVar2 + 8);
        } else if (param_2 == 3){
            short *psVar3 = (short*)(iVar2 + 2);
            int it = param_3;
            do {
                psVar3 = psVar3 + 1;
                int iVar1 = it + 8;
                us_to_ticks_scaled(it, (int)*(volatile short*)psVar3, uVar4, 0, 0);
                it = iVar1;
            } while (it != param_3 + 0x18);
            return 0;
        } else {
            if (param_2 != 1) param_2 = (unsigned)(int)*(volatile short*)(iVar2 + 4);
            else param_2 = (unsigned)(int)*(volatile short*)(iVar2 + 6);
        }
        us_to_ticks_scaled(param_3, (int)param_2, uVar4, param_4, param_4);
    } else {
        if (param_2 - 4 > 3) return 0xffffff7au;
        uVar4 = *(volatile unsigned*)(iVar2 + 0x18);
        if (param_2 == 6){
            param_2 = (unsigned)(int)*(volatile short*)(iVar2 + 0x14);
        } else if (param_2 == 7){
            short *psVar3 = (short*)(iVar2 + 0xe);
            int it = param_3;
            do {
                psVar3 = psVar3 + 1;
                int iVar1 = it + 8;
                us_to_ticks_scaled_v2(it, (int)*(volatile short*)psVar3, uVar4);
                it = iVar1;
            } while (it != param_3 + 0x18);
            return 0;
        } else {
            if (param_2 != 5) param_2 = (unsigned)(int)*(volatile short*)(iVar2 + 0x10);
            else param_2 = (unsigned)(int)*(volatile short*)(iVar2 + 0x12);
        }
        us_to_ticks_scaled_v2(param_3, (int)param_2, uVar4);
    }
    return 0;
}
