/* readable reconstruction; identity: FUN_00087510 @ 0x00087510
 * public-name: clz32
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   clz32                                    <= FUN_00087510 @ 0x00087510
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 */
/* Reconstructed FUN_00087510 @ 0x87510  (parity: 300/300 trials, PROVEN) */

int clz32(unsigned int param_1)
{
    int iVar1;
    if (param_1 < 0x10000) {
        param_1 = param_1 << 0x10;
        iVar1 = 0x10;
    } else {
        iVar1 = 0;
    }
    if (param_1 < 0x1000000) {
        param_1 = param_1 << 8;
        iVar1 = iVar1 + 8;
    }
    if (param_1 < 0x10000000) {
        param_1 = param_1 << 4;
        iVar1 = iVar1 + 4;
    }
    if (param_1 < 0x40000000) {
        if ((int)(param_1 << 2) < 0) return iVar1 + 2;
        if ((int)(param_1 << 3) < 0) return iVar1 + 3;
        iVar1 = 0x20;
    } else if ((int)param_1 >= 0) {
        return iVar1 + 1;
    }
    return iVar1;
}
